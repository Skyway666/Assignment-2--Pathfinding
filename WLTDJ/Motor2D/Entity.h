#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

//Parent class to all the entities

struct SDL_Texture;
struct Collider;

class Entity //: public Path
{
protected:
	Animation* animation;
	Collider* collider = nullptr;

public:
	fPoint position;
	float scale;

public:
	Entity(int x, int y);
	virtual ~Entity();

	const Collider* GetCollider() const;
	
	void Draw(SDL_Texture* sprites); //Draw and update collider position

	virtual void Update() {}; //Update enemy logic
	virtual void ManagePhysics() {};//Manage Physics of grounded enemies
	virtual void OnCollision(Collider* collider){}; //Every entity has its own "OnCollision"
};

#endif // __ENEMY_H__