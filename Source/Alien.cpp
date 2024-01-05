#include "Alien.hpp"

Alien::Alien(Vector2 Position) noexcept
	:position(Position)
{}

void Alien::Update() noexcept
{
	position.x += (moveRight ? SPEED : -SPEED);

	moveRight = (position.x >= GetScreenWidth()) ? false : (position.x <= 0) ? true : moveRight;
	position.y += (position.x >= GetScreenWidth() || position.x <= 0) ? 50 : 0;
}

void Alien::Render(Texture2D texture) const noexcept
{
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), COLOR);
}