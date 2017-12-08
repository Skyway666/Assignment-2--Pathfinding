#include "Coins.h"
#include "j1Textures.h"



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
	if (given_points)
	{
		scale -= 0.01;
		position.y -= 20;
		position.x -= 24;
		collider->SetPos(position.x, position.y);
	}
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

}

void Coins::Resume()
{

}

void Coins::Save(pugi::xml_node& data)
{

}

void Coins::Load(pugi::xml_node& data)
{

}