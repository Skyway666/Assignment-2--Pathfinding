#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "ClickManager.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");
	background_file_name = conf.child("menu_background").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	menu_background = App->tex->Load(background_file_name.GetString());

	return true;
}

// Update of all ui_elements will be executed here
bool j1Gui::PreUpdate()
{
	return true;
}

// Draw of all ui_elements and background will be executed here
bool j1Gui::PostUpdate()
{
	App->render->Blit(menu_background, 0, 0);
	//TEST
	SDL_Texture* text = App->fonts->Print("DEBERIAS TRABAJAR LOS FINES DE SEMANA, WAIFU DRAWER", { 255,255,255,255 });
	App->render->Blit(text, 0, 0,3,true);
	//TEST

	

	return true;
}


//This method will call iterate over all the colliders of the icons in the "ui_elements" list, looking for the one that has the same collider that the one given to the 
//function. Then it will call its "OnClick" method
void j1Gui::OnClick(ui_collider* c1)
{

}

//Same as "OnClick", but will call "OverClick" methods
void j1Gui::OverClick(ui_collider* c1)
{

}
// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

