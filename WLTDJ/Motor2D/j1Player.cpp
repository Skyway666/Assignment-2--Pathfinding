#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Map.h"
#include "p2Log.h"
#include "j1Audio.h"
#include "j1Scene.h"

j1Player::j1Player()
{
	name.create("player");
	position.x = 0;
	position.y = 0;
	int row = 0;

	sprite_distance.x = 548;
	sprite_distance.y = 482;

	// dying
	for (int i = 0; i < 10; i++)
		death.PushBack({ 1 + sprite_distance.x * i, 1 + sprite_distance.y * row, 547, 481 });

	death.loop = false;
	death.speed = 0.8;
	row++;

	// idle animation
	for (int i = 0; i < 10; i++)
		idle.PushBack({ 1 + sprite_distance.x * i, 1 + sprite_distance.y * row, 547, 481 });

	idle.speed = 0.8;
	row++;

	// running
	for (int i = 0; i < 8; i++)
		run.PushBack({ 1 + sprite_distance.x * i, 1 + sprite_distance.y * row, 547, 481 });

	row++;

	// sliding
	for (int i = 0; i < 10; i++)
		slide.PushBack({ 1 + sprite_distance.x * i, 1 + sprite_distance.y * row, 547, 481 });

	row++;

	// jumping
	for (int i = 0; i < 8; i++)
		jump.PushBack({ 1 + sprite_distance.x * i, 1 + sprite_distance.y * row, 547, 481 });

	jump.loop = false;

	// wall slide left

	wallslideleft.PushBack({ 1 + sprite_distance.x * 8, 1 + sprite_distance.y * row, 547, 481 });
	wallslideleft.PushBack({ 1 + sprite_distance.x * 9, 1 + sprite_distance.y * row, 547, 481 });

	wallslideleft.speed = 0.1;
	row++;

	// falling
	for (int i = 0; i < 7; i++)
		fall.PushBack({ 1 + sprite_distance.x * i, 1 + sprite_distance.y * row, 547, 481 });

	fall.speed = 0.2;
	fall.loop = false;

	// wall slide right

	wallslideright.PushBack({ 1 + sprite_distance.x * 8, 1 + sprite_distance.y * row, 547, 481 });
	wallslideright.PushBack({ 1 + sprite_distance.x * 9, 1 + sprite_distance.y * row, 547, 481 });

	wallslideright.speed = 0.1;
}

j1Player::~j1Player()
{
	App->tex->UnLoad(graphics);
	App->tex->UnLoad(App->map->bone_graphics);
}

bool j1Player::Awake(pugi::xml_node& conf)
{
	jump_time = conf.child("jump_time").attribute("value").as_int();
	slide_time = conf.child("slide_time").attribute("value").as_int();
	walljump_time = conf.child("walljump_time").attribute("value").as_int();
	speed_modifier.y = conf.child("speed_modifier.y").attribute("value").as_float();
	speed_modifier.x = conf.child("speed_modifier.x").attribute("value").as_float();
	walljump_speed.y = conf.child("walljump_speed.y").attribute("value").as_float();
	walljump_speed.x = conf.child("walljump_speed.x").attribute("value").as_float();
	gravity = conf.child("gravity").attribute("value").as_float();

	return true;
}
// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->tex->Load("textures/SpriteSheet.png");
	App->map->bone_graphics = App->tex->Load("textures/BONE.png");
	App->scene->win_screen = App->tex->Load("textures/WinScreen.png");

	SDL_Rect r{ 0, 0, 481, 547 };

	SDL_Rect ground{ r.x + 1000, r.y + 900, r.w, 100 };

	SDL_Rect collider_rect{ 0, 0, r.w * 0.2, r.h * 0.2 };

	contact.x = 0;
	contact.y = 0;

	collider = App->collision->AddCollider(collider_rect, COLLIDER_PLAYER);

	
	return ret;
}

// Update: draw background
bool j1Player::PostUpdate()
{
	if (contact.x != 0)
		speed.y = speed_modifier.y;
	else
		speed.y = speed_modifier.y * 1.5;

	player_x_displacement = App->map->data.player_starting_value.x - position.x;

	if (contact.y == 1 && !sliding)
	{
		current_animation = &idle;
		fall.Reset();
	}
	else if (contact.y != 1)
		current_animation = &fall;

	speed.x = 0;

	if (dead)
	{

		current_animation = &death;

		if(current_animation->Finished())
		{ 
			position.x = App->map->data.player_starting_value.x;
			position.y = App->map->data.player_starting_value.y - 5;
			death.Reset();
			dead = false;
		}
	}

	if (!win && !dead)
	{ 
		// Sliding
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && contact.y == 1)
		{
			sliding = true;
		}

		// Moving right
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !sliding)
		{
			flip = false;

			if (contact.y == 1)
				current_animation = &run;
			if (contact.x != 2)
				speed.x = speed_modifier.x;
		}

		// Moving left
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !sliding)
		{
			flip = true;

			if (contact.y == 1)
				current_animation = &run;
			if (contact.x != 1)
				speed.x = -speed_modifier.x;
		}

		// Jumping
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !sliding)
		{
			if (contact.y == 1)
			{
				jumping = true;
			}
			else if (contact.x == 1 || contact.x == 2)
			{
				walljumping = true;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		{
			if(App->map->map != 0)
			{ 
			   App->map->map = 0;
			   App->collision->Erase_Non_Player_Colliders();
			   App->map->CleanUp();
			   App->map->Load("Level 1 final.tmx");

			}
			position.x = App->map->data.player_starting_value.x;
			position.y = App->map->data.player_starting_value.y - gravity * 2;
		}
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{
			position.x = App->map->data.player_starting_value.x;
			position.y = App->map->data.player_starting_value.y - gravity * 2;
		}
	}

	WallSlide();
	Jump();
	Slide();

	if (sliding && contact.x != 1 && flip)
		speed.x = -1.5 * speed_modifier.x;
	else if ( sliding && contact.x != 2 && !flip)
		speed.x = 1.5 * speed_modifier.x;


	if (!walljumping)
		position.x += speed.x;

	if (contact.y != 1 && StickToWall)
		position.y += gravity / 2;

	else if (contact.y != 1)
		position.y += gravity;

	StickToWall = false;
	contact.x = 0;
	contact.y = 0;

	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, 0.3, &current_animation->GetCurrentFrame(), flip);

	// Set camera to follow the player
	App->render->camera.x = -position.x + 400;
	App->render->camera.y = -position.y + 400;

	//Put collider next to player
	if (collider != nullptr)
	{
		if (!sliding)
		  collider->SetPos(position.x + 30, position.y + 30);
		else
		{ 
			    collider->SetPos(position.x + 30, position.y + 547 * 0.2 - App->map->data.tile_height - 1 + 50);
		
		}
	}

	frames++;

	// Win condition timer
	if(win == true)
	{ 
		if(allowtime)
		{ 
		   time = frames;
		   allowtime = false;
		}
	    if(frames - time < 360)
		{ 
	       App->render->Blit(App->scene->win_screen, position.x- 400, position.y - 400);
		}
		else
		{
			allowtime = true;
			win = false;
		}
	}


	return true;
}

void j1Player::WallSlide()
{
	if (contact.x == 2 && contact.y != 1 && contact.y != 2)
	{
		StickToWall = true;
		current_animation = &wallslideright;
		flip = false;
	}
	else if (contact.x == 1 && contact.y != 1 && contact.y != 2)
	{
		StickToWall = true;
		current_animation = &wallslideleft;
		flip = false;
	}
}

void j1Player::Jump()
{
	// jump
	if (jumping)
	{
		if (allowtime)
		{
			time = frames;
			allowtime = false;
			contact.y = 0;
			App->audio->PlayFx(1);
			fall.Reset();
		}

		if (frames - time <= jump_time && contact.y == 0)
		{
			current_animation = &jump;
			position.y -= speed.y;
		}
		else
		{
			jumping = false;
			allowtime = true;
			jump.Reset();
		}

		if (contact.y == 1 && (contact.x == 1 || contact.x == 2))
		{
			jumping = false;
			allowtime = true;
			jump.Reset();
		}
	}
	// wall jump
	else if (walljumping)
	{
		fall.Reset();

		if (allowtime)
		{
			time = frames;
			allowtime = false;
			jcontact = contact.x;
			contact.x = 0;
			App->audio->PlayFx(1);
		}

		if (frames - time <= walljump_time && contact.x == 0)
		{
			current_animation = &jump;
			position.y -= walljump_speed.y;

			if (jcontact == 1)
			{
				position.x += walljump_speed.x;
				flip = true;
			}
			else if (jcontact == 2)
				position.x -= walljump_speed.x;
		}
		else
		{
			walljumping = false;
			allowtime = true;
			jump.Reset();
		}

		if (contact.y == 1 || contact.x == 1 || contact.x == 2)
		{
			walljumping = false;
			allowtime = true;
			jump.Reset();
		}
	}
}

void j1Player::Slide()
{	
	if (sliding)
	{
		if (allowtime)
		{
			time = frames;
			allowtime = false;
			
			collider->SetSize(collider->rect.w + 3, App->map->data.tile_height -50);
			player_height_before_sliding = position.y;
			App->audio->PlayFx(2);
		}
		if (frames - time <= slide_time) 
		{
			current_animation = &slide;
			rect_after_sliding.x = position.x;
			rect_after_sliding.y = player_height_before_sliding;
			rect_after_sliding.h = 547 * 0.2;
			rect_after_sliding.w = 481 * 0.2;

		}

	
		else if (App->collision->WillCollideAfterSlide(rect_after_sliding , 1) && contact.x == 0)
		{
			time = frames;
		}
		else
		{
			sliding = false;
			allowtime = true;
			collider->SetSize(481 * 0.2, 547 * 0.2);
			if (contact.y == 1)
			position.y = player_height_before_sliding - 3;
		}
	}
}

bool j1Player::Load(pugi::xml_node& data)
{
	if(App->map->map == data.child("player_position").attribute("map").as_int())
	{ 
		position.x = data.child("player_position").attribute("x").as_float();
		position.y = data.child("player_position").attribute("y").as_float() - gravity * 2;
	}
	else
	{
		if (App->map->map == 0)
		{
			App->map->map = 1;
			App->collision->Erase_Non_Player_Colliders();
			App->map->CleanUp();
			App->map->Load("Level 2 final.tmx");
			position.x = data.child("player_position").attribute("x").as_float();
			position.y = data.child("player_position").attribute("y").as_float() - gravity * 2;
		}
		else
		{
			App->map->map = 0;
			App->collision->Erase_Non_Player_Colliders();
			App->map->CleanUp();
			App->map->Load("Level 1 final.tmx");
			position.x = data.child("player_position").attribute("x").as_float();
			position.y = data.child("player_position").attribute("y").as_float() - gravity * 2;
		}
	}

	return true;
}

// Save Game State
bool j1Player::Save(pugi::xml_node& data) const
{
	pugi::xml_node player = data.append_child("player_position");

	player.append_attribute("x") = position.x;
	player.append_attribute("y") = position.y;
	player.append_attribute("map") = App->map->map;

	return true;
}