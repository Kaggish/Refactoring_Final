#include "Alien.hpp"

void Alien::Update() noexcept
{
	position.x += (moveRight ? SPEED : -SPEED);

	moveRight = (position.x >= GetScreenWidth()) ? false : (position.x <= 0) ? true : moveRight;
	position.y += (position.x >= GetScreenWidth() || position.x <= 0) ? 50 : 0;
}

void Alien::Render(Texture2D texture) const noexcept
{
	DrawTextureV(texture, {position.x - RADIUS, position.y - RADIUS}, COLOR);
}