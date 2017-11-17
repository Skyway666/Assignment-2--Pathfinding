#include "GroundEnemy.h"



GroundEnemy::GroundEnemy(int x, int y, Ground_Enemy_Initial_Inf initial_inf) : GroundEntity(x, y)
{
	type = ENTITY_TYPES::GROUND_ENEMY;
	scale = 0.19;

	position.x = x;
	position.y = y;

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

	walk_time = 30; // Could be initialized with an argument
	speed.y = speed_modifier.y;
	speed.x = speed_modifier.x;
	walk_timer.Start(walk_time);
	idle_speed = speed_modifier.x;

	SDL_Rect r{ 0, 0, 579, 763 };
	SDL_Rect collider_rect{ 0, 0, (r.w - 100) * scale, (r.h - 40) * scale };

	collider = App->collision->AddCollider(collider_rect, COLLIDER_ENEMY_GROUND, App->entities);
}


GroundEnemy::~GroundEnemy()
{

}

void GroundEnemy::Update(float dt, bool do_logic)
{
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		position.x = App->entities->player->position.x;
		position.y = App->entities->player->position.y;
	}
	speed.x = speed_modifier.x;
	frames++;
	animation = &run;

	if (contact.y == 1 && contact.x != 0)
	{
		jumping = true;
		turn = true;
	}

	if (is_idle)
		Exec_idle();
	else if (!is_idle)
		Exec_attack();

	if (front_of_pit && !is_idle)
		speed.x = 0;

	if (jumping && !is_idle)
		position.x += speed.x * jumping_multiplier * dt;
	else if (jumping && is_idle)
		position.x += speed.x * jumping_multiplier * dt;
	else if (!is_idle)
		position.x += speed.x * dt * player_pos;
	else
		position.x += speed.x * dt;

	turn = false;

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
	if (walk_timer.IsOver() || turn || App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN || front_of_pit)
	{
		idle_speed = -idle_speed;
		walk_timer.Start(walk_time);
	}

	speed.x = idle_speed;

	if (speed.x < 0)
		flip = true;
	else if (speed.x > 0)
		flip = false;

	front_of_pit = false;
}

void GroundEnemy::Exec_attack()
{
	if (App->entities->player->collider != nullptr)
	{
		if (position.x - App->entities->player->position.x >= 0)
			player_pos = -1;
		else
			player_pos = 1;
	}

	if (player_pos == -1)
		flip = true;
	else if (player_pos == 1)
		flip = false;

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

void GroundEnemy::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PATH)
		is_idle = false;
	else if (collider->type == COLLIDER_WALKABLE)
		is_idle = true;
}

void GroundEnemy::ManagePhysics(float dt)
{
	App->collision->ManageGroundCollisions((GroundEntity*)this, dt);
	App->collision->EnemyJump((GroundEntity*)this, dt);
}