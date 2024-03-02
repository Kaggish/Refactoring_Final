#pragma once
#include "raylib.h"

enum struct BulletType
{
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

class Projectile
{
	int SPEED = {};

public:
	Projectile(Vector2 Position, int speed) noexcept;

	Vector2 position = { 0, 0 };
	static constexpr float WIDTH = 7.0f;
	static constexpr float HEIGHT = 50.0f;

	bool active = true;

	Rectangle HitBox() const noexcept;

	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};
