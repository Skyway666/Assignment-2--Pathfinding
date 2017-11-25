#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Entities.h"
#include "j1Textures.h"
#include "Entity.h"
#include "j1Map.h"
#include "j1Audio.h"
#include "p2Log.h"
#include "AirEnemy.h"
#include "Player.h"
#include "GroundEnemy.h"
#define SPAWN_MARGIN 100

j1Entities::j1Entities()
{
	name.create("entities"); //Should obviously be called "entities", as to recive all their information, but untill "moduleplayer" is completelly erased, it's easier this way
}

// Destructor
j1Entities::~j1Entities()
{
}

bool j1Entities::Awake(pugi::xml_node& conf)
{

	//Load player initial variables
	pugi::xml_node player = conf.child("player");

	p_ini_inf.jump_time = player.child("jump_time").attribute("value").as_int();
	p_ini_inf.slide_time = player.child("slide_time").attribute("value").as_int();
	p_ini_inf.walljump_time = player.child("walljump_time").attribute("value").as_int();
	p_ini_inf.speed_modifier.x = player.child("speed_modifier.x").attribute("value").as_float();
	p_ini_inf.speed_modifier.y = player.child("speed_modifier.y").attribute("value").as_float();
	p_ini_inf.walljump_speed.x = player.child("walljump_speed.x").attribute("value").as_float();
	p_ini_inf.walljump_speed.y = player.child("walljump_speed.y").attribute("value").as_float();
	p_ini_inf.gravity = player.child("gravity").attribute("value").as_float();
	p_ini_inf.pathfinding_distance.x = player.child("pathfinding_distance.x").attribute("value").as_float();
	p_ini_inf.pathfinding_distance.y = player.child("pathfinding_distance.y").attribute("value").as_float();

	//Load Ground enemies initial viariables
	pugi::xml_node ground_enemy = conf.child("ground_enemy");

	ge_ini_inf.jump_time = ground_enemy.child("jump_time").attribute("value").as_int();
	ge_ini_inf.speed_modifier.x = ground_enemy.child("Genemy_speed_modifier.x").attribute("value").as_float();
	ge_ini_inf.speed_modifier.y = ground_enemy.child("Genemy_speed_modifier.y").attribute("value").as_float();
	ge_ini_inf.gravity = ground_enemy.child("gravity").attribute("value").as_float();

	//Load Air enemies initial variables
	pugi::xml_node air_enemy = conf.child("air_enemy");

	fe_ini_inf.agro_distance = air_enemy.child("agro_distance").attribute("value").as_int();
	fe_ini_inf.idle_speed = air_enemy.child("idle_speed").attribute("value").as_int();
	fe_ini_inf.side_fly_time = air_enemy.child("side_fly_time").attribute("value").as_float();
	fe_ini_inf.speed_modifier.x = air_enemy.child("speed_modifier.x").attribute("value").as_float();
	fe_ini_inf.speed_modifier.y = air_enemy.child("speed_modifier.y").attribute("value").as_float();
	fe_ini_inf.tired_distance = air_enemy.child("tired_distance").attribute("value").as_int();

	return true;
}

bool j1Entities::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	enemy_sprites = App->tex->Load("textures/Enemy_sprites.png");
	player_sprites = App->tex->Load("textures/SpriteSheet.png");

	//Shouldn't be loading here
	App->map->bone_graphics = App->tex->Load("textures/BONE.png");
	App->scene->win_screen = App->tex->Load("textures/WinScreen.png");

	AddEntity(ENTITY_TYPES::PLAYER, App->map->data.player_starting_value.x, App->map->data.player_starting_value.y);

	return true;
}

// Called before render is available
bool j1Entities::Update(float dt)
{
	// Manage entities' physics
	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr && (entities[i]->type == ENTITY_TYPES::PLAYER || entities[i]->type == ENTITY_TYPES::GROUND_ENEMY))
			entities[i]->ManagePhysics(dt);
	}

	if (player != nullptr)
		player->ManagePhysics(dt);

	// Update all entities
		for (uint i = 0; i < entities.count(); ++i)
		{ 
			if (entities[i] != nullptr)
				entities[i]->Update(dt, do_logic.IsOver());
		}

	if (player != nullptr)
		player->Update(dt);
	    

	// Draw all entities
	for (uint i = 0; i < entities.count(); ++i)
	{ 
		if (entities[i] != nullptr)
			entities[i]->Draw(enemy_sprites);
	}

	if (player != nullptr)
	{ 
		player->WinScreen(dt); //Provisional
		player->Draw(player_sprites);
	}

	//Update enemies logic every 0.5 seconds
	if (do_logic.IsOver())
		do_logic.Start(0.5);

	return true;
}

// Called before quitting
bool j1Entities::CleanUp()
{
	LOG("Freeing all entities");

	App->tex->UnLoad(player_sprites);
	App->tex->UnLoad(enemy_sprites);

	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}		
    delete player;
	player = nullptr;

	return true;
}
void j1Entities::Add_waiting_entity(ENTITY_TYPES type, int x, int y)
{
	Entity_info enemy_info;
	enemy_info.position.x = x;
	enemy_info.position.y = y;
	enemy_info.type = type;
	waiting_queue.Push(enemy_info, 0);
}

void j1Entities::Spawn_waiting_entities()
{
	if(waiting_queue.Count() != 0)
	{ 
		for (int i = 0; i < waiting_queue.Count(); i++)
		{
			Entity_info enemy_info = *waiting_queue.Peek(i);
			AddEntity(enemy_info.type, enemy_info.position.x, enemy_info.position.y);
		}
	}
}

void j1Entities::Clear_waiting_list()
{
	waiting_queue.Clear();
}

void j1Entities::AddEntity(ENTITY_TYPES type, int x, int y)
{
	switch(type){
		case ENTITY_TYPES::AIR_ENEMY: 
		{
			Entity* new_ent = new AirEnemy(x, y, fe_ini_inf);
			entities.add(new_ent);
			break;
		}
		
		case ENTITY_TYPES::GROUND_ENEMY:
		{
			GroundEnemy* new_ent = new GroundEnemy(x, y, ge_ini_inf);
			entities.add(new_ent);
			break;
		}

		case ENTITY_TYPES::PLAYER:
		{
			Player* new_ent = new Player(x, y, p_ini_inf);
			player = new_ent;
			break;
		}
	}
}

void j1Entities::OnCollision(Collider* c1, Collider* c2) 
{
    // Once the collision module is fixed, it will call this function whenever an enemy and the player collide. C1 will be the entity collider
	// and c2 one which has collided. This module will compare c1 with the colliders of all the entities, and call the virtual "OnCollision" method of
	// the entity that has the same collider
	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{ 
			if(entities[i]->GetCollider() == c1)
			{ 
			    entities[i]->OnCollision(c2);
				break;
			}
		}
	}

	if (player != nullptr)
	{ 
		if(player->GetCollider() == c1)
			player->OnCollision(c2);
	}

}


void j1Entities::EraseEntities()
{
	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->collider->to_delete = true;
			delete entities[i];
			entities[i] = nullptr;
		}
	}
	entities.clear();
}

//Load game state
bool j1Entities::Load(pugi::xml_node& data)
{
	if (App->map->map == data.child("player").attribute("map").as_int())
	{
		Load_entities(data);
	}
	else
	{
		if (App->map->map == 0)
		{
			App->scene->Change_to_map(1);
			Load_entities(data);
		}
		else
		{
			App->scene->Change_to_map(0);
			Load_entities(data);
		}
	}

	return true;
}

// Save Game State
bool j1Entities::Save(pugi::xml_node& data) const
{
	pugi::xml_node player_ = data.append_child("player");

	player->Save(player_);

	pugi::xml_node enemies = data.append_child("enemies");
	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{
			if(entities[i]->type == AIR_ENEMY)
			{ 
				pugi::xml_node air_enemy = enemies.append_child("air_enemy");
				entities[i]->Save(air_enemy);
			}
			else if (entities[i]->type == GROUND_ENEMY)
			{
				pugi::xml_node ground_enemy = enemies.append_child("ground_enemy");
				entities[i]->Save(ground_enemy);
			}
		}
	}
	
	return true;
}
void j1Entities::Load_entities(pugi::xml_node& data)
{
	pugi::xml_node player_ = data.child("player");
	player->Load(player_);

	pugi::xml_node entity_iterator = data.child("enemies").first_child();
	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->type == AIR_ENEMY)
			{
				entities[i]->Load(entity_iterator);
			}
			else if (entities[i]->type == GROUND_ENEMY)
			{
				entities[i]->Load(entity_iterator);
			}
			entity_iterator = entity_iterator.next_sibling();
		}

	}
}