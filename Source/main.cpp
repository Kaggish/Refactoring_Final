#include "raylib.h"
#include "game.hpp"
#include "Window.hpp"
#include <print>

int main(void)
{
	constexpr int screenWidth = 1280;
	constexpr int screenHeight = 920;
	try {
		Window window(screenWidth, screenHeight, "SPACE INVADERS");
		Game game;
		Resources resources;

		SetTargetFPS(60);

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