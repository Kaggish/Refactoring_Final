#include "Projectile.hpp"

Projectile::Projectile(Vector2 Position, BulletType Type) noexcept
	:position(Position)
	,type(Type)
	,lineStart({position.x , -15.0f})
	,lineEnd({position.x, 15.0f})
{
	if (type == BulletType::ENEMY_PROJECTILE) {
		SPEED *= -1;
		position.y += 40;
	}
}

void Projectile::Update() noexcept
{
	position.y -= SPEED;

	lineStart.y = position.y;
	lineEnd.y = position.y;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(Texture2D texture) const noexcept
{
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}