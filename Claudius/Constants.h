#pragma once
#include "Color.h"
#include "string"
#include "Coords.h"

constexpr std::string_view WINDOW_NAME = "Snake";

constexpr int SQUARE_SIZE = 15;
constexpr bool FILLED_SQUARE = true;

constexpr int GRID_WIDTH  = 50;
constexpr int GRID_HEIGHT = 50;
constexpr Coords MIDDLE_COORDS = { .x = GRID_WIDTH / 2, .y = GRID_HEIGHT / 2 };
constexpr int SCREEN_WIDTH  = GRID_WIDTH * SQUARE_SIZE;
constexpr int SCREEN_HEIGHT = GRID_HEIGHT * SQUARE_SIZE;

constexpr float        TARGET_FPS = 20.0f;
constexpr unsigned int MS_BETWEEN_FRAMES = static_cast<unsigned int>(1000.0f / TARGET_FPS);

constexpr Color BACKGROUND_COLOR = Color(0, 0, 0, 0);
constexpr Color APPLE_COLOR      = Color(255, 0, 0, 0);
constexpr Color SNAKE_COLOR      = Color(0, 0, 255, 0);

constexpr int SNAKE_START_LENGTH = 3;

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

constexpr inline bool within_grid_brounds(const Coords& coords) noexcept
{
	return coords.x >= 0 && coords.x <= GRID_WIDTH && coords.y >= 0 && coords.y <= GRID_HEIGHT;
}