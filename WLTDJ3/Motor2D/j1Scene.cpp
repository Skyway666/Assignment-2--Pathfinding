
#include "j1Scene.h"
#include "j1Gui.h"
#include "Player.h"
#include "j1Fonts.h"
#include "j1Transition.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& conf)
{
	LOG("Loading Scene");
	main_menu_background_file_name = conf.child("menu_background").attribute("file").as_string("");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	App->map->path_indicator = App->tex->Load("textures/path_indicator.png");
	main_menu_background = App->tex->Load(main_menu_background_file_name.GetString());
	win_screen = App->tex->Load("textures/WinScreen.png"); //Could be loaded from xml

	//Menu setup
	Load_main_menu();

	return true;
}

// Used to load and unload stuff safelly
bool j1Scene::PreUpdate()
{
	if (App->pause && pause_menu_spawned)
	{
		Load_pause();
		pause_menu_spawned = false;
	}
	else if(!App->pause && !pause_menu_spawned)
	{
		UnLoad_pause();
		pause_menu_spawned = true;
	}

	//Execute load and unload functions safelly
	//First all unloads
		if (want_unload_main_menu)
		{
			UnLoad_main_menu();
			want_unload_main_menu = false;
		}
		if (want_unload_credits)
		{
			UnLoad_credits();
			want_unload_credits = false;
		}
		if (want_unload_options)
		{
			UnLoad_options();
			want_unload_options = false;
		}
		if (want_unload_HUD)
		{
			UnLoad_HUD();
			want_unload_HUD = false;
		}
	//Then all loads
		if (want_load_main_menu)
		{
			Load_main_menu();
			want_load_main_menu = false;
		}
		if (want_load_credits)
		{
			Load_credits();
			want_load_credits = false;
		}
		if (want_load_options)
		{
			Load_options();
			want_load_options = false;
		}
		if (want_load_HUD)
		{
			Load_HUD();
			want_load_HUD = false;
		}
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Playtime counter
	if (hourglass != nullptr)
	{
		UpdateTime();
		hourglass_time->UpdateText(time);
		if (App->pause)
			hourglass->animation->Reset();
	}

	// Update points
	if (coins != nullptr)
	{
		sprintf_s(currentcoins, 500, "x%i", App->entities->player->points);
		current_coins->UpdateText(currentcoins);
		
		if (coin_animation)
		{
			coins->animation->Reset();
			coin_animation = false;
		}
		if (App->pause)
			coins->animation->Reset();
	}

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

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
	{
		//tests here
	}

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

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || exit_app)
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
	if(App->map->map_loaded)
	{ 
		App->entities->EraseEntities();
		App->collision->Erase_Non_Player_Colliders();
		App->entities->Clear_waiting_list();
		App->map->CleanUp();
	}
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

void j1Scene::Unload_map()
{
	App->entities->EraseEntities();
	App->collision->Erase_Non_Player_Colliders();
	App->entities->Clear_waiting_list();
	App->map->CleanUp();
	App->map->map = -1;
	App->pause = false;
}
void j1Scene::Load_main_menu()
{
	//Start button (All of it could be the child of start to simplify code)
	start = App->gui->Add_button(370, 250, (j1Module*)this);
	Text* text_to_link = App->gui->Add_text(0, 0, "START");
	start->Link_ui_element(text_to_link, 100, 30);
	//Continue button
	continuee = App->gui->Add_button(370, 350, (j1Module*)this);
	text_to_link = App->gui->Add_text(0, 0, "CONTINUE");
	continuee->Link_ui_element(text_to_link, 75, 30);	
	//Options button
	options = App->gui->Add_button(370, 450, (j1Module*)this);
	text_to_link = App->gui->Add_text(0, 0, "OPTIONS");
	options->Link_ui_element(text_to_link, 85, 30);	
	//Credits button
	credits = App->gui->Add_button(370, 550, (j1Module*)this);
	text_to_link = App->gui->Add_text(0, 0, "CREDITS");
	credits->Link_ui_element(text_to_link, 85, 30);
	//Exit button
	exit = App->gui->Add_button(370, 650, (j1Module*)this);
	text_to_link = App->gui->Add_text(0, 0, "EXIT");
	exit->Link_ui_element(text_to_link, 105, 30);


	

	App->gui->Set_backgrond(main_menu_background);
}

void j1Scene::UnLoad_main_menu()
{
	App->gui->Erase_Ui_element(start);
	start = nullptr;
	App->gui->Erase_Ui_element(continuee);
	continuee = nullptr;
	App->gui->Erase_Ui_element(exit);
	exit = nullptr;
	App->gui->Erase_Ui_element(credits);
	credits = nullptr;
	App->gui->Erase_Ui_element(options);
	options = nullptr;

	App->gui->Set_backgrond(nullptr);
}

void j1Scene::Load_credits()
{
	Text* text_to_link = App->gui->Add_text(0, 0, "MAIN MENU");
	exit_main_menu_fc = App->gui->Add_button(500, 500, (j1Module*)this);
	exit_main_menu_fc->Link_ui_element(text_to_link, 70, 30);

	App->gui->Set_backgrond(win_screen);
}
void j1Scene::UnLoad_credits()
{
	App->gui->Erase_Ui_element(exit_main_menu_fc);
	exit_main_menu_fc = nullptr;

	App->gui->Set_backgrond(nullptr);
}

void j1Scene::Load_pause()
{
	Text* titola = App->gui->Add_text(0, 0, "PAUSE MENU", title);
	Pause_Window = App->gui->Add_window(300, 100);

	resume = App->gui->Add_button(0, 0, (j1Module*)this);
	Text* text_to_link = App->gui->Add_text(0, 0, "RESUME");
	resume->Link_ui_element(text_to_link, 80, 22);

	exit_main_menu_fg = App->gui->Add_button(0, 0, (j1Module*)this);
	text_to_link = App->gui->Add_text(0, 0, "MAIN MENU");
	exit_main_menu_fg->Link_ui_element(text_to_link, 70, 30);

	Pause_Window->Link_ui_element(resume, 120, 100);
	Pause_Window->Link_ui_element(exit_main_menu_fg, 120, 300);
	Pause_Window->Link_ui_element(titola, 120, 30);
}

void j1Scene::UnLoad_pause()
{
	App->gui->Erase_Ui_element(Pause_Window);
	Pause_Window = nullptr;
	resume = nullptr;
	exit_main_menu_fg = nullptr;
}

void j1Scene::Load_options()
{
	//Create window elements
	upper_music_volume = App->gui->Add_button(900, 400, (j1Module*)this, UPPER);
	lower_music_volume = App->gui->Add_button(400, 400, (j1Module*)this, LOWER);

	upper_fx_volume = App->gui->Add_button(900, 600, (j1Module*)this, UPPER);
	lower_fx_volume = App->gui->Add_button(400, 600, (j1Module*)this, LOWER);

	exit_main_menu_fo = App->gui->Add_button(0, 600, (j1Module*)this);
	Text* text_to_link = App->gui->Add_text(0, 0, "MAIN MENU");
	exit_main_menu_fo->Link_ui_element(text_to_link, 70, 30);

	music_volume = App->gui->Add_StatBar(565, 410, 300, 50, &App->audio->music_volume, MIX_MAX_VOLUME);
	text_to_link = App->gui->Add_text(0, 0, "MUSIC VOLUME");
	//Create label for text
	Icon* pretty_label = App->gui->Add_icon(0, 0);
	pretty_label->anim.PushBack({ 939, 1139, 362, 141 });
	pretty_label->anim.loop = false;
	pretty_label->animation = &pretty_label->anim;
	pretty_label->scale = 0.7;
	//Link label to text
	text_to_link->Link_ui_element(pretty_label, -35, -30);

	music_volume->Link_ui_element(text_to_link, 0, -80);

	fx_volume = App->gui->Add_StatBar(565, 610, 300, 50, &App->audio->fx_volume, MIX_MAX_VOLUME);
	text_to_link = App->gui->Add_text(0, 0, "FX VOLUME");
	//Create label for text
	pretty_label = App->gui->Add_icon(0, 0);
	pretty_label->anim.PushBack({ 939, 1139, 362, 141 });
	pretty_label->anim.loop = false;
	pretty_label->animation = &pretty_label->anim;
	pretty_label->scale = 0.7;
	//Link label to text
	text_to_link->Link_ui_element(pretty_label, -60, -30);

	fx_volume->Link_ui_element(text_to_link, 20, -80);

	App->gui->Set_backgrond(main_menu_background);

}

void j1Scene::UnLoad_options()
{
	App->gui->Erase_Ui_element(upper_music_volume);
	upper_music_volume = nullptr;
	App->gui->Erase_Ui_element(lower_music_volume);
	lower_music_volume = nullptr;
	App->gui->Erase_Ui_element(upper_fx_volume);
	upper_fx_volume = nullptr;
	App->gui->Erase_Ui_element(lower_fx_volume);
	lower_fx_volume = nullptr;
	App->gui->Erase_Ui_element(exit_main_menu_fo);
	exit_main_menu_fo = nullptr;
	App->gui->Erase_Ui_element(music_volume);
	music_volume = nullptr;
	App->gui->Erase_Ui_element(fx_volume);
	fx_volume = nullptr;
}
void j1Scene::OnMouseEvent(UI_EVENT event, Ui_element* element)
{
	//TEST
	if(event == MOUSE_STOP_CLICK && !App->transition->transitioning)
	{ 
		//Main menu
			if (element == start)
			{
				//Game loading (JUST FOR TESTING)
				Change_to_map(0);
				App->entities->AddEntity(ENTITY_TYPES::PLAYER, App->map->data.player_starting_value.x, App->map->data.player_starting_value.y); 
				//Unload main menu adn load hud
				App->transition->Make_transition(&want_unload_main_menu, &want_load_HUD);
			}
			if (element == continuee)
			{		
				//Load saved game
				App->LoadGame();
				//Create new player when continuing from menu
				App->entities->AddEntity(ENTITY_TYPES::PLAYER, App->map->data.player_starting_value.x, App->map->data.player_starting_value.y); 
				//Unload main menu adn load hud
				App->transition->Make_transition(&want_unload_main_menu, &want_load_HUD);
			}
			if (element == exit)
			{
				//Exit app
				App->transition->Make_transition(&exit_app, nullptr);
			}
			if (element == credits)
			{
				//Unload main menu and Load credits
				App->transition->Make_transition(&want_unload_main_menu, &want_load_credits);
			}
			if (element == options)
			{
				//Unload main menu and load options
				App->transition->Make_transition(&want_unload_main_menu, &want_load_options);
			}
		//Pause menu
			if (element == resume)
			{
				App->pause = false;
			}
			if (element == exit_main_menu_fg)
			{	
				//Game unloading (should be also done with a bool)
				Unload_map();
				//Load main menu and Unload HUD
				App->transition->Make_transition(&want_load_main_menu, &want_unload_HUD);
			}

		//Credits menu
			if (element == exit_main_menu_fc)
			{
				//Unload credits and Load main menu
				App->transition->Make_transition(&want_unload_credits, &want_load_main_menu);
			}
		//Options menu
			if (element == upper_music_volume)
			{
				App->audio->Modify_music_volume(10); // "10" could be a value loaded from xml
			}
			if (element == lower_music_volume)
			{
				App->audio->Modify_music_volume(-10);
			}
			if (element == upper_fx_volume)
			{
				App->audio->Modify_fx_volume(10);
				App->audio->PlayFx(1);
			}
			if (element == lower_fx_volume)
			{
				App->audio->Modify_fx_volume(-10);
				App->audio->PlayFx(1);
			}
			if (element == exit_main_menu_fo) 
			{
				//Unload main menu and load options
				App->transition->Make_transition(&want_load_main_menu, &want_unload_options);
			}


	}
	//TEST
}

void j1Scene::Load_HUD()
{
	hourglass = App->gui->Add_icon(920, 580);
	coins = App->gui->Add_icon(-20, -20);

	int row = 0;
	for (int i = 0; i < 16; i++)
		hourglass->anim.PushBack({ 229 * i, 345 * row, 229, 345 });
	row++;
	for (int i = 0; i < 16; i++)
		hourglass->anim.PushBack({ 229 * i, 345 * row, 229, 345 });
	row++;
	for (int i = 0; i < 14; i++)
		hourglass->anim.PushBack({ 229 * i, 345 * row, 229, 345 });

	hourglass->animation_speed = 0.2;
	hourglass->anim.speed = 0.2;
	hourglass->anim.loop = true;
	hourglass->animation = &hourglass->anim;
	hourglass->scale = 0.5;

	row++;
	for (int i = 0; i < 4; i++)
		coins->anim.PushBack({ 229 * i, 345 * row, 229, 345 });
	for (int i = 3; i >= 0; i--)
		coins->anim.PushBack({ 229 * i, 345 * row, 229, 345 });

	coins->animation_speed = 0.3;
	coins->anim.speed = 0.3;
	coins->anim.loop = false;
	coins->animation = &coins->anim;
	coins->scale = 0.5;


	hourglass_time = App->gui->Add_text(0, 0, "00:00:00");
	hourglass->Link_ui_element(hourglass_time, -50, 120);
	playtime.Start();

	current_coins = App->gui->Add_text(0, 0, "x0");
	coins->Link_ui_element(current_coins, 65, 85);
}

void j1Scene::UnLoad_HUD()
{
	App->gui->Erase_Ui_element(hourglass);
	hourglass = nullptr;
	App->gui->Erase_Ui_element(coins);
	coins = nullptr;
}

void j1Scene::UpdateTime()
{
	if (!App->pause)
	{
		s = playtime.ReadSec();

		if (s >= 10)
		{
			s = 0;
			s2++;
			playtime.Start();
		}
		if (s2 >= 6)
		{
			s2 = 0;
			m++;
		}
		if (m >= 10)
		{
			m = 0;
			m2++;
		}
		if (m2 >= 6)
		{
			m2 = 0;
			h++;
		}
		if (h >= 10)
		{
			h = 0;
			h2++;
		}
		if (h2 >= 10)
		{
			s = 0;
			s2 = 0;
			m = 0;
			m2 = 0;
			h = 0;
			h2 = 0;
		}

		int i = 0;
		time[i] = h2 + 48;
		i++;
		time[i] = h + 48;
		i++;
		time[i] = 58;
		i++;
		time[i] = m2 + 48;
		i++;
		time[i] = m + 48;
		i++;
		time[i] = 58;
		i++;
		time[i] = s2 + 48;
		i++;
		time[i] = s + 48;
	}
	else
	{
		playtime.ResumeFromSec(s);
	}
}

bool j1Scene::Save(pugi::xml_node& data) const
{
	data.append_attribute("s") = s;
	data.append_attribute("s2") = s2;
	data.append_attribute("m") = m;
	data.append_attribute("m2") = m2;
	data.append_attribute("h") = h;
	data.append_attribute("h2") = h2;

	return true;
}

bool j1Scene::Load(pugi::xml_node& data)
{
	s = data.attribute("s").as_int();
	s2 = data.attribute("s2").as_int();
	m = data.attribute("m").as_int();
	m2 = data.attribute("m2").as_int();
	h = data.attribute("h").as_int();
	h2 = data.attribute("h2").as_int();

	playtime.ResumeFromSec(s);

	return true;
}