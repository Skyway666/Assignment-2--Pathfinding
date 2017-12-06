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
	bool Awake(pugi::xml_node& conf);

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
	void Load_credits(); bool want_to_load_credits = false;
	void UnLoad_credits(); bool want_to_unload_credits = false;

	bool exit_app = false;
private:
	//Main menu setup
	Window* Menu_Window = nullptr;
	Button* start = nullptr;
	Button* continuee = nullptr;
	Button* exit = nullptr;
	SDL_Texture* main_menu_background;
	
	//Pause menu setup
	Window* Pause_Window = nullptr;
	Button* resume = nullptr;
	Button* exit_main_menu = nullptr;
	bool pause_menu_spawned = true;
	
	//Credits setup

	
	//Paths to load assets from config
	p2SString main_menu_background_file_name;

	_TTF_Font* title;


	
};

#endif // __j1SCENE_H__