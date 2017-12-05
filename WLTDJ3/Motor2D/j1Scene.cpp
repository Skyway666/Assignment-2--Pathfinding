
#include "j1Scene.h"
#include "j1Gui.h"
#include "Player.h"
#include "j1Fonts.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{	
	//This are the conditions that make the game start. In order to end it, all entities should be erased and execute map's cleanup
	//colliders should also be cleaned up

	//App->map->Load("Level 1.2 provisional.tmx");
	//App->map->map = 0;
	//App->pathfinding->SetMap();	
	//App->entities->Spawn_waiting_entities();
	//App->entities->AddEntity(ENTITY_TYPES::PLAYER, App->map->data.player_starting_value.x, App->map->data.player_starting_value.y);


	//TEST

	//Menu window
	title = App->fonts->Load("fonts/open_sans/OpenSans-Regular.ttf", 30);
	Text* titola = App->gui->Add_text(100, 100, "WHO LET THE DOG JUMP", title);

	Menu_Window = App->gui->Add_window(300, 100);

	start = App->gui->Add_button(300, 300, (j1Module*)this,START);
	Text* text_to_link = App->gui->Add_text(0, 0, "START");
	start->Link_ui_element(text_to_link, 90, 22);

	boom = App->gui->Add_button(300, 500, (j1Module*)this, START);
	text_to_link = App->gui->Add_text(0, 0, "TEST BUTTON");
	boom->Link_ui_element(text_to_link, 60, 22);

	Menu_Window->Link_ui_element(start, 120, 100);
	Menu_Window->Link_ui_element(boom, 120, 300);
	Menu_Window->Link_ui_element(titola, 45, 30);

	titola = App->gui->Add_text(100, 100, "PAUSE MENU", title);

	//Pause window
	Pause_Window = App->gui->Add_window(300, 100);

	continuee = App->gui->Add_button(300, 300, (j1Module*)this, START);
	text_to_link = App->gui->Add_text(0, 0, "CONTINUE");
	continuee->Link_ui_element(text_to_link, 75, 22);

	exit = App->gui->Add_button(300, 500, (j1Module*)this, START);
	text_to_link = App->gui->Add_text(0, 0, "EXIT");
	exit->Link_ui_element(text_to_link, 100, 22);

	Pause_Window->Link_ui_element(continuee, 120, 100);
	Pause_Window->Link_ui_element(exit, 120, 300);
	Pause_Window->Link_ui_element(titola, 120, 30);

	Pause_Window->SetActive(false);



	//TEST

	App->map->path_indicator = App->tex->Load("textures/path_indicator.png");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	//TEST
	if (App->pause && pause_once)
	{
		Pause_Window->SetActive(true);
		pause_once = false;
	}
	else if(!App->pause && !pause_once)
	{
		Pause_Window->SetActive(false);
		pause_once = true;
	}
	//TEST
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (App->framerate_cap != 0)
		{
			App->framerate_cap = 0;
			App->cap = "Off";
		}
		else
		{
			App->framerate_cap = App->config_framerate_cap;
			App->cap = "On";
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 50 * dt;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 50 * dt;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 50 * dt;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 50 * dt;


	// Set camera to follow the player (commented in order to debug better)
	if(App->entities->player != nullptr)
	{ 
		App->render->camera.x = -App->entities->player->position.x + 400;
		App->render->camera.y = -App->entities->player->position.y + 400;
	}

	//Camera limit (don't let player see ugly stuff)
	if (App->render->camera.y < App->map->data.camera_y_limit)
		App->render->camera.y = App->map->data.camera_y_limit;



	App->map->Draw();
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	App->tex->UnLoad(win_screen);
	App->tex->UnLoad(App->map->bone_graphics);
	return true;
}

void j1Scene::Change_to_map(int _map)
{
	App->entities->EraseEntities();
	App->collision->Erase_Non_Player_Colliders();
	App->entities->Clear_waiting_list();
	App->map->CleanUp();
	if (_map == 0)
	{
		App->map->Load("Level 1.2 provisional.tmx");
		App->map->map = 0;
	}
	else if (_map == 1)
	{
		App->map->Load("Level 2.2 provisional.tmx");
		App->map->map = 1;
	}
	App->pathfinding->SetMap();
	App->entities->Spawn_waiting_entities();
	App->loading_frame = true;
}

void j1Scene::OnMouseEvent(UI_EVENT event, Ui_element* element)
{
	//TEST
	if(event == MOUSE_STOP_CLICK)
	{ 
		if (element == start)
		{
			
			App->map->Load("Level 1.2 provisional.tmx");
			App->map->map = 0;
			App->pathfinding->SetMap();
			App->entities->Spawn_waiting_entities();
			App->entities->AddEntity(ENTITY_TYPES::PLAYER, App->map->data.player_starting_value.x, App->map->data.player_starting_value.y);

			Menu_Window->SetActive(false);
			App->gui->blit_background = false;
			App->loading_frame = true;
			
		}
		if (element == continuee)
		{
			App->pause = false;
		}
		if (element == exit)
		{
			App->pause = false;
			Menu_Window->SetActive(true);
			App->gui->blit_background = true;
		}

	}
	//TEST
}
