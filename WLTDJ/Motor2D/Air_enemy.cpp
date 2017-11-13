#include "Air_enemy.h"



Air_enemy::Air_enemy(int x, int y): Entity(x,y)
{
	scale = 0.1;
	type = ENTITY_TYPES::AIR_ENEMY;
}


Air_enemy::~Air_enemy()
{

}

void Air_enemy::Update(float dt)
{
	iPoint player_map_pos(App->entities->player->position.x, App->player->position.y);
	iPoint monster_map_pos(position.x, position.y);

	App->map->WorldToMap(&player_map_pos.x, &player_map_pos.y);
	App->map->WorldToMap(&monster_map_pos.x, &monster_map_pos.y);

	
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)
	{
		App->pathfinding->CreatePath(monster_map_pos, player_map_pos);
	}

	App->pathfinding->DebugDraw();
}

void Air_enemy::OnCollision() 
{

}