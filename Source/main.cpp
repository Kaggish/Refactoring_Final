#include "raylib.h"
#include "game.hpp"

int main(void)
{    
    const int screenWidth = 1280;
    const int screenHeight = 920;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

    SetTargetFPS(60);

    Game game;
    Resources resources;
    
    while (!WindowShouldClose())
    {

        game.Input();
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        game.Render();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}