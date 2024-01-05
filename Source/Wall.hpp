#pragma once
#include "raylib.h"

class Wall
{
public:
	Wall(Vector2 Position) noexcept;

	Vector2 position = {};
	int health = 50;
	bool active = true;
	float RADIUS = 45;

	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};
