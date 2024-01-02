#include "Player.hpp"


void Player::Initialize()
{
	float window_width = (float)GetScreenWidth();
	x_pos = window_width / 2;
}

void Player::Update()
{
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	x_pos += SPEED * direction;

	if (x_pos < 0 + radius)
	{
		x_pos = 0 + radius;
	}
	else if (x_pos > GetScreenWidth() - radius)
	{
		x_pos = GetScreenWidth() - radius;
	}

	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}
}

void Player::Render(Texture2D texture)
{
	float window_height = static_cast<float>(GetScreenHeight());
	DrawTexture(texture, static_cast<int>(x_pos), static_cast<int>(window_height - player_base_height), WHITE);
}