#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION  // Avoid including raygui implementation again
#include <iostream>
#include "components/guitar.h"
#include "components/piano.h"
#include "components/modal_chart.h"
#include "controller/menu.h"


/**
 * For window resizing
 * @param a
 * @param b
 * @return
 */
constexpr int MIN(int a, int b) {
    return (a < b) ? a : b;
}

constexpr int MAX(int a, int b) {
    return (a > b) ? a : b;
}


int main()
{

    // Note manager
    // Create a vector of all musical notes
    std::vector<std::string> allNotesVec = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
    /** Window Setup **/
//    const int screenWidth =  1920;  // Only for when using 2k settings
//    const int screenHeight = 1080;
    const int screenWidth =  1280;
    const int screenHeight = 720;
    Color backgroundColor = RAYWHITE;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Guitar App");
    SetExitKey(KEY_ZERO);  // Frees up escape key for menu, makes '0' exit program

    /** Object Inits **/
    std::vector<std::unique_ptr<Instrument>> instrumentsVec;  // Holds all instruments

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


    Menu menu(screenWidth, screenHeight, 0, screenHeight * .0001f, 1, .05f);


    // Used to stop hovering at same time as over objects
    bool menuActive = false;

    std::vector<std::string> currNotesVec;
    // Fill current notes with empty strings
    for (int i = 0; i < 50; i++) {
        currNotesVec.emplace_back("X");
    }
    // print current notes
    for (int i = 0; i < currNotesVec.size(); i++) {
        std::cout << currNotesVec[i] << std::endl;
    }

    InitAudioDevice();  // TODO: Not sure if best here in main, or if each class should have one
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
        // This is from guitar to Piano
        currNotesVec = instrumentsVec[0]->getSelectedNotes();  // TODO: Do this for each instrument
        std::cout << "\nNotes Currently Selected" << std::endl;
        for (int i = 0; i < currNotesVec.size(); i++) {
            std::cout << currNotesVec[i] << std::endl;

        }

        // use setActiveNotes from Piano to set notes selected in Guitar
        instrumentsVec[1]->setActiveNotes(currNotesVec);


        /** Call most things here **/
        for (int i = 0; i < instrumentsVec.size(); i++) {
            if (instrumentsVec[i]->getStateActive()) {
                //instrumentsVec[i]->hover(mousePos);
                instrumentsVec[i]->soundTests();
                instrumentsVec[i]->clickColorHold(mousePos);
                instrumentsVec[i]->clickAndDrag(mousePos);
                instrumentsVec[i]->notesActivate();
            }
        }

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

        /** Test for note sharing between classes **/


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
    instrumentsVec[1]->destroy();  // TODO: Loop through entire instrument vec instead
    //UnloadSound(soundTest);
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
