#include "Player.hpp"

Player::Player(int PositionX) noexcept
	:PosX(PositionX)
{}

int Player::Boundaries() noexcept
{
	if (PosX < 0)
	{
		return PosX = 0;
	}
	else if (PosX > GetScreenWidth() - RADIUS)
	{
		return PosX = GetScreenWidth() - RADIUS;
	}
	return PosX = PosX;
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