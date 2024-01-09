#include "Player.hpp"

int Player::Boundaries() noexcept
{
	return PosX = (PosX < 0) ? 0 : (PosX > GetScreenWidth() - RADIUS) ? GetScreenWidth() - RADIUS : PosX;
}

void Player::Input() noexcept
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
}

void Player::Update() noexcept
{
	PosX += SPEED * direction;
	Boundaries();

	//Animate()
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

void Player::Render(Texture2D texture) const noexcept
{
	const float window_height = static_cast<float>(GetScreenHeight());
	DrawTexture(texture, static_cast<int>(PosX), static_cast<int>(window_height - player_base_height), WHITE);
}