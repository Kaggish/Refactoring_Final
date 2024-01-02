#pragma once
#include "raylib.h"
#include "Helper.hpp"

class Alien
{
	static constexpr Color COLOR = WHITE;
	static constexpr int SPEED = 2;

public:

	Alien(Vector2 Position);
	Vector2 position = { 0, 0 };
	static constexpr float radius = 30;

	bool active = true;
	bool moveRight = true;

	EntityType type = EntityType::ENEMY;


	void Update();
	void Render(Texture2D texture);
};
