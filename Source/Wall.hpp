#pragma once
#include "raylib.h"

class Wall
{
public:
	Wall(Vector2 Position);

	Vector2 position = {};
	int health = 50;
	bool active = true;
	float radius = 30;

	void Render(Texture2D texture);
	void Update();
};