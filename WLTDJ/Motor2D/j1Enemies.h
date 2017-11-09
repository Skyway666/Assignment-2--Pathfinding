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

	int bossmain;
	int counter = 0;
	bool Init();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();
	void EraseEnemies();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(int path, ENEMY_TYPES type, int x, int y);
	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites = nullptr;

};

#endif // __j1ENEMIES_H__