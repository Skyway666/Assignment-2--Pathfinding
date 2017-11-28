#include "ClickManager.h"
#include "j1Input.h"
#include "j1App.h"
#include "p2Log.h"

ClickManager::ClickManager()
{

}


ClickManager::~ClickManager()
{

}

Ui_collider* ClickManager::Add_ui_collider(SDL_Rect rect)
{
	Ui_collider* new_collider = new Ui_collider(rect);
	colliders.add(new_collider);

	return new_collider;
}

void ClickManager::Update()
{
	iPoint mouse_position;
	App->input->GetMousePosition(mouse_position.x, mouse_position.y);
	for (int i = 0; i < colliders.count(); i++)
	{
		if(colliders[i] != nullptr) //Skip empty colliders
		{ 
			if (colliders[i]->CheckCollision(mouse_position) && !colliders[i]->mouse_over)
			{
				colliders[i]->mouse_over = true;
				App->gui->OnMouseEvent_caller(colliders[i], MOUSE_ENTER);
				LOG("ENTER");
			}
			if (colliders[i]->mouse_over && !colliders[i]->CheckCollision(mouse_position))
			{
				colliders[i]->mouse_over = false;
				App->gui->OnMouseEvent_caller(colliders[i], MOUSE_EXIT);
				LOG("EXIT");
			}
			if (colliders[i]->mouse_over && App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				App->gui->OnMouseEvent_caller(colliders[i], MOUSE_CLICK);
				LOG("CLICK");
			}
		}
	}
}

void ClickManager::Cleanup()
{
	for (int i = 0; i < colliders.count(); i++)
	{
		delete colliders[i];
		colliders[i] = nullptr;
	}
}

