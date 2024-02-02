#include "Window.hpp"

Window::Window(const int screenWidth, const int screenHeight, std::string_view title, unsigned int FPS) noexcept
{
	InitWindow(screenWidth, screenHeight, title.data());
	SetTargetFPS(FPS);
}

Window::~Window()
{
	CloseWindow();
}
