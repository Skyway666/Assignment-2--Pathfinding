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
		timer_active = true;
	}

	void NewTime()
	{
		if (App->pause)
			was_paused = true;
		else if (was_paused)
		{
			was_paused = false;
			pause_time_taken = true;
		}

		if (!was_paused && pause_time_taken)
		{
			Start((timer_duration - SDL_GetTicks()) / 1000);
			pause_time_taken = false;
		}
	}

	bool IsOver()
	{
		NewTime();

		if (timer_active && !App->pause)
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
	bool was_paused = false;
	bool pause_time_taken = false;
};

