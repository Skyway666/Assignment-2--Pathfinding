#pragma once
#include "j1Gui.h"
#include "Animation.h"
#include "p2Point.h"
//Base class for every UI_Element
struct SDL_Texture;
class Ui_element
{
public:
	Ui_element(int x, int y, UI_ELEMENT_TYPE type);
	~Ui_element();

	//Logic update
	virtual void Update() {};
	//In charge of drawing current animation
	virtual void Draw(SDL_Texture*) {};

	iPoint position; //Position where will be drawn
	Animation* animation;//Animation which will be executed by "Draw"
	UI_ELEMENT_TYPE type; //Type of UI element
};

