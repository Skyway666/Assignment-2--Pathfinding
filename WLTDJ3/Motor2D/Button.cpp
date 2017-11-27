#include "Button.h"
#include "j1Gui.h"
#include "Text.h"


Button::Button(int x, int y, Linked_text* text) : Ui_element(x, y)
{
	type = BUTTON;
}


Button::~Button()
{
}
