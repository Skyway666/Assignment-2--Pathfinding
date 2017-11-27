#pragma once
#include "Ui_element.h"

struct Linked_text;
class Icon : public Ui_element
{
public:
	Icon(int x, int y, Linked_text* text);
	~Icon();
private:
	Animation Idle;
};

