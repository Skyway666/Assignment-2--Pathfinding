#include "Icon.h"
#include "j1Gui.h"
#include "Text.h"



Icon::Icon(int x, int y, Linked_text* text): Ui_element(x,y)
{
	type = ICON;
	Idle.PushBack({ 2,112,226,67 });
	Idle.loop = false;

	if(text != nullptr)
	{ 
		//Put the text in its place
		text->text->position.x = x + text->offset.x;
		text->text->position.y = y + text->offset.y;
	}

	animation = &Idle;
}


Icon::~Icon()
{

}
