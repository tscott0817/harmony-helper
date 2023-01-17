#include "raylib.h"
#include <iostream>

int drawGuitarNeck(Texture2D neckTexture, Rectangle boxRec, const int screenWidth, const int screenHeight, Vector2 boxCenter);

int main(void)
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - mouse input");

    Vector2 squarePosition = { 50.0f, 600.0f };
    Vector2 squareSize = {80.0f, 80.0f};
    Color squareColor = DARKBLUE;

    Image neckImage = LoadImage("../wood.png");     // Loaded in CPU memory (RAM)
    Texture2D neckTexture = LoadTextureFromImage(neckImage);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(neckImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    //Rectangle boxRec = (0, 0, texture.width, texture.height);
    Rectangle boxRec = {0, 0, static_cast<float>(neckTexture.width), static_cast<float>(neckTexture.height)};
    Vector2 boxCenter = { 50.0f, 200.0f };


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

        std::cout << textureSwap << std::endl;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        /**
         * Neck:
         *   width = 80% of screen size
         *   height = 20% of screen height
         *
         *
         *
         * **/
        drawGuitarNeck(neckTexture, boxRec, screenWidth, screenHeight, boxCenter);
        DrawRectangleV(squarePosition, squareSize, squareColor);



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadTexture(neckTexture);       // Texture unloading
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


// TODO: Will want this to be its own object, these params will be class variables instead (except texture maybe)
int drawGuitarNeck(Texture2D neckTexture, Rectangle boxRec, const int screenWidth, const int screenHeight, Vector2 boxCenter) {
    DrawTexturePro(neckTexture,
                   boxRec,
                   (Rectangle) {screenWidth * .1f, boxCenter.y + 50, screenWidth * .8f, screenHeight * .2f},  /** Params = (x-pos, y-pos, height, width) **/
                   boxCenter, 0, WHITE);

    // TODO: Not sure if I should do this or just make void method
    return 0;
}