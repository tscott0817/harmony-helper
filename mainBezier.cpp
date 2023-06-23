#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "rayguiCustom.h"
#undef RAYGUI_IMPLEMENTATION  // Avoid including raygui implementation again
#include <iostream>
#include "components/guitar.h"
#include "components/piano.h"
#include "components/modal_chart.h"
#include "controller/menu.h"

// For window resizing
//#define MIN(a, b) ((a)<(b)? (a) : (b))
//#define MAX(a, b) ((a)>(b)? (a) : (b))
constexpr int MIN(int a, int b) {
    return (a < b) ? a : b;
}

constexpr int MAX(int a, int b) {
    return (a > b) ? a : b;
}


void attachConnection(Vector2 mousePos, Vector2 &bezierStart, Vector2 &bezierEnd, Rectangle startPos, Rectangle endPos, bool &canDrawConnection);
void drawConnection(Vector2 bezierStart, Vector2 &bezierEnd, Rectangle container, Rectangle startConnector, Rectangle endConnector, bool canDrawConnectionInst, bool &canDrawBezier, bool menuActive, bool &stopBezier);

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
    std::vector<std::unique_ptr<Instrument>> instrumentsVec;

    float guitarWidth = .7f;
    float guitarHeight = .35f;
    float guitarPosX = .5f;  // The ( * 0.5f) are basically scalars for the guitar's position
    float guitarPosY = .8f;
    std::unique_ptr<Guitar> guitar = std::make_unique<Guitar>(screenWidth, screenHeight, guitarPosX, guitarPosY, guitarWidth, guitarHeight);
    instrumentsVec.push_back(std::move(guitar));

    float pianoWidth = .4f;
    float pianoHeight = .3f;
    float pianoPosX = .5f;
    float pianoPosY = .3f;
    std::unique_ptr<Piano> piano = std::make_unique<Piano>(screenWidth, screenHeight, pianoPosX, pianoPosY, pianoWidth, pianoHeight);
    instrumentsVec.push_back(std::move(piano));


    ModalChart modalChart(screenWidth, screenHeight, screenWidth * .35f, screenHeight * .7f, .6f, .5f);
    Menu menu(screenWidth, screenHeight, 0, screenHeight * .0001f, 1, .05f);

    /** Bezier Curve Tests **/
    Vector2 bezierStart = {instrumentsVec[0]->getConnectionRec().x, instrumentsVec[0]->getConnectionRec().y};
    Vector2 bezierEnd = {0,0};
    Vector2 bezierStartPiano = {instrumentsVec[1]->getConnectionRec().x, instrumentsVec[1]->getConnectionRec().y};
    Vector2 bezierEndPiano = {0,0};
    bool canDrawConnection = false;
    bool menuActive = false;
    bool stopBezier = false;

    InitAudioDevice();  // Need to enable audio
    Sound soundTest = LoadSound("../resources/audio/key13.ogg");

    /** Main Loop **/
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // TODO: This can be used to resize objects dynamically with the window size,
        // TODO: Needs to be called each frame, so I think it should be param for object methods
        float scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);
        if (IsKeyPressed(KEY_SPACE)){
            PlaySound(soundTest);
            std::cout << "Playing sound" << std::endl;
        }

        // For mouse interactions
        Vector2 mousePos = GetMousePosition();
        bool leftMouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        /** Object Interactions **/
        for (int i = 0; i < instrumentsVec.size(); i++) {
            if (instrumentsVec[i]->getStateActive()) {
                instrumentsVec[i]->hover(mousePos);
                instrumentsVec[i]->clickAndDrag(mousePos);
                instrumentsVec[i]->playSound(mousePos);
            }
        }

        attachConnection(mousePos, bezierStart, bezierEnd, instrumentsVec[0]->getConnectionRec(), instrumentsVec[1]->getConnectionRec(), canDrawConnection);
        
        // Check keyboard for escape key press
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu.canDraw = !menu.canDraw;
        }
        menu.hover(mousePos);

        /** Determines Which Objects Are Shown **/
        // TODO: Don't want in main
        if (menu.isHovering) {
            menuActive = true;
        }
        else {
            menuActive = false;
        }
        // Menu stuff
        for (int i = 0; i < instrumentsVec.size(); i++) {
            if (menu.getActiveButtons()[i] == 0) {
                instrumentsVec[i]->setCanDraw(false);
            }
            if (menu.getActiveButtons()[i] == 1) {
                instrumentsVec[i]->setCanDraw(true);
            }
        }

        /** Object Drawing Here  **/
        BeginDrawing();

        ClearBackground(backgroundColor);
        menu.setBackground(screenWidth, screenHeight);  // TODO: Probably don't want this in menu class

        // Draw Objects
        for (int i = 0; i < instrumentsVec.size(); i++) {
            if (instrumentsVec[i]->getCanDraw()) {
                instrumentsVec[i]->draw(scale);
            }
        }
        if (canDrawConnection) {
            std::cout << "Drawing Connection" << std::endl;
            drawConnection(bezierStart, bezierEnd, instrumentsVec[0]->getContainer(), instrumentsVec[0]->getConnectionRec(), instrumentsVec[1]->getConnectionRec(), instrumentsVec[0]->getCanDrawConnection(), canDrawConnection, menuActive, stopBezier);

        }
        // Want Menu to be drawn last so it's on top
        menu.drawTopMenu(screenWidth, screenHeight);

        // TODO: Do the same for every object, stop hover interactions if using RayGUI
        if (menu.isHovering){  // Takes care of hovering issue between menu and guitars
            instrumentsVec[0]->setStateActive(false);
            instrumentsVec[1]->setStateActive(false);
        }
        else {
            instrumentsVec[0]->setStateActive(true);
            instrumentsVec[1]->setStateActive(true);
        }
        EndDrawing();
    }

    /** Object Destruction **/
    //guitarNeck.destroy();
    //guitarNeck->destroy();
    //instrumentsVec[0]->destroy();
    //piano.destroy();
    instrumentsVec[1]->destroy();
    modalChart.destroy();
    // menu.destroy();  TODO: From before I used RayGUI
    UnloadSound(soundTest);
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

// TODO: Maybe make connection its own class, starting to clutter main
void attachConnection(Vector2 mousePos, Vector2 &bezierStart, Vector2 &bezierEnd, Rectangle startPos, Rectangle endPos, bool& canDrawConnection) {
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
void drawConnection(Vector2 bezierStart, Vector2 &bezierEnd, Rectangle container, Rectangle startConnector, Rectangle endConnector, bool canDrawConnectionInst, bool &canDrawBezier, bool menuActive, bool &stopBezier) {  // TODO: Take in objects to connect to? OR make separate connector class.
    Vector2 mousePos = GetMousePosition();  // TODO: Maybe pass in
    bezierStart.x = startConnector.x;
    bezierStart.y = startConnector.y;
    bool mouseHeld = false;
    
//    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && canDrawBezier && !menuActive && !stopBezier) {
//        bezierEnd = mousePos;
//        mouseHeld = true;
//        DrawLineBezier(bezierStart, bezierEnd, 2.0f, RED);
//    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && canDrawBezier && !stopBezier) {
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
