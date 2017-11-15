#pragma once
#ifndef __j1ENTITIES_H__
#define __j1ENTITIES_H__

#include "j1Module.h"
#include "j1Collisions.h"
#include "p2List.h"



enum ENTITY_TYPES
{
	PLAYER,
	GROUND_ENEMY,
	AIR_ENEMY
};

struct Player_Initial_Inf
{
	fPoint speed_modifier;
	fPoint walljump_speed;
	float gravity;
	int jump_time;
	int slide_time;
	int walljump_time;
};

struct Flying_Enemy_Initial_Inf
{

};
struct Ground_Enemy_Initial_Inf
{
	fPoint speed_modifier;
	float gravity;
	int jump_time;
};

class Entity;

class j1Entities : public j1Module
{
public:

	j1Entities();
	~j1Entities();

	bool Awake(pugi::xml_node& conf); //Load initial information of all entities
	bool Start(); //Load enemy textures
	bool Update(float dt); //Update all entities in "entities"
	bool CleanUp(); //Called when app is closed
	void EraseEntities(); //To erase all entities left on the map
	void OnCollision(Collider* c1, Collider* c2); //Called by the callback of "j1Collisions", should iterate over all entities and call their OnCollision method if the collider is theirs
	bool AddEntity(ENTITY_TYPES type, int x, int y); //Adds an enemy to the list with a certain type and position (should return a pointer to the enemy... or not)
	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	Player* player = nullptr; //Really special entity

private:

	p2List<Entity*> entities;
	SDL_Texture* sprites = nullptr;
	SDL_Texture* player_sprites = nullptr;

	Player_Initial_Inf p_ini_inf;
	Flying_Enemy_Initial_Inf fe_ini_inf;
	Ground_Enemy_Initial_Inf ge_ini_inf;

};


#endif // __j1ENTITIES_H__