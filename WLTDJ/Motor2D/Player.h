#pragma once
#include "Entity.h"
#include "Animation.h"
#include "j1Collisions.h"
#include "p2Point.h"
#include "j1Entities.h"
#include "j1Collisions.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Scene.h"
class Player : public Entity
{
public:
	Player(int x, int y, Player_Initial_Inf initial_inf);
	~Player();
	
	void Update(float dt);	




private:

	void WallSlide();
	void Jump();
	void Slide();

	void Animation_Loading();
	SDL_Rect rect_after_sliding;	
	int frames = 0;
	int time = 0;
	bool allowtime = true;


	float player_height_before_sliding;
	bool jumping = false;
	bool walljumping = false;
	bool flip = false;
	bool StickToWall = false;
	bool dead = false;
	bool sliding = false;
	bool win = false;
	bool godmode = false;
	bool super_godmode = false;
	int jcontact = 0; // for Jump() function

	iPoint contact; // y = 0 -> none, y = 1 -> ground, y = 2 -> ceiling /// x = 0 -> none, x = 1 -> left, x = 2 -> right
	fPoint speed;
	fPoint position;
	iPoint sprite_distance;
	fPoint speed_modifier;
	fPoint walljump_speed;
	float player_dt;
	float gravity;
	float player_x_displacement;
	int jump_time;
	int slide_time;
	int walljump_time;

	Animation idle;
	Animation run;
	Animation jump;
	Animation fall;
	Animation death;
	Animation slide;
	Animation wallslideright;
	Animation wallslideleft;
};
