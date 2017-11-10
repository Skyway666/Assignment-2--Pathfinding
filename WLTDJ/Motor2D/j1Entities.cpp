#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Entities.h"
#include "j1Textures.h"
#include "Enemy.h"
#include "j1Map.h"
#include "j1Audio.h"
#include "p2Log.h"
#define SPAWN_MARGIN 100

j1Entities::j1Entities()
{

}

// Destructor
j1Entities::~j1Entities()
{
}

bool j1Entities::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	// sprites = App->tex->Load("assets/ ENEMY SPRITE SHEET HERE.png");

	return true;
}

// Called before render is available
bool j1Entities::Update(float dt)
{
	/*for (uint i = 0; i < MAX_ENTITIES; ++i)
		if (entities[i] != nullptr) entities[i]->Move();

	for (uint i = 0; i < MAX_ENTITIES; ++i)
		if (entities[i] != nullptr)
		{
				entities[i]->Draw(sprites);
		}*/
	return true;
}

// Called before quitting
bool j1Entities::CleanUp()
{
	/*LOG("Freeing all entities");

	App->tex->UnLoad(sprites);

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}
*/
	return true;
}

bool j1Entities::AddEnemy(ENTITY_TYPES type, int x, int y)
{

	return true;
}

void j1Entities::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{

	}
}


void j1Entities::EraseEntities()
{
	//for (uint i = 0; i < MAX_ENTITIES; ++i)
	//{
	//	if (entities[i] != nullptr)
	//	{
	//		delete entities[i];
	//		entities[i] = nullptr;
	//	}
	//}
}