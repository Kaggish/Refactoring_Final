#include "Window.hpp"

Window::Window(const int screenWidth, const int screenHeight, std::string_view title) noexcept
{
	InitWindow(screenWidth, screenHeight, title.data());
}

Window::~Window()
{
	CloseWindow();
}
