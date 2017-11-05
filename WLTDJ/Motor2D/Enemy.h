#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
//#include "Path.h" (pathfinding)

struct SDL_Texture;
struct Collider;

class Enemy //: public Path
{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;

public:
	fPoint position;
	float scale = 1;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
};

#endif // __ENEMY_H__