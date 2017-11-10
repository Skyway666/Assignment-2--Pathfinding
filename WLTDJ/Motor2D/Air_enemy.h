#pragma once
#include "Entity.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "Pathfinding.h"

class Air_enemy : public Entity
{
public:
	Air_enemy(int x, int y);
	~Air_enemy();

	void Update();
	void OnCollision();
};

