#include "Ui_element.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "ClickManager.h"




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
	collider->SetPos(position.x, position.y);

	if (animation != nullptr)
	{
		App->render->Blit(sprite, position.x, position.y, 1, false, &(animation->GetCurrentFrame()));
	}
}

void Ui_element::Link_ui_element(Ui_element* element, int offset_x, int offset_y)
{
	element->position.x = position.x + offset_x;
	element->position.y = position.y + offset_y;

	linked_elements.add(element);
}