#include "AirEnemy.h"



AirEnemy::AirEnemy(int x, int y): Entity(x,y)
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


	iPoint scaledw_h(1135 * 0.1, 845 * 0.1);
	collider = App->collision->AddCollider({x, y, scaledw_h.x,scaledw_h.y}, COLLIDER_DEADLY, App->entities);
	idle.loop = true;
	idle.speed = 0.3; 
	side_fly_time = 2; //Could be initialized with an argument
	speed_modifier.x = 4; //Could be initialized with an argument
	speed_modifier.y = 4; //Could be initialized with an argument
	idle_speed = 2; //Could be initialized with an argument
	ideling_heigh = y; 
	agro_distance = 4; //Could be initialized with an argument
	tired_distance = 10; //Could be initialized with an argument
	initial_tile = iPoint(x, y); 
	App->map->WorldToMap(&initial_tile.x, &initial_tile.y);



	side_fly_timer.Start(side_fly_time);
}


AirEnemy::~AirEnemy()
{

}

void AirEnemy::Update(float dt)
{
	//Maybe should be a function
	center.x = position.x + (1135 * scale)/2;
	center.y = position.y + (845 * scale)/2;

    animation = &idle;
	if (is_idle)
		Exec_idle();
	else
		Exec_path();

	if (distance_to_player() < agro_distance && !returning)
	{
		is_idle = false;
	}
	if(distance_to_start() > tired_distance)
	{
     	returning = true;
	}

    if (do_logic.IsOver())
	{ 
		if (!returning && !is_idle)
		{
			Find_path_player();
			do_logic.Start(0.5);
		}
		else if (returning)
		{
			do_logic.Start(0.5);
			if(!home_path_found)
			{ 
				Find_path_home();
				home_path_found = true;
			}
			iPoint monster_map_pos(center.x, center.y);
			App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);
			if (monster_map_pos == initial_tile)
			{
				returning = false;
				is_idle = true;
				home_path_found = false;
			}
		}
	}


	if (speed.x < 0)
		flip = true;
	else if(speed.x > 0)
		flip = false;

	//Add speed to position
	position.x += speed.x * dt;
	position.y += speed.y * dt;

	//Make collider follow enemy
	collider->SetPos(position.x, position.y);   
}
void AirEnemy::Exec_idle()
{
	if (side_fly_timer.IsOver())
	{
		idle_speed = -idle_speed;
		side_fly_timer.Start(side_fly_time);
	}

	speed.x = idle_speed;

	
}

void AirEnemy::Exec_path()
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

			speed.y = (tile_to_reach.y - monster_map_pos.y)*speed_modifier.y;
			speed.x = (tile_to_reach.x - monster_map_pos.x)*speed_modifier.x;
		}
	}
	else
	{
		speed.x = 0;
		speed.y = 0;
	}

}

void AirEnemy::Find_path_player()
{
	//Pathfinding
	iPoint player_map_pos(App->entities->player->center.x, App->entities->player->center.y);
	iPoint monster_map_pos(center.x, center.y);

	App->map->WorldToMap(&player_map_pos.x, &player_map_pos.y);
	App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);

	App->pathfinding->CreatePath(monster_map_pos, player_map_pos);

	path_to_follow = App->pathfinding->GetLastPath();
	next_tile = 0;

	App->pathfinding->DebugDraw();
}

void AirEnemy::Find_path_home()
{
	//Pathfinding
	iPoint monster_map_pos(center.x, center.y);

	App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);

	App->pathfinding->CreatePath(monster_map_pos, initial_tile);

	path_to_follow = App->pathfinding->GetLastPath();
	next_tile = 0;

	App->pathfinding->DebugDraw();
}


void AirEnemy::OnCollision() 
{
	
}

int AirEnemy::distance_to_player()
{
	iPoint monster_map_pos(center.x, center.y);
	App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);
	iPoint player_map_pos(App->entities->player->center.x, App->entities->player->center.y);
	App->map->WorldToMap(&player_map_pos.x, &player_map_pos.y);

	int ret = sqrt(pow(player_map_pos.x - monster_map_pos.x, 2) + pow(player_map_pos.y - monster_map_pos.y, 2));
	return ret;
}

int AirEnemy::distance_to_start()
{
	iPoint monster_map_pos(center.x, center.y);
	App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);

	int ret = sqrt(pow(initial_tile.x - monster_map_pos.x, 2) + pow(initial_tile.y - monster_map_pos.y, 2));
	return ret;
}