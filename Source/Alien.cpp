#include "Alien.hpp"

Rectangle Alien::HitBox() const noexcept
{
	return {position.x, position.y, WIDTH, HEIGHT};
}

void Alien::Update() noexcept
{
	position.x += (moveRight ? SPEED : -SPEED);

	moveRight = (position.x >= GetScreenWidth()) ? false : (position.x <= 0) ? true : moveRight;
	position.y += (position.x >= GetScreenWidth() || position.x <= 0) ? 50 : 0;
}

void Alien::Render(Texture2D texture) const noexcept
{
	DrawTextureV(texture, {position.x, position.y}, COLOR);
}