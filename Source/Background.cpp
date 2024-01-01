#include "BackGround.hpp"

Star::Star(Vector2 Position, float Size)
	:position(Position)
	, size(Size)
{}

void Star::Render(float ScrollingOffset) const noexcept
{
	DrawCircle(static_cast<int>(position.x + (ScrollingOffset / size)), static_cast<int>(position.y), size, COLOR);
}

void Background::AtStart()
{
	for (int i = 0; i < starAmmount; ++i)
	{
		Vector2 tmpPos{ static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150)), static_cast<float>(GetRandomValue(0, GetScreenHeight())) };
		float tmpSize = static_cast<float>(GetRandomValue(1, 8) / 2);

		stars.emplace_back(tmpPos, tmpSize);
	}
}

void Background::Update(float ScrollingOffset)
{
	scrollingOffset = ScrollingOffset;
}

void Background::Render()
{
	for (const auto& star : stars)
	{
		star.Render(scrollingOffset);
	}
}