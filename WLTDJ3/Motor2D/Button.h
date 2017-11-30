#pragma once
#include "Ui_element.h"

struct Linked_text;
struct Ui_collider;
enum BUTTON_TYPE;
class j1Module;
class Button : public Ui_element
{
public:
	Button(int x, int y, j1Module* _listener,BUTTON_TYPE _button_type, Linked_text* text);
	~Button();
	BUTTON_TYPE button_type; //We should be able to create various types of buttons

	//Change the button animation depending on the mouse state
	void OnMouseEvent(UI_EVENT event);
	//Collider

private:

	//Animations should be load from the xml
	Animation Idle;
	Animation Shiny;
	Animation Pressed;
};

