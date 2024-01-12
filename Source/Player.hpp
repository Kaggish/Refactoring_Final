#pragma once
#include "raylib.h"

inline const float GetScreenHeightF() noexcept
{
	return static_cast<float>(GetScreenHeight());
}

class Player
{
	static constexpr int SPEED = 7;

public:

	const float player_base_height = 70.0f;
	int lives = 3;
	Vector2 position{ static_cast<float>(GetScreenWidth() / 2), GetScreenHeightF() - player_base_height};
	const float RADIUS = 50.0f;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	float Boundaries() noexcept;

	void Input() noexcept;
	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};