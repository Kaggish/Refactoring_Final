#pragma once
#include "raylib.h"
#include "Helper.hpp"

class Projectile //TODO: Make into its own class
{
	int SPEED = 15;

public:
	EntityType type = {};
	Projectile(Vector2 Position, EntityType Type);

	Vector2 position = { 0,0 };
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	bool active = true;

	void Update();
	void Render(Texture2D texture);
};
