#pragma once
#include "Entity.h"
class GroundEntity : public Entity
{
public:
	GroundEntity(int, int);
	~GroundEntity();

	float gravity;
	iPoint contact;
	bool jumping = false;
	int jump_time;
	// Will eventually replace them:
	int frames = 0;
	int time = 0;
	bool allowtime = true;

	virtual void Jump(float dt) {};
};