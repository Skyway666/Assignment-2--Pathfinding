#pragma once
#include "Animation.h"
#include "p2Point.h"

//Base class for every UI_Element
struct SDL_Texture;
enum UI_ELEMENT_TYPE;
class Ui_element
{
public:
	Ui_element(int x, int y);
	~Ui_element();

	//Logic update
	virtual void Update() {};
	//In charge of drawing current animation
	virtual void Draw(SDL_Texture*);
	//Code to execute when button is clicked
	virtual void OnClick() {};
	//Code to execute when mouse is over button
	virtual void OverClick() {};

	iPoint position; //Position where will be drawn
	Animation* animation;//Animation which will be executed by "Draw"
	UI_ELEMENT_TYPE type; //Type of UI element
};

