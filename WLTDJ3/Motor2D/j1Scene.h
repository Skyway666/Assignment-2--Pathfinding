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

	//Executes code depending on the event and the ui element affected
	void OnMouseEvent(UI_EVENT event, Ui_element* element);
    
	//Unloads current map and loads the map indicated in the argument. If there is no map loaded, it just loads the indicated map
	void Change_to_map(int);

	//Functions to load and unload Ui setups and bools to execute them safely
	void Load_main_menu(); bool want_load_main_menu = false;
	void UnLoad_main_menu(); bool want_unload_main_menu = false;

	bool exit_app = false;
private:
	//TEST
	Window* Menu_Window;
	Button* start;
	Button* continuee;
	Button* exit;
	
	Window* Pause_Window;
	Button* resume;
	Button* exit_main_menu;

	bool pause_menu_spawned = true;
	//TEST
	
	_TTF_Font* title;


	
};

#endif // __j1SCENE_H__