//Daniel Burt,  11/03/2022

#include "Game.h"
#include <algorithm>
#include <iostream>

#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
//I would use gsl_narrow but the gsl nuget package is deprecated and generates errors
void Game::seed_random() const noexcept
{
	const unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	srand(seed);
}
#pragma warning(pop)

void Game::run()
{
	while (true)
	{
		
		timer.wait_for_time_to_update();

		if (snake.finished_dying()) break;
		if (!process_user_events()) break;
		update();
		render();

		timer.on_frame_complete();
	}
}

/*
	Returns false if user requests quit
	else returns true
*/
inline bool Game::process_user_events() noexcept
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:    return false;
			case SDL_KEYDOWN: on_key_down(TranslateKeyCode(e.key.keysym.sym)); continue;
			default:break;
		}
	}
	return true;
}

void Game::update()
{
	if (snake.is_alive() && snake.should_die())
	{
		snake.start_death_animation();
		print_result();
	}
	if (snake.head_coords() == apple_coords)
	{
		snake.add_part();
		apple_coords = get_random_free_space();
	}
	snake.update();
}

void Game::render() noexcept
{
	renderer.render(apple_coords, APPLE_COLOR);
	for (const auto& part : snake.snake_part_coords)
	{
		renderer.render(part, SNAKE_COLOR);
	}
	renderer.present();
}


std::vector<Coords> Game::all_available_squares() const
{
	std::vector<Coords> available_squares;
	available_squares.reserve(GRID_HEIGHT * GRID_WIDTH - snake.length());
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			const auto coord = Coords(x, y);
			if (std::none_of(snake.begin(), snake.end(), [coord](const Coords& part_coord) noexcept { return coord == part_coord; }))
			{
				available_squares.push_back(coord);
			}
		}
	}
	return available_squares;
}

Coords Game::get_random_free_space() const noexcept
{
	try
	{
		const std::vector<Coords> available_squares = all_available_squares();
		return available_squares.at(rand() % available_squares.size());
	}
	catch (...)
	{
		return Coords{rand() % GRID_WIDTH, rand() % GRID_HEIGHT};
	}
}

void Game::print_result() const noexcept
{
	try
	{
		std::cout << "Game Over!\n\nYour snake reached a length of: " << snake.length() << "\n\n";
		if (snake.is_longest_snake_possible())
		{
			std::cout << "Wow! That's the highest score possible\n\n";
		}
	}
	catch (...) {}
}

void Game::on_key_down(KeyCode key) noexcept
{
	snake.on_key_down(key);
}


