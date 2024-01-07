#pragma once

#include "raylib.h"
#include <string_view>

class Window
{
public:
	Window(const int screenWidth, const int screenHeight, std::string_view title) noexcept;
	~Window();

	Window(const Window& other) = delete;
	Window operator= (const Window& other) = delete;
	Window(const Window&& other) = delete;
	Window operator= (const Window&& other) = delete;

};
