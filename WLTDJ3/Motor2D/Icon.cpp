#include "Icon.h"
#include "j1Gui.h"
#include "Text.h"
#include "ClickManager.h"
#include "j1App.h"



Icon::Icon(int x, int y): Ui_element(x,y)
{
	type = ICON;
	Idle.PushBack({ 16,528,457,485});
	Idle.loop = false;

	collider = App->gui->click_manager->Add_ui_collider({ x,y,457,100 });
	animation = &Idle;
}


Icon::~Icon()
{

}

void Icon::OnMouseEvent(UI_EVENT event)
{
	if (event == MOUSE_CLICK)
	{
		gripped = true;
	}
	if (event == MOUSE_STOP_CLICK)
	{
		gripped = false;
	}
}