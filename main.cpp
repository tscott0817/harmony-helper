#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "components/neck.h"
#include "components/modal_chart.h"
#include "components/menu.h"

// For window resizing
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define MAX(a, b) ((a)>(b)? (a) : (b))

int main()
{

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Object sizes
    float guitarWidth = .8f;
    float guitarHeight = .4f;
    float guitarPosX = screenWidth * .5f;  // The ( * 0.5f) are basically scalars for the guitar's position
    float guitarPosY = screenHeight * .2f;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Guitar App");

    Neck guitarNeck(screenWidth, screenHeight, guitarPosX, guitarPosY, guitarWidth, guitarHeight);
    ModalChart modalChart(screenWidth, screenHeight, screenWidth * .35f, screenHeight * .7f, .6f, .5f);
    Menu menu(screenWidth, screenHeight, screenWidth * .8f, screenHeight * .7f, .2f, .4f);


    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {

        // Compute required framebuffer scaling
        // TODO: This can be used to resize objects dynamically with the window size,
        // TODO: Needs to be called each frame, so I think it should be param for object methods
        float scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

        // For mouse interactions
        Vector2 mousePos = GetMousePosition();
        bool leftMouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        guitarNeck.hover(mousePos);
        modalChart.hover(mousePos);
        menu.hover(mousePos, leftMouseClicked);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        guitarNeck.drawGuitarNeck(scale);
        modalChart.drawModalChart(scale);
        menu.drawMenu(scale);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    guitarNeck.destroy();
    modalChart.destroy();
    menu.destroy();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}