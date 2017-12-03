#include "Ui_element.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "ClickManager.h"
#include "j1Input.h"




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
	if(collider != nullptr)
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
	element->offset.x = offset_x;
	element->offset.y = offset_y;

	linked_elements.add(element);
}

void Ui_element::Update()
{
	//Move object if gripped
	iPoint mouse_position;
	App->input->GetMousePosition(mouse_position.x, mouse_position.y);
	iPoint mouse_displacement;
	if (gripped && !mouse_pos_gotten)
	{
		mouse_pos_when_grip = mouse_position;
		pos_when_grip = position;
		mouse_pos_gotten = true;
	}
	mouse_displacement = mouse_position - mouse_pos_when_grip;
	if (gripped)
	{
		position = pos_when_grip + mouse_displacement;
	}
	if (!gripped && mouse_pos_gotten)
	{
		mouse_pos_gotten = false;
		offset += mouse_displacement;
	}

	//Update position of all linked objects to match parent
	for (int i = 0; i < linked_elements.count(); i++)
	{
		linked_elements[i]->position = position + linked_elements[i]->offset;
	}
}