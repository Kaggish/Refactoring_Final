#pragma once
#include "raylib.h"

class Wall
{
public:
	static constexpr float RADIUS = 45;		
	Vector2 position = {};
	int health = 50;
	bool active = true;
	
	void Render(Texture2D texture) const noexcept;
};
