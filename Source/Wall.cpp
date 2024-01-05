#include "Wall.hpp"

Wall::Wall(Vector2 Position) noexcept
	:position(Position)
{}

void Wall::Render(Texture2D texture) const noexcept
{
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
	DrawText(TextFormat("%i", health), static_cast<int>(position.x + 10.0f), static_cast<int>(position.y + 50.0f), 20, RED);
}

void Wall::Update() noexcept
{
	if (health < 1)
	{
		active = false;
	}
}