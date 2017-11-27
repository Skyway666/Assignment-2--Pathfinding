#include "Button.h"
#include "j1Gui.h"
#include "ClickManager.h"
#include "j1App.h"
#include "p2Log.h"


Button::Button(int x, int y, Linked_text* text, BUTTON_TYPE _button_type) : Ui_element(x, y)
{
	type = BUTTON;
	button_type = _button_type;
	Idle.PushBack({ 2,112,226,67 });
	Idle.loop = false;

	collider = App->gui->click_manager->Add_ui_collider({x,y,226,67 });

	if (text != nullptr)
	{
		//Put the text in its place
		text->text->position.x = x + text->offset.x;
		text->text->position.y = y + text->offset.y;
	}

	animation = &Idle;
}


Button::~Button()
{

}

void Button::OnClick()
{
	LOG("CLICK!");
}