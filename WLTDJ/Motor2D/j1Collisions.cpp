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
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
			// skip empty and player colliders
			if (colliders[i] == nullptr || colliders[i]->type == COLLIDER_NONE || colliders[i]->type == COLLIDER_PLAYER)
				continue;

			if (colliders[i]->type == COLLIDER_WALL || ((colliders[i]->type == COLLIDER_PIT || colliders[i]->type == COLLIDER_DEADLY) && App->player->godmode))
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
						if (colliders[i]->type == COLLIDER_DEADLY && !App->player->godmode)
						{
							App->player->dead = true;
						}
						else if (colliders[i]->type == COLLIDER_BONE)
						{
							if(App->map->map == 0)
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
	}

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

void Collider::WillCollide(const SDL_Rect& r, int speed_x, int speed_y, int gravity, float dt)
{
	speed_x *= dt;
	speed_y *= dt;
	gravity *= dt;

	if (r.y + r.h > rect.y && r.y < rect.y + rect.h && r.x < rect.x + rect.w + ceil(speed_x * 2) && r.x + r.w > rect.x) // Will collide left
		App->player->contact.x = 1;
	if (r.y + r.h > rect.y && r.y < rect.y + rect.h && r.x + r.w > rect.x - ceil(speed_x * 2) && r.x < rect.x + rect.w) // Will collide right
		App->player->contact.x = 2;
	if (r.y < rect.y + rect.h && r.y + r.h > rect.y - ceil(gravity * 2) && r.x + r.w > rect.x && r.x < rect.x + rect.w) // Will collide ground
		App->player->contact.y = 1;
	if (r.y + r.h > rect.y && r.y < rect.y + rect.h + ceil(speed_y * 2) && r.x + r.w > rect.x && r.x < rect.x + rect.w) // Will collide top
		App->player->contact.y = 2;
}

bool j1Collisions::WillCollideAfterSlide(const SDL_Rect& r, int distance, float dt) const
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty and player colliders
		if (colliders[i] == nullptr || colliders[i]->type == COLLIDER_NONE || colliders[i]->type == COLLIDER_PLAYER)
			continue;

		distance *= dt;

		if ((colliders[i]->type == COLLIDER_WALL || ((colliders[i]->type == COLLIDER_PIT || colliders[i]->type == COLLIDER_DEADLY) && App->player->godmode))
			&& r.y + r.h > colliders[i]->rect.y && r.y < colliders[i]->rect.y + colliders[i]->rect.h + ceil(distance * 2)
			&& r.x + r.w > colliders[i]->rect.x && r.x < colliders[i]->rect.x + colliders[i]->rect.w)
			return true;
	}

	return false;
}