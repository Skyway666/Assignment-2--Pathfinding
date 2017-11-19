
#include "j1Scene.h"


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
	App->map->Load("Level 1.2 provisional.tmx");
	App->map->map = 0;
	App->map->path_indicator = App->tex->Load("textures/path_indicator.png");


	//JUST A TEST
	App->pathfinding->SetMap();	

	App->entities->Spawn_waiting_entities();

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
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
	App->render->camera.x = -App->entities->player->position.x + 400;
	App->render->camera.y = -App->entities->player->position.y + 400;

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
	return true;
}

void j1Scene::Change_to_map(int _map)
{

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
	App->entities->EraseEntities();
	App->entities->Spawn_waiting_entities();
}

