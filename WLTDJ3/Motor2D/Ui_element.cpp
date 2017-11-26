#include "Ui_element.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"



Ui_element::Ui_element(int x, int y)
{
	position.x = x;
	position.y = y;
}


Ui_element::~Ui_element()
{

}

void Ui_element::Draw(SDL_Texture* sprite)
{
	if (animation != nullptr)
	{
		App->render->Blit(sprite, position.x, position.y, 1, false, &(animation->GetCurrentFrame()));
	}
}