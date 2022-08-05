#pragma once

struct Coords
{
	int x{}, y{};
	constexpr bool operator== (const Coords& other) const noexcept = default;
};

