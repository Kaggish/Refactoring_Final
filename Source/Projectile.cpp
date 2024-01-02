#include "Projectile.hpp"

void Projectile::Update()
{
	position.y -= speed;

	// UPDATE LINE POSITION
	lineStart.y = position.y - 15;
	lineEnd.y = position.y + 15;

	lineStart.x = position.x;
	lineEnd.x = position.x;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(Texture2D texture)
{
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}