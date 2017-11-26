#pragma once
//This class will function very similarly to how "colliders" does. It will create and store all the "ui_colliders" in a list, anditerate them checking for 
//collisions in every frame. If a collider is clicked, the "OnClick" method of the j1Gui module will be called, and the collider will be passed as an argument.
//Then, the "OnCollision" method will compare that collider with all the colliders of the different UI elements (if they have one) and call the "OnCollision" method 
//of the one that has been clicked. Then, the appropiated code will be executed.

//The exact same procedure will function with "OverClick", which will trigger the animation of the mouse being pressed, and probably nothing else.

struct ui_collider;

class ClickManager
{
public:
	ClickManager();
	~ClickManager();
};

