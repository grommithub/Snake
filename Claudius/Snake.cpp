#include "Snake.h"
#include "Coords.h"
#include "Constants.h"
#include <algorithm>

Snake::Snake(unsigned int starting_length)
{
	for (unsigned int i = 0; i < starting_length; i++)
	{
		snake_part_coords.push_back(Coords(MIDDLE_COORDS.x + i, MIDDLE_COORDS.y));
	}
}

void Snake::update() noexcept
{
	if (waiting()) return;

	if (dead)
	{
		if (!finished_dying())
		{
			play_death_animation();
		}
		return;
	}
	move();
}

void Snake::on_key_down(KeyCode key) noexcept
{
	if ((key == KeyCode::W || key == KeyCode::UP_ARROW) && current_direction != Direction::DOWN)
	{
		next_direction = Direction::UP;
	}
	if ((key == KeyCode::S || key == KeyCode::DOWN_ARROW) && current_direction != Direction::UP)
	{
		next_direction = Direction::DOWN;
	}
	if ((key == KeyCode::A || key == KeyCode::LEFT_ARROW) && current_direction != Direction::RIGHT)
	{
		next_direction = Direction::LEFT;
	}
	if ((key == KeyCode::D || key == KeyCode::RIGHT_ARROW) && current_direction != Direction::LEFT)
	{
		next_direction = Direction::RIGHT;
	}
}
inline size_t Snake::length() const noexcept
{
	return snake_part_coords.size();
}

std::vector<Coords>::const_iterator Snake::begin() const noexcept
{
	return snake_part_coords.begin();
}

std::vector<Coords>::const_iterator Snake::end() const noexcept
{
	return snake_part_coords.end();
}


bool Snake::is_alive() const noexcept
{
	return !dead;
}


void Snake::add_part()
{
	snake_part_coords.push_back(Coords(snake_part_coords.back()));
}

bool Snake::is_longest_snake_possible() const noexcept
{
	return length() >= GRID_WIDTH * GRID_HEIGHT;
}


inline Coords Snake::head_coords() const noexcept
{
	return snake_part_coords.front();
}

inline bool Snake::waiting() const noexcept
{
	return next_direction == Direction::NONE;
}

void Snake::start_death_animation() noexcept
{
	dead = true;
}

inline void Snake::move() noexcept
{
	current_direction = next_direction; 
	update_snake_part_positions();
	move_head();
}

void Snake::move_head() noexcept
{
	switch (current_direction)
	{
	case Direction::UP:
		snake_part_coords.front().y--;
		break;
	case Direction::DOWN:
		snake_part_coords.front().y++;
		break;
	case Direction::LEFT:
		snake_part_coords.front().x--;
		break;
	case Direction::RIGHT:
		snake_part_coords.front().x++;
		break;
	default:
		break;
	}
}

void Snake::update_snake_part_positions() noexcept
{
	std::shift_right(snake_part_coords.begin(), snake_part_coords.end(), 1);
}

bool Snake::colliding_with_self() noexcept
{
	for (const auto& part : snake_part_coords)
	{
		if (&part == &snake_part_coords.front()) continue;
		if (head_coords() == part)
		{
			return true;
		}
	}
	return false;
}

bool Snake::should_die() noexcept
{
	return !within_grid_brounds(head_coords()) || colliding_with_self();
}



bool Snake::finished_dying() const noexcept
{
	return snake_part_coords.empty();
}

void Snake::play_death_animation() noexcept
{
	snake_part_coords.pop_back();
}

