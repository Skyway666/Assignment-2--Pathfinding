#include "Coins.h"
#include "j1Textures.h"
#include "j1Scene.h"



Coins::Coins(int x, int y) : Entity(x, y)
{
	position.x = x;
	position.y = y;

	scale = 0.3;
	type = ENTITY_TYPES::COIN;

	anim.PushBack({ 32, 0, 147, 405 });
	anim.PushBack({ 261, 0, 147, 405 });
	anim.PushBack({ 484, 0, 212, 405 });

	anim.speed = 0.2;
	int W = anim.GetCurrentFrame().w * scale;
	int H = anim.GetCurrentFrame().h * scale;
	collider = App->collision->AddCollider({ x, y, W, H }, COLLIDER_COIN, App->entities);

	animation = &anim;
}


Coins::~Coins()
{
}


void Coins::Update(float dt, bool dologic)
{
	if (given_points && !App->pause)
	{
		scale -= 0.01;
		position.y -= 20;
		position.x -= 24;
		collider->SetPos(position.x, position.y);
		
		if (!pa_started)
		{
			play_animation.Start(0.5);
			pa_started = true;
		}
		if (play_animation.IsOver() && !animation_played)
		{
			App->scene->coin_animation = true;
			animation_played = true;
			App->entities->EraseEntity(this);
		}
	}

	animation->speed = 0.2 * dt;
}

void Coins::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER || collider->type == COLLIDER_GOD || collider->type == COLLIDER_SUPER_GOD)
	{
		if (!given_points)
		{
			App->entities->player->points++;
			given_points = true;
		}
	}
}

void Coins::Pause()
{
	animation->Reset();
	play_animation.Pause();
}

void Coins::Resume()
{
	play_animation.StartAfterPause();
	play_animation.ResetPause();
}

void Coins::Save(pugi::xml_node& data)
{
	data.append_attribute("x") = position.x;
	data.append_attribute("y") = position.y;
	data.append_attribute("collected") = collected;
	data.append_attribute("given_points") = given_points;
	data.append_attribute("pa_started") = pa_started;
	data.append_attribute("animation_played") = animation_played;

	play_animation.Save();
}

void Coins::Load(pugi::xml_node& data)
{
	position.x = data.attribute("x").as_int();
	position.y = data.attribute("y").as_int();
	collected = data.attribute("collected").as_bool();
	given_points = data.attribute("given_points").as_bool();
	pa_started = data.attribute("pa_started").as_bool();
	animation_played = data.attribute("animation_played").as_bool();

	play_animation.Load();
}