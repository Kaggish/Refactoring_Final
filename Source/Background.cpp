#include "BackGround.hpp"
#include "Helper.hpp"

using namespace Helper;

Star::Star(Vector2 Position, float Size) noexcept
	:position(Position)
	,size(Size)
{}

void Star::Render(float ScrollingOffset) const noexcept
{
	DrawCircleV({ position.x + (ScrollingOffset / size), position.y }, size, COLOR);
}

Background::Background() noexcept
{
	for (int i = 0; i < starAmmount; ++i)
	{
		Vector2 tmpPos = { GetRandomValueF(-150, GetScreenWidth() + 150), GetRandomValueF(0, GetScreenHeight()) };
		float tmpSize = GetRandomValueF(1, 8) / 2;

		stars.emplace_back(tmpPos, tmpSize);
	}
}

void Background::Update(float ScrollingOffset) noexcept
{
	scrollingOffset = ScrollingOffset;
}

void Background::Render() const noexcept
{
	for (const auto& star : stars)
	{
		star.Render(scrollingOffset);
	}
}