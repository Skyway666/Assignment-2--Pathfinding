#pragma once
#include "Entity.h"
class GroundEntity : public Entity
{
public:
	GroundEntity(int, int);
	~GroundEntity();

	float gravity;
	fPoint contact;
	bool jumping = false;
	int jump_time;
	// Will eventually replace them:
	int frames = 0;
	int time = 0;
	bool allowtime = true;

	// should not be here:
	float jumping_multiplier = 1;
	bool front_of_pit = false;
	bool turn = false;

	virtual void Jump(float dt) {};
};