#pragma once
#include "raylib.h"

enum struct BulletType
{
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

class Projectile
{
	int SPEED = 15;

public:
	BulletType type = {};
	Projectile(Vector2 Position, BulletType type) noexcept;

	Vector2 position = { 0,0 };
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	bool active = true;

	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};
