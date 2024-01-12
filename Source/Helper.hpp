#pragma once
#include "raylib.h"

namespace Helper
{
	inline const float GetScreenHeightF() noexcept
	{
		return static_cast<float>(GetScreenHeight());
	}

	inline const float GetScreenWidthF() noexcept
	{
		return static_cast<float>(GetScreenWidth());
	}

	inline const float GetRandomValueF(int min, int max) noexcept
	{
		return static_cast<float>(GetRandomValue(min, max));
	}
}