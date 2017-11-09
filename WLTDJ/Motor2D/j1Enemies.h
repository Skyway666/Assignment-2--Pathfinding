#pragma once
#ifndef __j1ENEMIES_H__
#define __j1ENEMIES_H__

#include "j1Module.h"
#include "j1Collisions.h"

#define MAX_ENEMIES 10000


enum ENEMY_TYPES
{
	NO_TYPE
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
};

class j1Enemies : public j1Module
{
public:

	j1Enemies();
	~j1Enemies();

	bool Start(); //Load enemy textures
	bool PreUpdate(); //Potentially decide what enemies to spawn
	bool Update(); //Update all enemies in "enemies"
	bool PostUpdate(); //Potentially check camera position to decide what to despawn
	bool CleanUp(); //Called when app is closed
	void EraseEnemies(); //To erase all enemies left on the map
	void OnCollision(Collider* c1, Collider* c2); //Called by the callback of "j1Collisions", should iterate over all enemies and call their OnCollision method if the collider is theirs
	bool AddEnemy(int path, ENEMY_TYPES type, int x, int y); //Adds an enemy to the list with a certain type and position || Potentially to the queue
	void SpawnEnemy(const EnemyInfo& info); //Potencially spawns an enemy of the queue

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites = nullptr;

};

#endif // __j1ENEMIES_H__