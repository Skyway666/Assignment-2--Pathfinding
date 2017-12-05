#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "Pathfinding.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Entities.h"
#include "j1Gui.h"

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	SDL_Texture* win_screen;

	int time;

	bool time_gotten;

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void OnMouseEvent(UI_EVENT event, Ui_element* element);
    
	void Change_to_map(int);

	_TTF_Font* title;

	
private:
	//TEST
	Window* Menu_Window;
	Button* start;
	Button* boom;
	
	Window* Pause_Window;
	Button* continuee;
	Button* exit;

	bool pause_menu_spawned = true;
	//TEST


	
};

#endif // __j1SCENE_H__