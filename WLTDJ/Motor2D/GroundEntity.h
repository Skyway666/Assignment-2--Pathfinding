#pragma once
#include "Entity.h"
class GroundEntity : public Entity
{
public:
	GroundEntity(int, int);
	~GroundEntity();

	fPoint contact;
	fPoint speed_modifier;
	float gravity;
	float gravity2;

};

