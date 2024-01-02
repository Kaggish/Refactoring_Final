#pragma once
#include "raylib.h"
#include "Helper.hpp"

class Player //TODO: Make into its own class
{
public:

	float x_pos = 0;
	float speed = 7;
	float player_base_height = 70.0f;
	float radius = 50;
	int lives = 3;
	int direction = 0; //We don´t need direction really we are moving only in the X-axis
	int activeTexture = 0;
	float timer = 0;

	EntityType type = EntityType::PLAYER;

	void Initialize(); //Make into a constructor
	void Render(Texture2D texture);
	void Update();
};