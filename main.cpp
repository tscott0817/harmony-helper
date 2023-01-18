#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "components/neck.h"

// For window resizing
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define MAX(a, b) ((a)>(b)? (a) : (b))

int main(void)
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Guitar App");

    Vector2 squarePosition = { 50.0f, 600.0f };
    Vector2 squareSize = {80.0f, 80.0f};
    Color squareColor = DARKBLUE;

    Neck guitarNeck(screenWidth, screenHeight, .8f, .6f);


    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {

        // Compute required framebuffer scaling
        float scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

        // For mouse hovering
        if (GetMousePosition().x > squarePosition.x && GetMousePosition().x < squarePosition.x + (squareSize.x) &&
            GetMousePosition().y > squarePosition.y && GetMousePosition().y < squarePosition.y + (squareSize.y)) {
            squareColor = MAROON;
        }
        else {
            squareColor = DARKBLUE;
        }

        //std::cout << textureSwap << std::endl;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        guitarNeck.drawGuitarNeck(scale);
        DrawRectangleV(squarePosition, squareSize, squareColor);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    guitarNeck.destroy();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}