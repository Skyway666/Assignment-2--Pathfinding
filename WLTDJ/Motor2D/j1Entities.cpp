#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Entities.h"
#include "j1Textures.h"
#include "Entity.h"
#include "j1Map.h"
#include "j1Audio.h"
#include "p2Log.h"
#include "Air_enemy.h"
#define SPAWN_MARGIN 100

j1Entities::j1Entities()
{
	name.create("entities");
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
	p_ini_inf.speed_modifier.y = conf.child("speed_modifier.y").attribute("value").as_float();
	p_ini_inf.speed_modifier.x = conf.child("speed_modifier.x").attribute("value").as_float();
	p_ini_inf.walljump_speed.y = conf.child("walljump_speed.y").attribute("value").as_float();
	p_ini_inf.walljump_speed.x = conf.child("walljump_speed.x").attribute("value").as_float();
	p_ini_inf.gravity = conf.child("gravity").attribute("value").as_float();


	return true;
}
bool j1Entities::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->tex->Load("textures/Flying Monster/frame-1.png");

	return true;
}

// Called before render is available
bool j1Entities::Update(float dt)
{
	//Update all entities
	for (uint i = 0; i < entities.count(); ++i)
		if (entities[i] != nullptr) entities[i]->Update(dt);

	//Draw all entities
	for (uint i = 0; i < entities.count(); ++i)
		if (entities[i] != nullptr)
		{
				entities[i]->Draw(sprites);
		}

	return true;
}

// Called before quitting
bool j1Entities::CleanUp()
{
	LOG("Freeing all entities");

	App->tex->UnLoad(sprites);

	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}

	return true;
}

bool j1Entities::AddEntity(ENTITY_TYPES type, int x, int y)
{
	switch(type){
		case ENTITY_TYPES::AIR_ENEMY: 
		{
			Entity* new_ent = new Air_enemy(x, y);
			entities.add(new_ent);
		}
		case ENTITY_TYPES::GROUND_ENEMY:
		{

		}
		case ENTITY_TYPES::PLAYER:
		{

		}
	}
	return true;
}

void j1Entities::OnCollision(Collider* c1, Collider* c2) 
{
    // Once the collision module is fixed, it will call this function whenever enemy and player collides. C1 will be the entity collider
	// and c2 one which has collided. This module will compare c1 with the colliders of all the entities, and call the virtual "OnCollision" method of
	// the entity that has the same collider
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