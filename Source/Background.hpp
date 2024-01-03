#pragma once
#include "raylib.h"
#include <vector>

class Star
{
	static constexpr Color COLOR = SKYBLUE;
	Vector2 position = { 0, 0 };
	float size = 0;

public:

	Star(Vector2 Position, float Size);
	void Render(float ScrollingOffset) const noexcept;
};

class Background
{
public:
	Background();
	float scrollingOffset = 0.0f;
	const int starAmmount = 600;

	std::vector<Star> stars;
	void Update(float ScrollingOffset);
	void Render();
};
