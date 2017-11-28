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

	//MAYBE THIS SHOULDN'T BE HERE
	//Code to execute when button is clicked
	void OnMouseEvent(UI_EVENT event);
	//Collider
	Ui_collider* collider;
	//MAYBE THIS SHOULDN'T BE HERE
private:
	Animation Idle;
};

