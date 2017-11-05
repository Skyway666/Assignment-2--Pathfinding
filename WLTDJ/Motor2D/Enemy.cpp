#include "j1App.h"
#include "Enemy.h"
#include "j1Collisions.h"
#include "j1Render.h"

Enemy::Enemy(int x, int y) : position(x, y)
{

}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, scale, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{


}