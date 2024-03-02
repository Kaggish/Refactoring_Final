#include "Wall.hpp"

Rectangle Wall::HitBox() const noexcept
{
	return {position.x, position.y, WIDTH, HEIGHT};
}

void Wall::Render(Texture2D texture) const noexcept
{
	static constexpr auto LABEL_OFFSET_X = 10;
	static constexpr auto LABEL_OFFSET_Y = 50;
	const auto x = static_cast<int>(position.x);
	const auto y = static_cast<int>(position.y);
	DrawTextureV(texture, { position.x, position.y - HEIGHT }, WHITE);
	DrawText(TextFormat("%i", health), x + LABEL_OFFSET_X, y + LABEL_OFFSET_Y, 40, RED);
}