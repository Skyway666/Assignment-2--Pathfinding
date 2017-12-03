#include "Button.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "ClickManager.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1Map.h"
#include "Pathfinding.h"
#include "j1Entities.h"
#include "Pathfinding.h"



Button::Button(int x, int y, j1Module* _listener, BUTTON_TYPE _button_type): Ui_element(x, y)
{
	type = BUTTON;
	button_type = _button_type;
	Idle.PushBack({ 2,112,226,67 }); 
	Idle.loop = false;

	Shiny.PushBack({ 414,169,224,63 });
	Shiny.loop = false;

	Pressed.PushBack({ 644,169,224,63 });
	Pressed.loop = false;

	listener = _listener;
	collider = App->gui->click_manager->Add_ui_collider({x,y,226,67 });

	animation = &Idle;
}


Button::~Button()
{

}

void Button::OnMouseEvent(UI_EVENT event)
{
	if (event == MOUSE_ENTER)
	{
		animation = &Shiny;
	}
	if (event == MOUSE_EXIT)
	{
		animation = &Idle;
	}
	if (event == MOUSE_CLICK)
	{
		animation = &Pressed;
		gripped = true;
	}
	if (event == MOUSE_STOP_CLICK)
	{
		animation = &Shiny;
		gripped = false;
	}
}
