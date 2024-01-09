#pragma once
#include "raylib.h"

class Alien
{
	static constexpr Color COLOR = WHITE;
	static constexpr int SPEED = 2;

public:
	Vector2 position = { 0, 0 };
	static constexpr float RADIUS = 30;

	bool active = true;
	bool moveRight = true;

	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};
