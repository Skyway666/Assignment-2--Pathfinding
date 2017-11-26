#include "Icon.h"
#include "j1Gui.h"



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
