#pragma once
#include <SDL.h>
#include "Constants.h"

struct UpdateTimer
{
	float        sec_delta_time = 0.0f;
	unsigned int ms_last_frame = 0;
	unsigned int ms_time_to_wait = 0;

	unsigned int ms_between_frames = MS_BETWEEN_FRAMES;

	void wait_for_time_to_update() noexcept
	{
		SDL_Delay(calculate_wait_time());
	}

	unsigned int calculate_wait_time() noexcept
	{
		ms_time_to_wait = SDL_GetTicks() - ms_last_frame + (ms_between_frames);
		return ms_time_to_wait;
	}
	float get_seconds_delta_time() const noexcept
	{
		return static_cast<float>(ms_time_to_wait) / 1000.0f;
	}
	void on_frame_complete() noexcept
	{
		ms_last_frame = SDL_GetTicks();
	}
};