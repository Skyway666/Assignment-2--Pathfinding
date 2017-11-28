#pragma once
#include "j1Render.h"
#include "j1App.h"

class Chronometer
{
public:

	void Start(float amount_of_time) // Amount of time in seconds
	{
		time = amount_of_time * 1000;
		timer_duration = SDL_GetTicks() + time;
		pause_timer = timer_duration;
		timer_active = true;
	}

	void NewTime()
	{
		if (App->pause && !pause_timer_taken)
		{
			pause_timer = ((SDL_GetTicks() + time) - SDL_GetTicks()) / 1000;
			pause_timer_taken = true;
		}
		else if (!App->pause && pause_timer_taken)
		{
			Start(pause_timer);
			pause_timer_taken = false;
		}
	}

	bool IsOver()
	{
		if (timer_active)
		{
			if (timer_duration > SDL_GetTicks())
				return false;
			else
			{
				timer_active = false;
				return true;
			}
		}

		return true;
	}

	void Reset()
	{
		timer_duration = 0;
		timer_active = true;
	}

	int Read()
	{
		return timer_duration;
	}

private:

	float time = 0;
	int timer_duration = 0;
	bool timer_active = false;
	bool pause_timer_taken = false;
	float pause_timer = 0;
};

