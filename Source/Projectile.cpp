#include "Projectile.hpp"

Projectile::Projectile(Vector2 Position, int speed) noexcept
	:position(Position)
	,SPEED(speed)
	,lineStart({position.x , -15.0f})
	,lineEnd({position.x, 15.0f})
{}

Rectangle Projectile::HitBox() const noexcept
{
	return Rectangle();
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
	DrawTextureV(texture, position, WHITE);
}