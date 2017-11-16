#include "GroundEnemy.h"



GroundEnemy::GroundEnemy(int x, int y, Ground_Enemy_Initial_Inf initial_inf) : GroundEntity(x, y)
{
	type = ENTITY_TYPES::GROUND_ENEMY;
	scale = 0.19;

	int row = 0;

	// running
	for (int i = 0; i < 8; i++)
		run.PushBack({ 579 * i, 1732 + 763 * row, 547, 763 });

	row++;

	// jumping
	for (int i = 0; i < 10; i++)
		jump.PushBack({ 579 * i, 1732 + 763 * row, 579, 763 });

	jump.loop = false;

	gravity = initial_inf.gravity;
	jump_time = initial_inf.jump_time;
	speed_modifier.y = initial_inf.speed_modifier.y;
	speed_modifier.x = initial_inf.speed_modifier.x;

	walk_time = 30; //Could be initialized with an argument
	speed.y = speed_modifier.y;
	speed.x = speed_modifier.x;
	walk_timer.Start(walk_time);
	idle_speed = speed_modifier.x;

	SDL_Rect r{ 0, 0, 579, 763 };
	SDL_Rect collider_rect{ 0, 0, r.w * scale, r.h * scale };

	collider = App->collision->AddCollider(collider_rect, COLLIDER_ENEMY_GROUND, App->entities);
}


GroundEnemy::~GroundEnemy()
{

}

void GroundEnemy::Update(float dt, bool do_logic)
{
	frames++;

	//Maybe should be a function
	center.x = position.x + (1135 * scale) / 2;
	center.y = position.y + (845 * scale) / 2;

	animation = &run;
	if (is_idle)
		Exec_idle();
	else
		Exec_atack();


	// DoLogic
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if (debug)
			debug = false;
		else
			debug = true;

		Find_path();
		//is_idle = false;
		speed.x = speed_modifier.x * 2;
	}

	if (debug)
		App->pathfinding->DebugDraw();

	if (speed.x < 0)
		flip = true;
	else if (speed.x > 0)
		flip = false;

	position.x += speed.x * dt;

	if (contact.y == 1 && contact.x != 0)
		jumping = true;

	Jump(dt);

	// Simulate gravity
	if (contact.y != 1)
		position.y += ceil(gravity * dt);

	// Make collider follow enemy
	collider->SetPos(position.x, position.y);

	contact.x = 0;
	contact.y = 0;
}

void GroundEnemy::Exec_idle()
{
	if (walk_timer.IsOver() || contact.x != 0)
	{
		idle_speed = -idle_speed;
		walk_timer.Start(walk_time);
	}

	speed.x = idle_speed;
}

void GroundEnemy::Exec_atack()
{
	iPoint monster_map_pos(center.x, center.y);
	App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);

	if (path_to_follow->At(next_tile) != nullptr)
	{
		if (*path_to_follow->At(next_tile) == monster_map_pos)
		{
			next_tile++;
		}
		else
		{
			iPoint tile_to_reach = *path_to_follow->At(next_tile);

			speed.y = (tile_to_reach.y - monster_map_pos.y) * 2;
			speed.x = (tile_to_reach.x - monster_map_pos.x) * 2;
		}
	}
	else
	{
		speed.x = 0;
		speed.y = 0;
	}

}

void GroundEnemy::Find_path()
{
	//Pathfinding
	iPoint player_map_pos(App->entities->player->position.x, App->entities->player->position.y);
	iPoint monster_map_pos(center.x, center.y);

	App->map->WorldToMap(&player_map_pos.x, &player_map_pos.y);
	App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);

	App->pathfinding->CreateGroundPath(monster_map_pos, {player_map_pos.y + 1, monster_map_pos.x});

	path_to_follow = App->pathfinding->GetLastPath();
	next_tile = 0;

	App->pathfinding->DebugDraw();
}

void GroundEnemy::Jump(float dt)
{
	// jump
	if (jumping)
	{
		if (allowtime)
		{
			time = frames;
			allowtime = false;
			contact.y = 0;
			jump.Reset();
		}

		if (frames - time <= jump_time / (60 / App->framerate_cap) && contact.y == 0)
		{
			animation = &jump;
			position.y -= ceil(speed.y * dt);
		}
		else
		{
			jumping = false;
			allowtime = true;
			jump.Reset();
		}

		if (contact.y == 1)
		{
			jumping = false;
			allowtime = true;
			jump.Reset();
		}
	}
}

void GroundEnemy::OnCollision()
{

}

void GroundEnemy::ManagePhysics(float dt)
{
	App->collision->ManageGroundCollisions((GroundEntity*)this, dt);
	App->collision->EnemyJump((GroundEntity*)this, dt);
}