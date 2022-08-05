#pragma once
#include <vector>
#include "SDL_Resources.h"
#include "Snake.h"
#include "UpdateTimer.h"
#include <chrono>

class Game
{
	SDL_Initializer init;
	Window window;
	Renderer renderer;
	UpdateTimer timer;

	Snake snake;
	Coords apple_coords;
	
	void seed_random() const noexcept;

	Coords get_random_free_space() const noexcept;
	std::vector<Coords> all_available_squares() const;
	
	void print_result() const noexcept;

public:
	Game() noexcept(false) : renderer(window), snake(SNAKE_START_LENGTH)
	{
		seed_random();
		apple_coords = get_random_free_space();
	}

	void run();
	
	bool process_user_events() noexcept;
	void update();
	void render() noexcept;
	void on_key_down(KeyCode key) noexcept;


};


