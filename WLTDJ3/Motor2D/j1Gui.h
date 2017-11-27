#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "ClickManager.h"
#include "Ui_element.h"
#include "Icon.h"
#include "Button.h"
#include "Text.h"

#include "p2List.h"

#define CURSOR_WIDTH 2

enum UI_ELEMENT_TYPE
{
	ICON,
	BUTTON,
	TEXT
};
struct Linked_text
{
	Linked_text(int _offset_x, int _offset_y, Text* _text)
	{
		offset.x = _offset_x;
		offset.y = _offset_y;
		text = _text;
	}
public:
	iPoint offset;
	Text* text;

};
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Update of all ui_elements will be executed here
	bool PreUpdate();

	// Draw of all ui_elements and background will be executed here
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Add a ui element to "ui_elements" 
	Ui_element* AddUi_element(int x, int y, UI_ELEMENT_TYPE type, Linked_text* text = nullptr);

	Text* Add_text(int x, int y, const char* text);

	//This method will iterate over all the colliders of the icons in the "ui_elements" list, looking for the one that has the same collider that the one given to the 
	//function. Then it will call its "OnClick" method
	void OnClick(ui_collider* c1);

	//Same as "OnClick", but will call "OverClick" methods
	void OverClick(ui_collider* c1);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	//Background image(could be more)
	SDL_Texture* menu_background; 

	//Paths to load assets
	p2SString atlas_file_name;
	p2SString background_file_name;
	
	//Ui_element list, this module is to manage this list exclusively
	p2List<Ui_element*> ui_elements;
	ClickManager* click_manager;



};

#endif // __j1GUI_H__