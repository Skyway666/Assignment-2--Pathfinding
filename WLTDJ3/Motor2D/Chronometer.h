#pragma once
#include "j1Render.h"

class Chronometer
{
public:

	void Start(float amount_of_time) // Amount of time in seconds
	{
		time = amount_of_time * 1000;
		timer_duration = SDL_GetTicks() + time;
		timer_active = true;
	}

	bool IsOver()
	{
		if (timer_duration > SDL_GetTicks())
			return false;
		else
		{
			timer_active = false;
			return true;
		}
	}

	void Reset()
	{
		timer_duration = 0;
		timer_active = true;
	}

	void Pause()
	{
		if (!been_paused)
			pause_time = timer_duration - SDL_GetTicks();

		been_paused = true;
	}

	void StartAfterPause()
	{
		if (been_paused)
		{
			timer_duration = SDL_GetTicks() + pause_time;
			timer_active = true;
		}
	}

	void ResetPause()
	{
		been_paused = false;
	}

	int Read()
	{
		return timer_duration;
	}

private:

	float	time = 0;
	float	pause_time = 0;
	int		timer_duration = 0;
	bool	timer_paused = false;
	bool	timer_active = false;
	bool	been_paused = false;
};

