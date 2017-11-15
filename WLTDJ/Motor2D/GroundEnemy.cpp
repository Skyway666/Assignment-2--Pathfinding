#include "GroundEnemy.h"



GroundEnemy::GroundEnemy(int x, int y) : Entity(x, y)
{
	scale = 0.1;
	type = ENTITY_TYPES::GROUND_ENEMY;

	idle.PushBack({ 0,0,1135,845 });
	idle.PushBack({ 1135,0,1135,845 });
	idle.PushBack({ 1135 * 2,0,1135,845 });
	idle.PushBack({ 1135 * 3,0,1135,845 });
	idle.PushBack({ 0,845,1135,845 });
	idle.PushBack({ 1135,845,1135,845 });
	idle.PushBack({ 1135 * 2,845,1135,845 });
	idle.PushBack({ 1135 * 3,845,1135,845 });


	idle.loop = true;
	idle.speed = 0.3;
	walk_time = 2; //Could be initialized with an argument
	speed.x = 2;
	walk_timer.Start(walk_time);


}


GroundEnemy::~GroundEnemy()
{

}

void GroundEnemy::Update(float dt)
{
	//Maybe should be a function
	center.x = position.x + (1135 * scale) / 2;
	center.y = position.y + (845 * scale) / 2;

	animation = &idle;
	if (is_idle)
		Exec_idle();
	else
		Exec_atack();


	// DoLogic
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		Find_path();
		is_idle = false;
		speed.x = speed_modifier.x * 2;
	}

	if (speed.x < 0)
		flip = true;
	else if (speed.x > 0)
		flip = false;

	position.x += speed.x * dt;
	position.y += speed.y * dt;

}
void GroundEnemy::Exec_idle()
{
	if (walk_timer.IsOver())
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

	App->pathfinding->CreatePath(monster_map_pos, player_map_pos);

	path_to_follow = App->pathfinding->GetLastPath();
	next_tile = 0;

	App->pathfinding->DebugDraw();
}

void GroundEnemy::OnCollision()
{

}