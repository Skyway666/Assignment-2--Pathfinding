#pragma once
#include "Ui_element.h"

struct Linked_text;
class Icon : public Ui_element
{
public:
	Icon(int x, int y, Linked_text* text); //It should recive a pointer to the texture and animations should be set by the creator of the UI element
	~Icon();
private:
	Animation Idle;
};

