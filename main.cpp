#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "components/neck.h"
#include "components/modal_chart.h"

// For window resizing
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define MAX(a, b) ((a)>(b)? (a) : (b))

int main()
{

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Object sizes
    float guitarWidth = .7f;
    float guitarHeight = .3f;
    float guitarPosX = screenWidth * .5f;  // The ( * 0.5f) are basically scalars for the guitar's position
    float guitarPosY = screenHeight * .75f;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Guitar App");

    Neck guitarNeck(screenWidth, screenHeight, guitarPosX, guitarPosY, guitarWidth, guitarHeight);
    ModalChart modalChart(screenWidth, screenHeight, screenWidth * .5f, screenHeight * .3f, .6f, .5f);


    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {

        // Compute required framebuffer scaling
        // TODO: This can be used to resize objects dynamically with the window size,
        // TODO: This should probably be an argument of the constructor, but needs to be called each frame, so maybe put it in init()
        float scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

        //std::cout << textureSwap << std::endl;
        Vector2 mousePos = GetMousePosition();
        guitarNeck.hover(mousePos);
        modalChart.hover(mousePos);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        guitarNeck.drawGuitarNeck(scale);
        modalChart.drawModalChart(scale);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    guitarNeck.destroy();
    modalChart.destroy();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}