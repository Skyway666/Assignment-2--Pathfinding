#ifndef __j1COLLISIONS_H__
#define __j1COLLISIONS_H__

#define MAX_COLLIDERS 10000

#include "j1Module.h"
#include "p2Log.h"
#include "GroundEntity.h"


#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_BONE,
	COLLIDER_DEADLY,
	COLLIDER_PLAYER,
	COLLIDER_PIT,
	COLLIDER_MAX,
	COLLIDER_SUPER_GOD,
	COLLIDER_GOD,
	COLLIDER_ENEMY
};

class Player;

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	void SetSize(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}

	bool CheckCollision(const SDL_Rect& r) const;
	void WillCollide(GroundEntity* entity, float dt); // Detects if the entity is going to collide and returns the corresponding contact
	void WillCollidePit(GroundEntity* entity, float dt); // Enemy jumps if not falling and is on top of a pit
};

class j1Collisions : public j1Module
{
public:

	j1Collisions();
	~j1Collisions();

	bool Update(float dt);
	bool PreUpdate();
	bool CleanUp();
	void Erase_Non_Player_Colliders();

	bool WillCollideAfterSlide(Player* entity, float dt) const; // Checks if any rectangle would be colliding with the ceiling
	void ManageGroundCollisions(GroundEntity* entity, float dt); // Allows ground entities to react to environment's walls
	void EnemyJump(GroundEntity* entity, float dt); // To detect if the enemy has to jump
	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);

	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __j1COLLISIONS_H__