#pragma once
#include "raylib.h"

class Wall
{
public:
	static constexpr int WIDTH = 164;
	static constexpr int HEIGHT = 73;

	Vector2 position = {};

	int health = 50;

	bool active = true;
	
	Rectangle HitBox() const noexcept;

	void Render(Texture2D texture) const noexcept;
};
