#include "Player.hpp"

float Player::Boundaries() noexcept
{
	return position.x = (position.x < 0) ? 0 : (position.x > GetScreenWidth() - RADIUS) ? GetScreenWidth() - RADIUS : position.x;
}

Rectangle Player::HitBox() const noexcept
{
	return {position.x, position.y, WIDTH, HEIGHT};
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
	position.x += SPEED * direction;
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
	DrawTextureV(texture, { position.x - RADIUS, position.y - RADIUS }, WHITE);
}