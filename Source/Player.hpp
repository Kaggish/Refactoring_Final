#pragma once
#include "raylib.h"
#include "Helper.hpp"

using namespace Helper;

class Player
{
	static constexpr int SPEED = 7;

public:

	const float player_base_height = 70.0f;
	int lives = 3;
	Vector2 position{ GetScreenWidthF() / 2.0f, GetScreenHeightF() - player_base_height};
	const float RADIUS = 50.0f;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	float Boundaries() noexcept;
	Rectangle HitBox() const noexcept;

	void Input() noexcept;
	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};