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
    SetExitKey(KEY_ZERO);  // Frees up escape key for menu, makes '0' exit program


    // Object inits
    //----------------------------------------------------------------------------------
    float guitarWidth = .8f;
    float guitarHeight = .4f;
    float guitarPosX = screenWidth * .5f;  // The ( * 0.5f) are basically scalars for the guitar's position
    float guitarPosY = screenHeight * .5f;

    Neck guitarNeck(screenWidth, screenHeight, guitarPosX, guitarPosY, guitarWidth, guitarHeight);
    guitarNeck.stateActive = true; // To decide which object get draw on start of program
    ModalChart modalChart(screenWidth, screenHeight, screenWidth * .35f, screenHeight * .7f, .6f, .5f);
    Menu menu(screenWidth, screenHeight, 0, screenHeight * .0001f, 1, .05f);


    // Main loop
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

        /** Object Interactions **/
        if (guitarNeck.stateActive) {
            guitarNeck.hover(mousePos);
            guitarNeck.clickAndDrag(mousePos);
        }

        // Check keyboard for escape key press
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu.canDraw = !menu.canDraw;
        }


        /** Object Drawing Here  **/
        BeginDrawing();

        ClearBackground(backgroundColor);
        menu.setBackground(screenWidth, screenHeight);  // TODO: Probably don't want this in menu class

        /** Determines Which Objects Are Shown **/
        if (menu.canDraw) {
            menu.drawTopMenu(screenWidth, screenHeight);  // TODO: Syncing issue between menu and display objects
            guitarNeck.stateActive = false;  // Disallow hovering on all except menu
        }
        else {
            guitarNeck.stateActive = true;
        }


        // Change objects based on menu button clicks
        if (menu.getActiveButton() == 0) {
            guitarNeck.drawGuitarNeck(scale);
        }

        if (menu.getActiveButton() == 1) {
            modalChart.drawModalChart(scale);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    guitarNeck.destroy();
    modalChart.destroy();
    // menu.destroy();  TODO: From before I used RayGUI
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
