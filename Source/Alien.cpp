#include "Alien.hpp"

Alien::Alien(Vector2 Position)
	:position(Position)
{}

void Alien::Update()
{
	if (moveRight)
	{
		position.x += SPEED;
	}
	else
	{
		position.x -= SPEED;
	}

	if (position.x >= GetScreenWidth())
	{
		moveRight = false;
		position.y += 50;
	}
	else if (position.x <= 0)
	{
		moveRight = true;
		position.y += 50;
	}
}

void Alien::Render(Texture2D texture)
{
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), COLOR);
}