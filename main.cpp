#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again
#include <iostream>
#include "components/neck.h"
#include "components/piano.h"
#include "components/modal_chart.h"
#include "controller/menu.h"

// For window resizing
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define MAX(a, b) ((a)>(b)? (a) : (b))

void attachConnection(Vector2 mousePos, Vector2 &bezierStart, Rectangle startPos, Rectangle endPos, bool &canDrawConnection);
void drawConnection(Vector2 bezierStart, Vector2 &bezierEnd, Rectangle container, bool canDrawConnection, bool canDraw);

int main()
{
    /** Window Setup **/
    const int screenWidth =  1920;
    const int screenHeight = 1080;
    Color backgroundColor = RAYWHITE;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Guitar App");
    SetExitKey(KEY_ZERO);  // Frees up escape key for menu, makes '0' exit program

    /** Object Inits **/
    float guitarWidth = .7f;
    float guitarHeight = .35f;
    float guitarPosX = screenWidth * .5f;  // The ( * 0.5f) are basically scalars for the guitar's position
    float guitarPosY = screenHeight * .8f;
    Neck guitarNeck(screenWidth, screenHeight, guitarPosX, guitarPosY, guitarWidth, guitarHeight);

    float pianoWidth = .4f;
    float pianoHeight = .3f;
    float pianoPosX = screenWidth * .5f;
    float pianoPosY = screenHeight * .3f;
    Piano piano(screenWidth, screenHeight, pianoPosX, pianoPosY, pianoWidth, pianoHeight);


    ModalChart modalChart(screenWidth, screenHeight, screenWidth * .35f, screenHeight * .7f, .6f, .5f);
    Menu menu(screenWidth, screenHeight, 0, screenHeight * .0001f, 1, .05f);

    /** Bezier Curve Tests **/
    Vector2 bezierStart = {guitarNeck.getConnectionRec().x, guitarNeck.getConnectionRec().y};
    Vector2 bezierEnd = {0,0};
    bool canDrawConnection = false;

    /** Main Loop **/
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // TODO: This can be used to resize objects dynamically with the window size,
        // TODO: Needs to be called each frame, so I think it should be param for object methods
        float scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

        // For mouse interactions
        Vector2 mousePos = GetMousePosition();
        bool leftMouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        /** Object Interactions **/
        if (guitarNeck.getStateActive()) {
            guitarNeck.hover(mousePos);
            guitarNeck.clickAndDrag(mousePos);
        }
        piano.hover(mousePos);  // TODO: Want same if check as guitar
        piano.clickAndDrag(mousePos);
        attachConnection(mousePos, bezierStart, guitarNeck.getConnectionRec(), guitarNeck.getConnectionRec(), canDrawConnection);

        // Check keyboard for escape key press
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu.canDraw = !menu.canDraw;
        }
        menu.hover(mousePos);

        /** Determines Which Objects Are Shown **/
        // TODO: Don't want in main
        if (menu.isHovering) {
            // guitarNeck.setCanDrawConnection(false);
            canDrawConnection = false;
        }
        if (menu.getActiveButtons()[0] == 0) {
            guitarNeck.setCanDraw(false);
        }
        if (menu.getActiveButtons()[0] == 1) {
            guitarNeck.setCanDraw(true);
        }
        if (menu.getActiveButtons()[1] == 0) {
            piano.setCanDraw(false);
        }
        if (menu.getActiveButtons()[1] == 1) {
            piano.setCanDraw(true);
        }

        /** Object Drawing Here  **/
        BeginDrawing();

        ClearBackground(backgroundColor);
        menu.setBackground(screenWidth, screenHeight);  // TODO: Probably don't want this in menu class

        // Draw Objects
        if (guitarNeck.getCanDraw()) {
            guitarNeck.drawGuitarNeck(scale);
        }
        if (piano.getCanDraw()) {
            piano.drawPiano(scale);
        }
        if (canDrawConnection) {
            drawConnection(bezierStart, bezierEnd, guitarNeck.getContainer(), guitarNeck.getCanDrawConnection(), guitarNeck.getCanDraw());
        }
        // Want Menu to be drawn last so it's on top
        menu.drawTopMenu(screenWidth, screenHeight);

        // TODO: Do the same for every object, stop hover interactions if using RayGUI
        if (menu.isHovering){  // Takes care of hovering issue between menu and guitars
            guitarNeck.setStateActive(false);
        }
        else {
            guitarNeck.setStateActive(true);
        }
        EndDrawing();
    }

    /** Object Destruction **/
    guitarNeck.destroy();
    piano.destroy();
    modalChart.destroy();
    // menu.destroy();  TODO: From before I used RayGUI
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

void attachConnection(Vector2 mousePos, Vector2 &bezierStart, Rectangle startPos, Rectangle endPos, bool &canDrawConnection) {
    // Check if mouse is within the area of the connection point
    if (mousePos.x > startPos.x - (startPos.width * .5f) && mousePos.x < startPos.x + (startPos.width * .5f) &&
        mousePos.y > startPos.y - (startPos.height * .5f) && mousePos.y < startPos.y + (startPos.height * .5f)) {
        DrawRectangle(25, 25, 100, 100, RED);
//        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) canDrawConnection = true; bezierStart = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) canDrawConnection = true; bezierStart = {startPos.x, startPos.y};

    }
}

void drawConnection(Vector2 bezierStart, Vector2 &bezierEnd, Rectangle container, bool canDrawConnection, bool canDrawBezier) {  // TODO: Take in objects to connect to? OR make separate connector class.
    Vector2 mousePos = GetMousePosition();
    bezierStart.x = container.x;
    bezierStart.y = container.y - (container.height * .55f);
    bool mouseHeld = false;

    if (mousePos.x == container.x && mousePos.y == container.y) {
        canDrawConnection = false;
    }
    else {
        canDrawConnection = true;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && canDrawConnection) {
        bezierEnd = mousePos;
        mouseHeld = true;
        DrawLineBezier(bezierStart, bezierEnd, 2.0f, RED);
    }
    if (!mouseHeld) {
        DrawLineBezier(bezierStart, bezierEnd, 2.0f, RED);
    }
}
