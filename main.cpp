#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again
#include <iostream>
#include "components/neck.h"
#include "components/modal_chart.h"
#include "controller/menu.h"

// For window resizing
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define MAX(a, b) ((a)>(b)? (a) : (b))


int main()
{

    const int screenWidth =  2560;
    const int screenHeight = 1440;
    Color backgroundColor = RAYWHITE;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Guitar App");


    // Object inits
    //----------------------------------------------------------------------------------
    float guitarWidth = .8f;
    float guitarHeight = .4f;
    float guitarPosX = screenWidth * .5f;  // The ( * 0.5f) are basically scalars for the guitar's position
    float guitarPosY = screenHeight * .5f;

    Neck guitarNeck(screenWidth, screenHeight, guitarPosX, guitarPosY, guitarWidth, guitarHeight);
    ModalChart modalChart(screenWidth, screenHeight, screenWidth * .35f, screenHeight * .7f, .6f, .5f);
    // Menu menu(screenWidth, screenHeight, screenWidth * .8f, screenHeight * .7f, .2f, .4f);
    Menu menu(screenWidth, screenHeight, 0, screenHeight * .0001f, 1, .05f);


    // DrawText("Use mouse wheel to change font size", 20, 20, 10, GRAY);

    // Main game loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        // Compute required framebuffer scaling
        // TODO: This can be used to resize objects dynamically with the window size,
        // TODO: Needs to be called each frame, so I think it should be param for object methods
        float scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

        // For mouse interactions
        Vector2 mousePos = GetMousePosition();
        bool leftMouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        //guitarNeck.hover(mousePos);
//        modalChart.hover(mousePos);
//        menu.hover(mousePos, leftMouseClicked, modalChart);

        BeginDrawing();

        ClearBackground(backgroundColor);
        menu.setBackground(screenWidth, screenHeight);
        menu.drawTopMenu(screenWidth, screenHeight);  // TODO: Syncing issue between menu and display objects


        guitarNeck.drawGuitarNeck(scale);

        // TODO: Create if statement to swap between menus

        // TODO: canDraw value is changed by the menu button here
//        if (modalChart.canDraw) {
//            modalChart.drawModalChart(scale);
//        }
//        menu.drawMenu(scale);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    guitarNeck.destroy();
    modalChart.destroy();
    // menu.destroy();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
