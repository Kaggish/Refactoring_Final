#pragma once
#include "raylib.h"
#include "Helper.hpp"

using namespace Helper;

class Player
{
	static constexpr int SPEED = 7;
	static constexpr float WIDTH = 100.0f;
	static constexpr float HEIGHT = 100.0f;

public:
	float timer = 0;

	Vector2 position{ GetScreenWidthF() / 2.0f, GetScreenHeightF() - player_base_height};

	int lives = 3;
	int direction = 0;
	int activeTexture = 0;


	float Boundaries() noexcept;
	Rectangle HitBox() const noexcept;

	void Input() noexcept;
	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};