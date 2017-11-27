#pragma once
#include "Ui_element.h"

struct Linked_text;
class Button : public Ui_element
{
public:
	Button(int x, int y, Linked_text* text);
	~Button();
};

