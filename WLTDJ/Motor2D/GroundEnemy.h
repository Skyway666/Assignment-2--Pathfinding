#pragma once
#include "Entity.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "Pathfinding.h"
#include "j1Entities.h"
#include "Animation.h"
#include "Player.h"
#include "GroundEntity.h"
#include "Cronometer.h"


class GroundEnemy : public GroundEntity
{
public:
	GroundEnemy(int x, int y, Ground_Enemy_Initial_Inf initial_inf);
	~GroundEnemy();
	Animation idle;

	void Update(float dt);
	void OnCollision();
	void Exec_idle();
	void Exec_atack();
	void Find_path();
	void ManagePhysics(float dt);

private:

	void Jump(float dt);

	float walk_time; // Time that the enemy spends walking from one side to the other
	bool is_idle = true; // bool to know when the enemy should stop ideling and follow the player
	Cronometer walk_timer; // Timer to mesure when enemy should be moving
	p2DynArray<iPoint>* path_to_follow; // Path that the enemy must follow
	int next_tile; // Tile that the enemy has to reach
	int idle_speed; // speed at which the enemy idles
	bool debug = false; // Provisional

	iPoint center; // Maybe should have a function to get the center

};