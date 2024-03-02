#pragma once
#include "raylib.h"
#include "Helper.hpp"

using namespace Helper;

class Player
{
	static constexpr int SPEED = 7;

public:
	float timer = 0;
	static constexpr float HEIGHT = 97.0f;
	static constexpr float WIDTH = 94.0f;

	Vector2 position{ GetScreenWidthF() / 2.0f, GetScreenHeightF() - HEIGHT};

	int lives = 3;
	int direction = 0;
	int activeTexture = 0;


	float Boundaries() noexcept;
	Rectangle HitBox() const noexcept;

	void Input() noexcept;
	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};