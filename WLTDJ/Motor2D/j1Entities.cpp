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
	p_ini_inf.jump_time = conf.child("jump_time").attribute("value").as_int();
	p_ini_inf.slide_time = conf.child("slide_time").attribute("value").as_int();
	p_ini_inf.walljump_time = conf.child("walljump_time").attribute("value").as_int();
	p_ini_inf.speed_modifier.x = conf.child("speed_modifier.x").attribute("value").as_float();
	p_ini_inf.speed_modifier.y = conf.child("speed_modifier.y").attribute("value").as_float();
	p_ini_inf.walljump_speed.y = conf.child("walljump_speed.y").attribute("value").as_float();
	p_ini_inf.walljump_speed.x = conf.child("walljump_speed.x").attribute("value").as_float();
	p_ini_inf.gravity = conf.child("gravity").attribute("value").as_float();

	ge_ini_inf.jump_time = conf.child("jump_time").attribute("value").as_int();
	ge_ini_inf.speed_modifier.x = conf.child("Genemy_speed_modifier.x").attribute("value").as_float();
	ge_ini_inf.speed_modifier.y = conf.child("speed_modifier.y").attribute("value").as_float();
	ge_ini_inf.gravity = conf.child("gravity").attribute("value").as_float();

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
		player->Draw(player_sprites);

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
			Entity* new_ent = new AirEnemy(x, y);
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
			delete entities[i];
			entities[i] = nullptr;
		}
	}
}

//Load and save functions
bool j1Entities::Load(pugi::xml_node& data)
{
	if (App->map->map == data.child("player_position").attribute("map").as_int())
	{
		player->position.x = data.child("player_position").attribute("x").as_float();
		player->position.y = data.child("player_position").attribute("y").as_float() - player->gravity * 2;
	}
	else
	{
		if (App->map->map == 0)
		{
			App->scene->Change_to_map(1);
			player->position.x = data.child("player_position").attribute("x").as_float();
			player->position.y = data.child("player_position").attribute("y").as_float() - player->gravity * 2;
		}
		else
		{
			App->scene->Change_to_map(0);
			player->position.x = data.child("player_position").attribute("x").as_float();
			player->position.y = data.child("player_position").attribute("y").as_float() - player->gravity * 2;
		}
	}

	return true;
}

// Save Game State
bool j1Entities::Save(pugi::xml_node& data) const
{
	pugi::xml_node player_ = data.append_child("player_position");

	player_.append_attribute("x") = player->position.x;
	player_.append_attribute("y") = player->position.y;
	player_.append_attribute("map") = App->map->map;

	return true;
}