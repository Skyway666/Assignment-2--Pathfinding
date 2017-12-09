
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Transition.h"

j1Transition::j1Transition()
{
	name.create("transition");
}


j1Transition::~j1Transition()
{

}

bool j1Transition::Start()
{
	graphics = App->tex->Load("textures/Sandstorm.png");

	transition1.PushBack({ 0,0,1024,768 });
	transition1.PushBack({ 1024,0,1024,768 });
	transition1.PushBack({ 1024*2,0,1024,768 });
	transition1.PushBack({ 1024*3,0,1024,768 });
	transition1.PushBack({ 0,768,1024,768 });
	transition1.PushBack({ 1024,768,1024,768 });
	transition1.PushBack({ 1024 * 2,768,1024,768 });
	transition1.PushBack({ 1024 * 3,768,1024,768 });
	transition1.PushBack({ 0,768*2,1024,768 });
	transition1.PushBack({ 1024,768*2,1024,768 });

	transition1.loop = false;
	transition1.speed = 0.5;

	transition2.PushBack({ 1024,768 * 2,1024,768 });
	transition2.PushBack({ 0,768 * 2,1024,768 });
	transition2.PushBack({ 1024 * 3,768,1024,768 });
	transition2.PushBack({ 1024 * 2,768,1024,768 });
	transition2.PushBack({ 1024,768,1024,768 });
	transition2.PushBack({ 0,768,1024,768 });
	transition2.PushBack({ 1024 * 3,0,1024,768 });
	transition2.PushBack({ 1024 * 2,0,1024,768 });
	transition2.PushBack({ 1024,0,1024,768 });
	transition2.PushBack({ 0,0,1024,768 });

	transition2.loop = false;
	transition2.speed = 0.5;

	current_state = NOTHING;
	return true;
}

bool j1Transition::PostUpdate()
{
	switch (current_state) {

		case NOTHING:
		{
			transition1.Reset();
			break;
		}

		case FADING:
		{
			App->render->Blit(graphics, 0, 0, 1, false, &transition1.GetCurrentFrame());

			if (transition1.Finished())
			{
				current_state = UNFADING;
				if(bool_to_load != nullptr)
				*bool_to_load = true;
				if (bool_to_unload != nullptr)
				*bool_to_unload = true;
				transition2.Reset();
			}
			break;
		}
		case UNFADING:
		{
			App->render->Blit(graphics, 0, 0, 1, false, &transition2.GetCurrentFrame());
			if (transition2.Finished())
			{
				current_state = NOTHING;
			}
			break;
		}
	}


	return true;
}

void j1Transition::Make_transition(bool* _bool_to_unload, bool* _bool_to_load)
{
	current_state = FADING;
	bool_to_unload = _bool_to_unload;
	bool_to_load = _bool_to_load;
}