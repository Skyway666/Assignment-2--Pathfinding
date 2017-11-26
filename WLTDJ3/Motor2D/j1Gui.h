#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2



struct ui_collider;
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

	// Update of all icons will be executed here
	bool PreUpdate();

	// Draw of all icons will be executed here
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//This method will call iterate over all the colliders of the icons in the "ui_elements" list, looking for the one that has the same collider that the one given to the 
	//function. Then it will call its "OnClick" method
	void OnClick(ui_collider* c1);

	//Same as "OnClick", but will call "OverClick" methods
	void OverClick(ui_collider* c1);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__