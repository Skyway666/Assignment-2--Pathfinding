#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "ClickManager.h"

//This structure contains a pointer to a text and its offset. Its only use is to be passed to the icon or button constructor in order to have a text
//linked to it


j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
	click_manager = new ClickManager();
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

	//TEST
	Text* text_to_link = Add_text(0, 0, "ITWORKS?");
	Add_text(500, 500, "It really works, man i'm a genious");
	Linked_text final_text(100, 30, text_to_link);
	AddUi_element(300, 300, BUTTON, &final_text);

	return true;
}

// Update of all ui_elements will be executed here
bool j1Gui::PreUpdate()
{
	click_manager->Update();
	return true;
}

// Draw of all ui_elements and background will be executed here
bool j1Gui::PostUpdate()
{
	App->render->Blit(menu_background, 0, 0);
	
	for (uint i = 0; i < ui_elements.count(); ++i)
	{
		if (ui_elements[i] != nullptr)
			ui_elements[i]->Draw(atlas);
	}
	//TEST
	SDL_Texture* text = App->fonts->Print("DEBERIAS TRABAJAR LOS FINES DE SEMANA, WAIFU DRAWER", { 255,255,255,255 });
	App->render->Blit(text, 0, 0,3,true);
	//TEST

	

	return true;
}

Ui_element* j1Gui::AddUi_element(int x, int y, UI_ELEMENT_TYPE type, Linked_text* text, BUTTON_TYPE button_type)
{
	Ui_element* new_ui_element = nullptr;

	switch (type) {
		case UI_ELEMENT_TYPE::ICON:
		{
			new_ui_element = new Icon(x, y,text);
			ui_elements.add(new_ui_element);
			break;
		}

		case UI_ELEMENT_TYPE::BUTTON:
		{
			new_ui_element = new Button(x, y,text, button_type);
			ui_elements.add(new_ui_element);
			break;
		}
	}
	return new_ui_element;
}

Text* j1Gui::Add_text(int x, int y, const char* text)
{
	Ui_element* new_text = new Text(x, y, text);
	ui_elements.add(new_text);

	return (Text*)new_text;
}

//This method will iterate over all the colliders of the icons in the "ui_elements" list, looking for the one that has the same collider that the one given to the 
//function. Then it will call its "OnClick" method
void j1Gui::OnClick(Ui_collider* c1)
{
	for (int i = 0; i < ui_elements.count(); i++)
	{
		if(ui_elements[i] != nullptr)
		{
			if (ui_elements[i]->collider == c1)
			{
				ui_elements[i]->OnClick();
			}
		}
	}
}

//Same as "OnClick", but will call "OverClick" methods
void j1Gui::OverClick(Ui_collider* c1)
{

}
// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	for (int i = 0; i < ui_elements.count(); i++)
	{
		delete ui_elements[i];
		ui_elements[i] = nullptr;
	}
	click_manager->Cleanup();//Free all ui_colliders
	delete click_manager;
	click_manager = nullptr;
	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

