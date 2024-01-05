#pragma once
#include "raylib.h"

class Player
{
	static constexpr int SPEED = 7;

public:
	Player(int PositionX) noexcept;

	int lives = 3;
	int PosX = 0;
	int RADIUS = 50;
	int direction = 0;
	int activeTexture = 0;
	const float player_base_height = 70.0f;
	float timer = 0;

	int Boundaries() noexcept;

	void Input() noexcept;
	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};