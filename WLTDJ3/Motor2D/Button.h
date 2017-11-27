#pragma once
#include "Ui_element.h"

struct Linked_text;
struct Ui_collider;
enum BUTTON_TYPE;
class Button : public Ui_element
{
public:
	Button(int x, int y, Linked_text* text,  BUTTON_TYPE _button_type);
	~Button();
	BUTTON_TYPE button_type; //We should be able to create various types of buttons

	void OnClick(); //Code to execute when button is clicked
private:
	Animation Idle;
};

