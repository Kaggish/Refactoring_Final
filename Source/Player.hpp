#pragma once
#include "raylib.h"
#include "Helper.hpp"

class Player
{
	static constexpr int SPEED = 7;

public:
	Player(int PositionX);

	int lives = 3;
	int PosX = 0;
	int radius = 50;
	int direction = 0;
	int activeTexture = 0;
	const float player_base_height = 70.0f;
	float timer = 0;

	EntityType type = EntityType::PLAYER;

	int Boundaries();

	void Input();
	void Render(Texture2D texture);
	void Update();
};