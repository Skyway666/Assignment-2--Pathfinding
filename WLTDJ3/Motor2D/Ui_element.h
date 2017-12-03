#pragma once
#include "Animation.h"
#include "p2Point.h"
#include "j1Module.h"
#include "p2List.h"

//Base class for every UI_Element

//Every Ui_element should be able to: Draw itself, be linked to other elements, recive mouse events(not done yet) and be dragged(not done yet).
struct SDL_Texture;
enum UI_ELEMENT_TYPE;
struct Ui_collider;
class Ui_element
{
public:
	Ui_element(int x, int y);
	~Ui_element();

	// In charge of drawing current animation
	virtual void Draw(SDL_Texture*);
	// Links a Ui_element
	virtual void Link_ui_element(Ui_element* element, int offset_x, int offset_y); 
	//For the moment it will be used to be able to drag ui_elements
	virtual void Update();
	//Detect mouse events on ui element internally
	virtual void OnMouseEvent(UI_EVENT event) {};

	iPoint position; // Position where will be drawn
	Animation* animation;// Animation which will be executed by "Draw"
	UI_ELEMENT_TYPE type; // Type of UI element
	j1Module* listener = nullptr;  // Module which has to execute their OnMouseEvent
	Ui_collider* collider = nullptr;
	p2List<Ui_element*> linked_elements; // Linked elements that with move along with the Ui_element which they are linked to 


    //Variables to be able to move UI elements
	bool gripped = false; //Knowing if the variable is gripped
	bool mouse_pos_gotten = false; //Bool to know if the mouse position has been taken
	iPoint mouse_pos_when_grip; //Knowing the initial position of the mouse when the ui element has been gripped
	iPoint pos_when_grip;

	//This will be used just for linked elements
	iPoint offset;
};

