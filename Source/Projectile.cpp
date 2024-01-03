#include "Projectile.hpp"

Projectile::Projectile(Vector2 Position, EntityType Type)
	:position(Position)
	,type(Type)
{
	if (type == EntityType::ENEMY_PROJECTILE) {
		SPEED *= -1;
		position.y += 40;
	}
}

void Projectile::Update()
{
	position.y -= SPEED;

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