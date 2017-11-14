#include "Air_enemy.h"



Air_enemy::Air_enemy(int x, int y): Entity(x,y)
{
	scale = 0.1;
	type = ENTITY_TYPES::AIR_ENEMY;

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
	side_fly_time = 2; //Could be initialized with an argument
	speed.x = 2;
	ideling_heigh = y;
	side_fly_timer.Start(side_fly_time);
}


Air_enemy::~Air_enemy()
{

}

void Air_enemy::Update(float dt)
{

    animation = &idle;
	if (is_idle)
		Exec_idle();
	else
		Exec_atack();


    //DoLogic, basically
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)
	{ 
		Find_path();
		is_idle = false;
	}
	if (speed.x < 0)
		flip = true;
	else if(speed.x > 0)
		flip = false;

	position.x += speed.x * dt;
	position.y += speed.y * dt;

}
void Air_enemy::Exec_idle()
{
	if (side_fly_timer.IsOver())
	{
		idle_speed = -idle_speed;
		side_fly_timer.Start(side_fly_time);
	}

	speed.x = idle_speed;

	
}

void Air_enemy::Exec_atack()
{
	iPoint monster_map_pos(position.x, position.y);
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

			speed.y = (tile_to_reach.y - monster_map_pos.y)*2;
			speed.x = (tile_to_reach.x - monster_map_pos.x)*2;
		}
	}
	else
	{
		speed.x = 0;
		speed.y = 0;
	}

}

void Air_enemy::Find_path()
{
	//Pathfinding
	iPoint player_map_pos(App->entities->player->position.x, App->entities->player->position.y);
	iPoint monster_map_pos(position.x, position.y);

	App->map->WorldToMap(&player_map_pos.x, &player_map_pos.y);
	App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);

	App->pathfinding->CreatePath(monster_map_pos, player_map_pos);

	path_to_follow = App->pathfinding->GetLastPath();
	next_tile = 0;

	App->pathfinding->DebugDraw();
}

void Air_enemy::OnCollision() 
{

}