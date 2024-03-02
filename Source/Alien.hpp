#pragma once
#include "raylib.h"

class Alien
{
	static constexpr Color COLOR = WHITE;
	static constexpr int SPEED = 2;
	static constexpr float WIDTH = 94.0f;
	static constexpr float HEIGHT = 54.0f;

public:
	Vector2 position = { 0, 0 };

	bool active = true;
	bool moveRight = true;

	Rectangle HitBox() const noexcept;

	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};
