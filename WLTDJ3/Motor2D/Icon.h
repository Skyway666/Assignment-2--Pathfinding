#pragma once
#include "Ui_element.h"
class Icon : public Ui_element
{
public:
	Icon(int x, int y);
	~Icon();
private:
	Animation Idle;
};

