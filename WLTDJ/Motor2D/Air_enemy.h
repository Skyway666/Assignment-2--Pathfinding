#pragma once
#include "Entity.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "Pathfinding.h"
#include "j1Entities.h"
#include "Animation.h"
#include "Cronometer.h"
#include "Player.h"

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
	
	float side_fly_time; //Time that the enemy spends flying from one side to the other
	int ideling_heigh; //Height at which the enemy has to retrun to idle
	bool is_idle = true; //bool to know when the enemy should stop ideling and follow the player
	Cronometer side_fly_timer; //Timer to mesure when enemy should be moving
	p2DynArray<iPoint>* path_to_follow;//Path that the enemy must follow
	int next_tile; //Tile that the enemy has to reach
	int idle_speed = 2; //speed at which the enemy idles


	iPoint center;
	
};

