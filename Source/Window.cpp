#include "Window.hpp"
#include <print>

Window::Window(const int screenWidth, const int screenHeight, std::string_view title) noexcept
{
	try
	{
		InitWindow(screenWidth, screenHeight, title.data());
	}
	catch(const std::runtime_error& e)
	{
		[[gsl::suppress(f.6)]]
		std::println("Error: Could not create window", e.what());
	}
}

Window::~Window()
{
	CloseWindow();
}
