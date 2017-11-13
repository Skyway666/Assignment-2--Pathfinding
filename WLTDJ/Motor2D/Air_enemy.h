#pragma once
#include "Entity.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "Pathfinding.h"
#include "j1Entities.h"
#include "Animation.h"

class Air_enemy : public Entity
{
public:
	Air_enemy(int x, int y);
	~Air_enemy();
	Animation idle;

	void Update(float dt);
	void OnCollision();
	void Exec_idle();
	void Exec_atack();
	void Find_path();
private:
	
	int ideling_heigh;

	bool is_idle;
	
};

