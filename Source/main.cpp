#include "raylib.h"
#include "game.hpp"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{    
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

    SetTargetFPS(60);

    Game game = { State::MENU };
    Resources resources; //TODO: remove two-step initialization
    game.resources = resources;
    game.Launch();
    

    // Main game loop
    while (!WindowShouldClose())
    {

        game.Update();
      

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

       

        game.Render();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    std::string filename = "level.txt";  

    return 0;
}