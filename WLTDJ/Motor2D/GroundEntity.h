#pragma once
#include "Entity.h"
class GroundEntity : public Entity
{
public:
	GroundEntity(int, int);
	~GroundEntity();

	float gravity;
	fPoint contact;
	int jump_time;
};

