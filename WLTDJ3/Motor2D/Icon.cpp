#include "Icon.h"
#include "j1Gui.h"
#include "Text.h"



Icon::Icon(int x, int y): Ui_element(x,y)
{
	type = ICON;
	Idle.PushBack({ 2,112,226,67 });
	Idle.loop = false;

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