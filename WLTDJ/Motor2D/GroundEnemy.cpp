#include "GroundEnemy.h"



GroundEnemy::GroundEnemy(int x, int y, Ground_Enemy_Initial_Inf initial_inf) : GroundEntity(x, y)
{
	type = ENTITY_TYPES::GROUND_ENEMY;
	scale = 0.15;

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

	speed.y = speed_modifier.y;
	speed.x = speed_modifier.x;
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
	
	frames++;
	animation = &run;
	speed.x = speed_modifier.x;
	jump.speed = 0.4 * dt;
	run.speed = 0.4 * dt;

	if (last_contact_y != 1 && contact.y == 1)
		just_landed = true;

	if (contact.x != 0 && !is_idle)
		front_of_unwalkable = true;

	if (contact.y == 1 && contact.x != 0)
	{
		turn = true;
	}

	if (is_idle)
		Exec_idle();
	else if (!is_idle)
		Exec_attack();

	if (front_of_unwalkable && !is_idle)
		speed.x = 0;
	if (front_of_unwalkable && !is_idle && (((contact.x == 1 && player_pos == -1) || (contact.x == 2 && player_pos == 1))))
		speed.x = 0;

	if (!jumping && contact.y == 1)
		jump_x = 0;
	if (jump_x != 0)
		speed.x = jump_x;

	if (jumping)
		position.x += speed.x * jumping_multiplier * dt * player_pos;
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

	last_contact_y = contact.y;
	contact.x = 0;
	contact.y = 0;
	front_of_unwalkable = false;
}

void GroundEnemy::Exec_idle()
{
	player_pos = 1;

	if (turn || App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN || front_of_unwalkable)
		idle_speed = -idle_speed;

	speed.x = idle_speed;

	if (speed.x < 0)
		flip = true;
	else if (speed.x > 0)
		flip = false;

	front_of_unwalkable = false;
}

void GroundEnemy::Exec_attack()
{
	if (contact.y == 1)
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
	if (jumping && !just_landed)
	{
		if (allowtime)
		{
			time = frames;
			allowtime = false;
			contact.y = 0;
			jump.Reset();
		}

		if (frames - time <= jump_time / dt && contact.y == 0)
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
	else
		jumping = false;
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
	App->collision->EnemyJump(this, dt);
}