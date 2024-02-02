#include "raylib.h"
#include "game.hpp"
#include "Window.hpp"
#include <print>

//TODO: Make use of the RAYLIB rec for collision
//TODO: Make use of the collision functions in RAYLIB

int main(void)
{
	constexpr int screenWidth = 1920;
	constexpr int screenHeight = 1080;

	try {
		Window window(screenWidth, screenHeight, "SPACE INVADERS", 60);
		Game game;

		while (!WindowShouldClose())
		{
			game.Input();
			game.Update();

			BeginDrawing();
			ClearBackground(BLACK);
			game.Render();
			EndDrawing();
		}
	}
	catch (const std::runtime_error& e) {
		std::println("Error: Game cannot run", e.what());
	}
	return 0;
}