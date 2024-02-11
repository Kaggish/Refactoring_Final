#pragma once
#include "raylib.h"

class Wall
{
public:
	static constexpr float RADIUS = 60;		
	Vector2 position = {};
	int health = 50;
	bool active = true;
	
	Rectangle HitBox() const noexcept;

	void Render(Texture2D texture) const noexcept;
};
