#pragma once
//This class will function very similarly to how "colliders" does. It will create and store all the "ui_colliders" in a list, and iterate them checking for 
//collisions in every frame. If a collider is clicked, the "OnClick" method of the j1Gui module will be called, and the collider will be passed as an argument.
//Then, the "OnCollision" method will compare that collider with all the colliders of the different UI elements (if they have one) and call the "OnCollision" method 
//of the one that has been clicked. Then, the appropiated code will be executed.

//The exact same procedure will function with "OverClick", which will trigger the animation of the mouse being pressed, and probably nothing else.

#include "j1Gui.h"

struct Ui_collider
{
	Ui_collider(SDL_Rect _rect)
	{
		rect = _rect;
		mouse_over = false;
	}
	bool CheckCollision(iPoint point)
	{
		if (point.x > rect.x && point.x < rect.x + rect.w && point.y > rect.y && point.y < rect.y + rect.h)
		{
			return true;
		}
		return false;
	}
	SDL_Rect rect;
	bool mouse_over;
};

class ClickManager
{
public:
	ClickManager();
	~ClickManager();
	Ui_collider* Add_ui_collider(SDL_Rect _rect);

	//Will check all colliders compare it to the mouse position and click. Then if needed, will call the "OnClick" or "MouseOver" method of "j1Gui", passing
	//the indicated collider as an argument
	void Update();

	//Will empty the colliders list
	void Cleanup();

private:
	p2List<Ui_collider*> colliders;
};
