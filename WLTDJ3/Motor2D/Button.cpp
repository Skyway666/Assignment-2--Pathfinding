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
	Idle.PushBack({ 5,237,277,103 }); 
	Idle.loop = false;

	Shiny.PushBack({ 5,120,277,103 });
	Shiny.loop = false;

	Pressed.PushBack({ 5,6,277,103 });
	Pressed.loop = false;

	listener = _listener;
	collider = App->gui->click_manager->Add_ui_collider({x,y,277,95 });

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
	}
	if (event == MOUSE_STOP_CLICK)
	{
		animation = &Shiny;
	}
}
