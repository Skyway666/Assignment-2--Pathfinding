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


	return true;
}

// Update of all ui_elements and click_manager will be executed here
bool j1Gui::PreUpdate()
{
	//Update all icons (Maybe they should be able to blit from their own texture like texts)
	for (uint i = 0; i < icons.count(); ++i)
	{
		if (icons[i] != nullptr)
			icons[i]->Update();
	}
	//Update all buttons
	for (uint i = 0; i < buttons.count(); ++i)
	{
		if (buttons[i] != nullptr)
			buttons[i]->Update();
	}
	//Update all texts
	for (uint i = 0; i < texts.count(); ++i)
	{
		if (texts[i] != nullptr)
			texts[i]->Update();
	}
	click_manager->Update();
	return true;
}

// Draw of all ui_elements and background will be executed here
bool j1Gui::PostUpdate()
{
	if (active)//TEST
	{ 
		App->render->Blit(menu_background, 0, 0,1,false);
	
		//Blit all icons (Maybe they should be able to blit from their own texture like texts)
		for (uint i = 0; i < icons.count(); ++i)
		{
			if (icons[i] != nullptr)
				icons[i]->Draw(atlas);
		}
		//Blit all buttons
		for (uint i = 0; i < buttons.count(); ++i)
		{
			if (buttons[i] != nullptr)
				buttons[i]->Draw(atlas);
		}
		//Blit all texts
		for (uint i = 0; i < texts.count(); ++i)
		{
			if (texts[i] != nullptr)
				texts[i]->Draw();
		}
    }
	

	return true;
}

Icon* j1Gui::Add_icon(int x, int y)
{
	Icon* new_ui_element = nullptr;

	new_ui_element = new Icon(x, y);
	icons.add(new_ui_element);

	return new_ui_element;
}

Button* j1Gui::Add_button(int x, int y, j1Module* _listener, BUTTON_TYPE button_type)
{
	Button* new_ui_element = nullptr;

	new_ui_element = new Button(x, y,_listener,button_type);
	buttons.add(new_ui_element);

	return new_ui_element;
}

Text* j1Gui::Add_text(int x, int y, const char* text, _TTF_Font* font)
{
	Text* new_text = new Text(x, y, text, font);
	texts.add(new_text);

	return new_text;
}

//This method will iterate over all the colliders of the buttons in the "buttons" list, looking for the one that has the same collider that the one given to the 
//function. Then it will call its "OnClick" method
void j1Gui::OnMouseEvent_caller(Ui_collider* c1, UI_EVENT event)
{
	for (int i = 0; i < buttons.count(); i++)
	{
		if(buttons[i] != nullptr)
		{
			if (buttons[i]->collider == c1)
			{
				buttons[i]->listener->OnMouseEvent(event, buttons[i]);
				buttons[i]->OnMouseEvent(event);
			}
		}
	}
	for (int i = 0; i < icons.count(); i++)
	{
		if (icons[i] != nullptr)
		{
			if (icons[i]->collider == c1)
			{
				if(icons[i]->listener != nullptr)
				icons[i]->listener->OnMouseEvent(event, buttons[i]);
				icons[i]->OnMouseEvent(event);
			}
		}
	}
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	for (int i = 0; i < icons.count(); i++)
	{
		delete icons[i];
		icons[i] = nullptr;
	}
	for (int i = 0; i < buttons.count(); i++)
	{
		delete buttons[i];
		buttons[i] = nullptr;
	}
	for (int i = 0; i < texts.count(); i++)
	{
		delete texts[i];
		texts[i] = nullptr;
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

