#include "j1Module.h"
#include "Animation.h"

class SDL_Texture;

enum FADE_STATE
{
	NOTHING,
	FADING,
	UNFADING
};
class j1Transition : public j1Module
{
public:
	j1Transition();
	~j1Transition();

	//Load the assets for the transition animation
	bool Start();

	//If it is transitioning, make animation appear for the duration of the transition and turn bools to true in the middle of the animation
	bool PostUpdate();

	//Make a giant animation over all the stuff blited in the screen (maybe make some sound)
	void Make_transition(bool* bool_to_unload, bool* bool_to_load);

	bool transitioning = false;

private:

	bool* bool_to_load = nullptr;
	bool* bool_to_unload = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation transition1;
	Animation transition2;
	FADE_STATE current_state;



};

