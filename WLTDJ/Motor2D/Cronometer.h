#pragma once
#include "j1Render.h"

class Cronometer
{
public:
	void Start(float amount_of_time) // Amount of time in seconds
	{
		timer_duration = SDL_GetTicks() + amount_of_time * 1000;
		timer_active = true;
	}
	bool IsOver()
	{
		if (timer_active)
		{
			if (timer_duration > SDL_GetTicks())
			{
				return false;
			}
			else
			{
				timer_active = false;
				return true;
			}
		}
		return true;
	}
private:
	int timer_duration;
	bool timer_active;
};

