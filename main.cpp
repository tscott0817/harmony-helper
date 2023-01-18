#include "raylib.h"
#include <iostream>
#include "components/neck.h"

//int drawGuitarNeck(Texture2D neckTexture, Rectangle boxRec, const int screenWidth, const int screenHeight, Vector2 boxCenter);


int main(void)
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Guitar App");

    Vector2 squarePosition = { 50.0f, 600.0f };
    Vector2 squareSize = {80.0f, 80.0f};
    Color squareColor = DARKBLUE;

    Neck guitarNeck(screenWidth, screenHeight, 800, 400);


    SetTargetFPS(60);


    // Texture swap
    int textureSwap = 0;

    // Main game loop
    while (!WindowShouldClose())
    {


        /** I think the x and y positions are the top left corners **/
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

        guitarNeck.drawGuitarNeck();
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