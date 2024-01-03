#include "Wall.hpp"

Wall::Wall(Vector2 Position)
	:position(Position)
{}

void Wall::Render(Texture2D texture)
{
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
	DrawText(TextFormat("%i", health), static_cast<int>(position.x + 15.0f), static_cast<int>(position.y + 50.0f), 20, RED);
}

void Wall::Update()
{
	if (health < 1)
	{
		active = false;
	}
}