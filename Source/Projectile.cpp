#include "Projectile.hpp"

Projectile::Projectile(Vector2 Position, int speed) noexcept
	:position(Position)
	,SPEED(speed)
{}

Rectangle Projectile::HitBox() const noexcept
{
	return {position.x, position.y, WIDTH, HEIGHT};
}

void Projectile::Update() noexcept
{
	position.y -= SPEED;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(Texture2D texture) const noexcept
{
	DrawTextureV(texture, { position.x, position.y }, WHITE);
	DrawRectangleRec(HitBox(), RED);
}