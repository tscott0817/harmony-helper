#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION  // Avoid including raygui implementation again
#include <iostream>
#include "components/guitar.h"
#include "components/piano.h"
#include "components/modal_chart.h"
#include "controller/menu.h"

// For window resizing
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define MAX(a, b) ((a)>(b)? (a) : (b))

void attachConnection(Vector2 mousePos, Vector2 &bezierStart, Vector2 &bezierEnd, Rectangle startPos, Rectangle endPos, bool &canDrawConnection);
void drawConnection(Vector2 bezierStart, Vector2 &bezierEnd, Rectangle container, Rectangle startConnector, Rectangle endConnector, bool canDrawConnection, bool canDraw, bool menuActive, bool &stopBezier);

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
    //std::vector<Instrument> instrumentsVec;
    std::vector<std::unique_ptr<Instrument>> instrumentsVec;

    float guitarWidth = .7f;
    float guitarHeight = .35f;
    float guitarPosX = screenWidth * .5f;  // The ( * 0.5f) are basically scalars for the guitar's position
    float guitarPosY = screenHeight * .8f;
    Guitar guitarNeck(screenWidth, screenHeight, guitarPosX, guitarPosY, guitarWidth, guitarHeight);
    //instrumentsVec.push_back(guitarNeck);
    // Add the guitar to the vector of instruments
    instrumentsVec.push_back(std::make_unique<Guitar>(guitarNeck));

    float pianoWidth = .4f;
    float pianoHeight = .3f;
    float pianoPosX = screenWidth * .5f;
    float pianoPosY = screenHeight * .3f;
    Piano piano(screenWidth, screenHeight, pianoPosX, pianoPosY, pianoWidth, pianoHeight);
    //instrumentsVec.push_back(piano);
    instrumentsVec.push_back(std::make_unique<Piano>(piano));


    ModalChart modalChart(screenWidth, screenHeight, screenWidth * .35f, screenHeight * .7f, .6f, .5f);
    Menu menu(screenWidth, screenHeight, 0, screenHeight * .0001f, 1, .05f);

    /** Bezier Curve Tests **/
    //Vector2 bezierStart = {guitarNeck.getConnectionRec().x, guitarNeck.getConnectionRec().y};
    Vector2 bezierStart = {instrumentsVec[0]->getConnectionRec().x, instrumentsVec[0]->getConnectionRec().y};
    Vector2 bezierEnd = {0,0};
    Vector2 bezierStartPiano = {piano.getConnectionRec().x, guitarNeck.getConnectionRec().y};
    Vector2 bezierEndPiano = {0,0};
    bool canDrawConnection = false;
    bool menuActive = false;
    bool stopBezier = false;

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
        if (instrumentsVec[0]->getStateActive()) {
        //if (guitarNeck.getStateActive()) {
            //guitarNeck.hover(mousePos);
            //instrumentsVec[0].hover(mousePos);
            instrumentsVec[0]->hover(mousePos);
            instrumentsVec[0]->clickAndDrag(mousePos);
            //guitarNeck.clickAndDrag(mousePos);
        }
        piano.hover(mousePos);  // TODO: Want same if check as guitar
        piano.clickAndDrag(mousePos);
        // attachConnection(mousePos, bezierStartPiano, bezierEndPiano, piano.getConnectionRec(), guitarNeck.getConnectionRec(), canDrawConnection);
        //attachConnection(mousePos, bezierStart, bezierEnd, guitarNeck.getConnectionRec(), piano.getConnectionRec(), canDrawConnection);
        attachConnection(mousePos, bezierStart, bezierEnd, instrumentsVec[0]->getConnectionRec(), piano.getConnectionRec(), canDrawConnection);
        
        // Check keyboard for escape key press
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu.canDraw = !menu.canDraw;
        }
        menu.hover(mousePos);

        /** Determines Which Objects Are Shown **/
        // TODO: Don't want in main
        if (menu.isHovering) {
            // guitarNeck.setCanDrawConnection(false);
            menuActive = true;
        }
        else {
            menuActive = false;
        }
        // Guitar buttons
        if (menu.getActiveButtons()[0] == 0) {
            //guitarNeck.setCanDraw(false);
            instrumentsVec[0]->setCanDraw(false);
            canDrawConnection = false;  // TODO: Tied to guitarNeck, but want to remove if any object attached is destroyed
        }
        if (menu.getActiveButtons()[0] == 1) {
            //guitarNeck.setCanDraw(true);
            instrumentsVec[0]->setCanDraw(true);
        }
        // Piano buttons
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
        if (instrumentsVec[0]->getCanDraw()) {
        //if (guitarNeck.getCanDraw()) {
            //guitarNeck.draw(scale);
            //instrumentsVec[0].draw(scale);
            instrumentsVec[0]->draw(scale);
        }
        if (piano.getCanDraw()) {
            piano.draw(scale);
        }
        if (canDrawConnection) {
            // drawConnection(bezierStart, bezierEnd, guitarNeck.getContainer(), piano.getConnectionRec(), guitarNeck.getConnectionRec(), piano.getCanDrawConnection(), piano.getCanDraw(), menuActive, stopBezier);
//            drawConnection(bezierStart, bezierEnd, guitarNeck.getContainer(), guitarNeck.getConnectionRec(), piano.getConnectionRec(), guitarNeck.getCanDrawConnection(), guitarNeck.getCanDraw(), menuActive, stopBezier);
            drawConnection(bezierStart, bezierEnd, instrumentsVec[0]->getContainer(), instrumentsVec[0]->getConnectionRec(), piano.getConnectionRec(), instrumentsVec[0]->getCanDrawConnection(), instrumentsVec[0]->getCanDraw(), menuActive, stopBezier);

        }
        // Want Menu to be drawn last so it's on top
        menu.drawTopMenu(screenWidth, screenHeight);

        // TODO: Do the same for every object, stop hover interactions if using RayGUI
        if (menu.isHovering){  // Takes care of hovering issue between menu and guitars
            //guitarNeck.setStateActive(false);
            instrumentsVec[0]->setStateActive(false);
        }
        else {
            //guitarNeck.setStateActive(true);
            instrumentsVec[0]->setStateActive(true);
        }
        EndDrawing();
    }

    /** Object Destruction **/
    guitarNeck.destroy();
    //instrumentsVec[0]->destroy();
    piano.destroy();
    modalChart.destroy();
    // menu.destroy();  TODO: From before I used RayGUI
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

// TODO: Maybe make connection its own class, starting to clutter main
void attachConnection(Vector2 mousePos, Vector2 &bezierStart, Vector2 &bezierEnd, Rectangle startPos, Rectangle endPos, bool &canDrawConnection) {
    if (mousePos.x > startPos.x - (startPos.width * .5f) && mousePos.x < startPos.x + (startPos.width * .5f) &&
        mousePos.y > startPos.y - (startPos.height * .5f) && mousePos.y < startPos.y + (startPos.height * .5f)) {
        DrawRectangle(25, 25, 100, 100, RED);
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            canDrawConnection = true;
            bezierStart = {startPos.x, startPos.y};
            bezierEnd = {mousePos.x, mousePos.y};
        }
    }
}

// Bezier end pointer since it's being modified
void drawConnection(Vector2 bezierStart, Vector2 &bezierEnd, Rectangle container, Rectangle startConnector, Rectangle endConnector, bool canDrawConnection, bool canDrawBezier, bool menuActive, bool &stopBezier) {  // TODO: Take in objects to connect to? OR make separate connector class.
    Vector2 mousePos = GetMousePosition();  // TODO: Maybe pass in
    bezierStart.x = startConnector.x;
    bezierStart.y = startConnector.y;
    bool mouseHeld = false;

    if (mousePos.x == container.x && mousePos.y == container.y) {
        canDrawConnection = false;
    }
    else {
        canDrawConnection = true;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && canDrawConnection && !menuActive && !stopBezier) {
        bezierEnd = mousePos;
        mouseHeld = true;
        DrawLineBezier(bezierStart, bezierEnd, 2.0f, RED);
    }
    // If mouse is in the area of the end connector, allow attachment
    if (mousePos.x > endConnector.x - (endConnector.width * .5f) && mousePos.x < endConnector.x + (endConnector.width * .5f) &&
        mousePos.y > endConnector.y - (endConnector.height * .5f) && mousePos.y < endConnector.y + (endConnector.height * .5f) && !stopBezier) {
        stopBezier = true;
    }
    // If attachment to end point has been made, keep points at respective positions
    if (stopBezier) {
        // bezierEnd = {endConnector.x, endConnector.y - (endConnector.height * .5f)};
        bezierEnd.x = endConnector.x;
        bezierEnd.y = endConnector.y;
    }
    if (!mouseHeld) {
        DrawLineBezier(bezierStart, bezierEnd, 2.0f, RED);  // Keep bezier at end point when mouse not held anymore
    }
}
