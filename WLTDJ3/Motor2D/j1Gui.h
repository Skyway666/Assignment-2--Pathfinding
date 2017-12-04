#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "Icon.h"
#include "Button.h"
#include "Text.h"
#include "p2List.h"


#define CURSOR_WIDTH 2

class ClickManager;
struct Ui_collider;
enum UI_ELEMENT_TYPE //Type of ui elements avaliable
{
	ICON,
	BUTTON,
};
enum BUTTON_TYPE //Knowing what type of button we are creating, just for animation purpuses
{
	NONE,
	START,
	OPTIONS,
	CREDITS
};
enum UI_EVENT
{
	MOUSE_ENTER,
	MOUSE_EXIT,
	MOUSE_CLICK,
	MOUSE_STOP_CLICK,
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
	Icon* Add_icon(int x, int y);

	Button* Add_button(int x, int y, j1Module* _listener, BUTTON_TYPE button_type = NONE);

	//Ad text as UI
	Text* Add_text(int x, int y, const char* text, _TTF_Font* font = nullptr);

	//This method will iterate over all the colliders of the icons in the "ui_elements" list, looking for the one that has the same collider that the 
	//one given to the function. Then it will call the global "OnClick" method and "OnClick" method of the UI element, which will change the label.
	void OnMouseEvent_caller(Ui_collider* c1, UI_EVENT event);

	const SDL_Texture* GetAtlas() const;
	
	ClickManager* click_manager;
	//Bool to know if backround should be drawn
	bool blit_background = true;
	

private:

	SDL_Texture* atlas;
	//Background image(could be more)
	SDL_Texture* menu_background; 

	//Paths to load assets
	p2SString atlas_file_name;
	p2SString background_file_name;
	
	//Icons list
	p2List<Icon*> icons;
	//Buttons list
	p2List<Button*> buttons;
	//Text list. Separated from the ui elements list because they have to be drawn afterwards
	p2List<Text*> texts;
	



};

#endif // __j1GUI_H__