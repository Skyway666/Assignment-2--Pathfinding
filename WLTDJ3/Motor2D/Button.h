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

	void OnClick(); //Change animation 
	void OverClick(); //Change animation as well
private:
	Animation Idle;
};

