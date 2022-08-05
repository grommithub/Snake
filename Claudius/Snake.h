#pragma once

#include "Coords.h"
#include <vector>
#include "KeyCode.h"
#include "Constants.h"

class Snake
{
private:
	void move() noexcept;
	void move_head() noexcept;
	void update_snake_part_positions() noexcept;

	bool dead{};
	Direction current_direction = Direction::LEFT;
	Direction next_direction    = Direction::NONE;

public:
	Snake(unsigned int starting_length);

	void update() noexcept;
	void on_key_down(KeyCode key) noexcept;
	std::vector<Coords> snake_part_coords;

	inline Coords head_coords() const noexcept;
	inline size_t length() const noexcept;

	std::vector<Coords>::const_iterator begin() const noexcept;
	std::vector<Coords>::const_iterator end() const noexcept;

	void play_death_animation() noexcept;
	void add_part();
	void start_death_animation() noexcept;

	bool is_alive() const noexcept;
	bool should_die() noexcept;
	inline bool colliding_with_self() noexcept;
	inline bool finished_dying() const noexcept;
	inline bool waiting() const noexcept;
	bool is_longest_snake_possible() const noexcept;

};
