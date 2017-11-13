#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collisions.h"
#include "j1Player.h"
#include "j1Map.h"
#include "Pathfinding.h"

j1Collisions::j1Collisions()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BONE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DEADLY] = true;
}

// Destructor
j1Collisions::~j1Collisions()
{}



bool j1Collisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

// Called before render is available
bool j1Collisions::Update(float dt)
{
	/*for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			// skip empty and player colliders
			if (colliders[i] == nullptr || colliders[i]->type == COLLIDER_NONE || colliders[i]->type == COLLIDER_PLAYER)
				continue;

			if (App->player->collider->type != COLLIDER_SUPER_GOD && colliders[i]->type == COLLIDER_WALL || ((colliders[i]->type == COLLIDER_PIT || colliders[i]->type == COLLIDER_DEADLY) && App->player->collider->type == COLLIDER_GOD))
			{
				colliders[i]->WillCollide(App->player->collider->rect, App->player->speed_modifier.x, (App->player->speed_modifier.y), (App->player->gravity), dt);
				if (App->player->collider->CheckCollision(colliders[i]->rect))
				{
					if (App->player->flip && !App->player->walljumping)
						App->player->position.x += App->player->speed_modifier.x * dt;
					else if (!App->player->flip && !App->player->walljumping)
						App->player->position.x -= App->player->speed_modifier.x * dt;
					else if (App->player->walljumping && App->player->speed.x > 0)
						App->player->position.x -= App->player->speed_modifier.x * dt;
					else if (App->player->walljumping && App->player->speed.x < 0)
						App->player->position.x += App->player->speed_modifier.x * dt;
				}
			}
			else if (colliders[i]->type == COLLIDER_BONE || colliders[i]->type == COLLIDER_DEADLY)
			{
				if (App->player->collider->CheckCollision(colliders[i]->rect))
				{

					if (matrix[App->player->collider->type][colliders[i]->type])
					{
						if (App->player->collider->type != COLLIDER_SUPER_GOD && App->player->collider->type != COLLIDER_GOD && colliders[i]->type == COLLIDER_DEADLY)
						{
							App->player->dead = true;
						}
						else if (colliders[i]->type == COLLIDER_BONE)
						{
							if (App->map->map == 0)
							{
								App->collision->Erase_Non_Player_Colliders();
								App->map->CleanUp();
								App->map->Load("Level 2 final.tmx");
								App->map->map = 1;
								App->pathfinding->SetMap();
							}
							else if (App->map->map == 1)
							{
								App->collision->Erase_Non_Player_Colliders();
								App->map->CleanUp();
								App->map->Load("Level 1 final.tmx");
								App->map->map = 0;
								App->player->win = true;
							}
						}
					}

				}
			}
		}*/


	DebugDraw();

	return true;
}

void j1Collisions::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha, false);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha, false);
			break;
		case COLLIDER_GOD: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha, false);
			break;
		case COLLIDER_SUPER_GOD: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha, false);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha, false);
			break;
		case COLLIDER_PIT: // pink
			App->render->DrawQuad(colliders[i]->rect, 243, 64, 147, alpha, false);
			break;
		case COLLIDER_DEADLY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha, true);
			break;
		case COLLIDER_BONE: 
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha, true);
			break;
		}
	}
}

// Called before quitting
bool j1Collisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collisions::AddCollider(SDL_Rect rect, COLLIDER_TYPE type)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type);
			break;
		}
	}

	return ret;
}

void j1Collisions::Erase_Non_Player_Colliders()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->type != COLLIDER_PLAYER)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if (r.y + r.h > rect.y && r.y < rect.y + rect.h && r.x + r.w > rect.x && r.x < rect.x + rect.w)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void Collider::WillCollide(Entity* entity, float dt)
{
	SDL_Rect r = entity->collider->rect;
	fPoint speed = entity->speed_modifier;
	float gravity = entity->gravity;
	speed.x *= dt;
	speed.y *= dt;
	gravity *= dt;

	if (r.y + r.h > rect.y && r.y < rect.y + rect.h && r.x < rect.x + rect.w + ceil(speed.x * 2) && r.x + r.w > rect.x) // Will collide left
		entity->contact.x = 1;
	if (r.y + r.h > rect.y && r.y < rect.y + rect.h && r.x + r.w > rect.x - ceil(speed.x * 2) && r.x < rect.x + rect.w) // Will collide right
		entity->contact.x = 2;
	if (r.y < rect.y + rect.h && r.y + r.h > rect.y - ceil(gravity * 2) && r.x + r.w > rect.x && r.x < rect.x + rect.w) // Will collide ground
		entity->contact.y = 1;
	if (r.y + r.h > rect.y && r.y < rect.y + rect.h + ceil(speed.y * 2) && r.x + r.w > rect.x && r.x < rect.x + rect.w) // Will collide top
		entity->contact.y = 2;
}

bool j1Collisions::WillCollideAfterSlide(Entity* entity, float dt) const
{
	SDL_Rect r = entity->collider->rect;
	float speed = entity->speed_modifier.y;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty and player colliders
		if (colliders[i] == nullptr || colliders[i]->type == COLLIDER_NONE || colliders[i]->type == COLLIDER_PLAYER)
			continue;

		speed *= dt;

		if ((colliders[i]->type == COLLIDER_WALL || ((colliders[i]->type == COLLIDER_PIT || colliders[i]->type == COLLIDER_DEADLY) && entity->collider->type == COLLIDER_GOD))
			&& r.y + r.h > colliders[i]->rect.y && r.y < colliders[i]->rect.y + colliders[i]->rect.h + ceil(speed)
			&& r.x + r.w > colliders[i]->rect.x && r.x < colliders[i]->rect.x + colliders[i]->rect.w)
			return true;
	}

	return false;
}

void j1Collisions::ManageGroundCollisions(Entity* entity, float dt)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty and non-wall colliders
		if (colliders[i] == nullptr || colliders[i]->type == COLLIDER_NONE || colliders[i]->type == COLLIDER_PLAYER || colliders[i]->type == COLLIDER_BONE
			|| colliders[i]->type == COLLIDER_ENEMY || colliders[i]->type == COLLIDER_GOD || colliders[i]->type == COLLIDER_SUPER_GOD)
			continue;

		if (entity->collider->type != COLLIDER_SUPER_GOD && (colliders[i]->type == COLLIDER_WALL || ((colliders[i]->type == COLLIDER_PIT || colliders[i]->type == COLLIDER_DEADLY) && entity->collider->type == COLLIDER_GOD)))
		{
			colliders[i]->WillCollide(entity, dt);

			if (entity->collider->CheckCollision(colliders[i]->rect)) // In case the entity somehow passes thorugh a wall
			{
				if (entity->collider->type == COLLIDER_PLAYER)
				{
					if (entity->flip && !App->player->walljumping)
						entity->position.x += entity->speed_modifier.x * dt;
					else if (!entity->flip && !App->player->walljumping)
						entity->position.x -= entity->speed_modifier.x * dt;
					else if (App->player->walljumping && App->player->speed.x > 0)
						entity->position.x -= entity->speed_modifier.x * dt;
					else if (App->player->walljumping && App->player->speed.x < 0)
						entity->position.x += entity->speed_modifier.x * dt;
				}
				else
				{
					if (entity->flip)
						entity->position.x += entity->speed_modifier.x * dt;
					else if (!entity->flip)
						entity->position.x -= entity->speed_modifier.x * dt;
				}
			}
		}
	}
}