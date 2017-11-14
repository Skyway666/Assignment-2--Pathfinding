#include "Player.h"



Player::Player(int x, int y, Player_Initial_Inf initial_inf) : GroundEntity(x, y)
{
	Animation_Loading();

	jump_time = initial_inf.jump_time;
	slide_time = initial_inf.slide_time;
	walljump_time = initial_inf.walljump_time;
	speed_modifier.y = initial_inf.speed_modifier.y;
	speed_modifier.x = initial_inf.speed_modifier.x;
	walljump_speed.y = initial_inf.walljump_speed.y;
	walljump_speed.x = initial_inf.walljump_speed.x;
	gravity = initial_inf.gravity;
	gravity2 = initial_inf.gravity;
	
	scale = 0.3;
	type = ENTITY_TYPES::PLAYER;
	SDL_Rect r{ 0, 0, 481, 547 };
	SDL_Rect collider_rect{ 0, 0, r.w * 0.2, r.h * 0.2 };
	contact.x = 0;
	contact.y = 0;
	collider = App->collision->AddCollider(collider_rect, COLLIDER_PLAYER,App->entities);
}


Player::~Player()
{

}

void Player::Update(float dt)
{
	player_dt = dt;

	if (contact.x != 0 && !super_godmode)
		speed.y = speed_modifier.y;
	else if (!super_godmode)
		speed.y = speed_modifier.y * 1.5;

	if (godmode)
		collider->type = COLLIDER_GOD;
	else if (super_godmode)
		collider->type = COLLIDER_SUPER_GOD;
	else
		collider->type = COLLIDER_PLAYER;

	player_x_displacement = App->map->data.player_starting_value.x - position.x;

	if (contact.y == 1 && !sliding)
	{
		animation = &idle;
		fall.Reset();
	}
	else if (contact.y != 1)
		animation = &fall;

	speed.x = 0;

	if (dead)
	{

		animation = &death;

		if (animation->Finished())
		{
			position.x = App->map->data.player_starting_value.x;
			position.y = App->map->data.player_starting_value.y - 5;
			death.Reset();
			dead = false;
		}
	}

	if (!win && !dead)
	{
		// Godmode
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			if (godmode)
				godmode = false;

			if (super_godmode)
				super_godmode = false;
			else
				super_godmode = true;
		}
		else if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			if (super_godmode)
				super_godmode = false;

			if (godmode)
				godmode = false;
			else
				godmode = true;
		}

		// Sliding
		if (!super_godmode && App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && contact.y == 1)
		{
			if (!super_godmode)
				sliding = true;
		}
		else if (super_godmode && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			speed.y = speed_modifier.y;

		// Moving right
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !sliding)
		{
			flip = false;

			if (contact.y == 1)
				animation = &run;
			if (contact.x != 2)
				speed.x = speed_modifier.x;
		}

		// Moving left
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !sliding)
		{
			flip = true;

			if (contact.y == 1)
				animation = &run;
			if (contact.x != 1)
				speed.x = -speed_modifier.x;
		}

		// Stop moving if both A and D are pressed
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			speed.x = 0;
			if (animation == &run)
				animation = &idle;
		}

		// Jumping
		if (!super_godmode && App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !sliding)
		{
				gravity = gravity2;
				if (contact.y == 1)
				{
					jumping = true;
				}
				else if (contact.x == 1 || contact.x == 2)
				{
					walljumping = true;
				}
		}
		else if (super_godmode && App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			speed.y = -speed_modifier.y;

		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		{
			if (App->map->map != 0)
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
	else if (sliding && contact.x != 2 && !flip)
		speed.x = 1.5 * speed_modifier.x;


	if (!walljumping)
		position.x += ceil(speed.x * dt);

	if (contact.y != 1 && !super_godmode)
	{
		if (StickToWall)
			position.y += ceil(gravity / 2 * dt);
		else if (contact.y != 1)
			position.y += ceil(gravity * dt);
	}

	if (super_godmode)
	{
		position.y += speed.y * dt;
		speed.y = 0;
	}

	StickToWall = false;
	contact.x = 0;
	contact.y = 0;

	// Draw everything --------------------------------------



	//Put collider next to player (Should be done in "draw")
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

	// Win condition timer (Should not be done here, and timer should be the good one
	if (win == true)
	{
		if (allowtime)
		{
			time = frames;
			allowtime = false;
		}
		if (frames - time < 360)
		{
			App->render->Blit(App->scene->win_screen, position.x - 400, position.y - 400);
		}
		else
		{
			allowtime = true;
			win = false;
		}
	}

}

void Player::WallSlide()
{
	if (contact.x == 2 && contact.y != 1 && contact.y != 2)
	{
		StickToWall = true;
		animation = &wallslideright;
		flip = false;
	}
	else if (contact.x == 1 && contact.y != 1 && contact.y != 2)
	{
		StickToWall = true;
		animation = &wallslideleft;
		flip = false;
	}
}

void Player::Jump()
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

		if (frames - time <= jump_time / (60 / App->framerate_cap) && contact.y == 0)
		{
			animation = &jump;
			position.y -= ceil(speed.y * player_dt);
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

		if (frames - time <= walljump_time / (60 / App->framerate_cap) && contact.x == 0)
		{
			animation = &jump;
			position.y -= ceil(walljump_speed.y * player_dt);

			if (jcontact == 1)
			{
				position.x += ceil(walljump_speed.x * player_dt);
				flip = true;
			}
			else if (jcontact == 2)
				position.x -= ceil(walljump_speed.x * player_dt);
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

void Player::Slide()
{
	if (sliding)
	{
		if (allowtime)
		{
			time = frames;
			allowtime = false;

			collider->SetSize(collider->rect.w + 3, App->map->data.tile_height - 50);
			player_height_before_sliding = position.y;
			App->audio->PlayFx(2);
		}
		if (frames - time <= slide_time / (60 / App->framerate_cap))
		{
			animation = &slide;
			rect_after_sliding.x = position.x;
			rect_after_sliding.y = player_height_before_sliding;
			rect_after_sliding.h = 547 * 0.2;
			rect_after_sliding.w = 481 * 0.2;

		}


		else if (App->collision->WillCollideAfterSlide(this, player_dt) && contact.x == 0)
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

void Player::Animation_Loading()
{
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

void Player::ManagePhysics(float dt)
{
	App->collision->ManageGroundCollisions((GroundEntity*)this, dt);
}

void Player::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_BONE)
	{
		if (App->map->map == 0)
		{
			App->collision->Erase_Non_Player_Colliders();
			App->map->CleanUp();
			App->map->Load("Level 2 final.tmx");
			App->map->map = 1;
			App->pathfinding->SetMap();
	
			position.x = App->map->data.player_starting_value.x;
			position.y = App->map->data.player_starting_value.y;
		}
		else if (App->map->map == 1)
		{
			App->collision->Erase_Non_Player_Colliders();
			App->map->CleanUp();
			App->map->Load("Level 1 final.tmx");
			App->map->map = 0;
			win = true;
			
			position.x = App->map->data.player_starting_value.x;
			position.y = App->map->data.player_starting_value.y;
		}
	}
	else if (collider->type == COLLIDER_DEADLY)
	{
		dead = true;
	}
}
