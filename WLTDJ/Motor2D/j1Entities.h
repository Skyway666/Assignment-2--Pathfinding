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

class Entity;

class j1Entities : public j1Module
{
public:

	j1Entities();
	~j1Entities();

	bool Start(); //Load enemy textures
	bool Update(float dt); //Update all entities in "entities"
	bool CleanUp(); //Called when app is closed
	void EraseEntities(); //To erase all entities left on the map
	void OnCollision(Collider* c1, Collider* c2); //Called by the callback of "j1Collisions", should iterate over all entities and call their OnCollision method if the collider is theirs
	bool AddEntity(ENTITY_TYPES type, int x, int y); //Adds an enemy to the list with a certain type and position (should return a pointer to the enemy)

private:

	p2List<Entity*> entities;
	SDL_Texture* sprites = nullptr;

};

#endif // __j1ENTITIES_H__