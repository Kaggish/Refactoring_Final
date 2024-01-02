#pragma once
#include "raylib.h"

class Wall //TODO: Make into its own class
{
public:
	Vector2 position; //TODO: Initialize variables that are declared
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;
	float radius = 60;

	void Render(Texture2D texture);
	void Update();
};