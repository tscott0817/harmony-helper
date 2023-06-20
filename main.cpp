#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION  // Avoid including raygui implementation again
#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
#include "components/guitar.h"
#include "components/piano.h"
#include "components/modal_chart.h"
#include "controller/menu.h"


// TODO: If using webassembly, probably don't need to check OS
/**
 * Check OS
 */
//#include <Windows.h>
//
//#ifdef _WIN32
//    const std::string operatingSystem = "Windows";
//#elif __APPLE__
//    const std::string operatingSystem = "macOS";
//#elif __linux__
//    const std::string operatingSystem = "Linux";
//#elif __unix__ // all unices not caught above
//    const std::string operatingSystem = "Unix";
//#else
//    const std::string operatingSystem = "Unknown";
//#endif


/**
 * For window resizing
 */
constexpr int MIN(int a, int b) {
    return (a < b) ? a : b;
}

constexpr int MAX(int a, int b) {
    return (a > b) ? a : b;
}

// TODO: These won't work if in separate class?
// void playSound(const std::vector<std::unique_ptr<Instrument>>& instrumentsVec, const std::vector<Sound>& notesSoundVec);
std::vector<Sound> initPianoAudio();
void unloadPianoAudio(std::vector<Sound> notesSoundVec);

int main()
{
    /** Window Setup **/
    // TODO: Check user's computer for their screen size and set window size accordingly
    const int screenWidth =  1280;
    const int screenHeight = 720;
//    const int screenWidth =  1920;  // Only for when using 2k settings
//    const int screenHeight = 1080;

    Color backgroundColor = RAYWHITE;  // Ignore error; I prefer knowing the type instead of 'auto'
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);  // Allows window to be resized
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Anti-aliasing for shape edges
    InitWindow(screenWidth, screenHeight, "Guitar App");
    SetExitKey(KEY_ZERO);  // Frees up escape key for menu, makes '0' exit program

    /** Object Inits **/
    Menu menu(screenWidth, screenHeight, 0, screenHeight * .0001f, 1, .05f);

    std::vector<std::unique_ptr<Instrument>> instrumentsVec;  // Holds all instruments
    float guitarWidth = .7f;
    float guitarHeight = .35f;
    float guitarPosX = .5f;  // The ( * 0.5f) are basically scalars for the guitar's position
    float guitarPosY = .8f;
    std::unique_ptr<Guitar> guitar = std::make_unique<Guitar>(screenWidth, screenHeight, guitarPosX, guitarPosY, guitarWidth, guitarHeight);
    instrumentsVec.emplace_back(std::move(guitar));

    float pianoWidth = .4f;
    float pianoHeight = .3f;
    float pianoPosX = .5f;
    float pianoPosY = .3f;
    std::unique_ptr<Piano> piano = std::make_unique<Piano>(screenWidth, screenHeight, pianoPosX, pianoPosY, pianoWidth, pianoHeight);
    instrumentsVec.emplace_back(std::move(piano));

    // InitAudioDevice();  // TODO: Not sure if best here in main, or if each class should have one

    /** Audio **/
    instrumentsVec[1]->initAudio();  // TODO: Just Piano has audio currently

    std::string instrSoundChoice = "Piano";  // TODO: Make this user assignable to choose sound

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

        /** Handles appropriate instrument functions to call **/
        for (const auto & instrument : instrumentsVec) {
            if (instrument->getCanDraw()) {  // Only allow interactions if menu has activated object
                instrument->selectNote(mousePos);  // Highlights chosen not on selected instrument
                instrument->notesActivate();  // Activates notes on the other non-selected instruments
                instrument->clickAndDrag(mousePos);
            }
        }

        // Check keyboard for escape key press
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu.canDraw = !menu.canDraw;
        }
        menu.hover(mousePos);

        /** Determines Which Objects Are Shown **/
        // Menu stuff
        // TODO: Need to make some boolean check in instruments to add locations or
        //  mouse interactions still work even if instruments is not visible
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
        for (const auto & instrument : instrumentsVec) {
            if (instrument->getCanDraw()) {
                instrument->draw(scale);  // Scale is not being used currently
            }
        }
        /** This will be a separate object, just for testing now **/
        if (GuiButton((Rectangle){screenWidth * .9f, screenHeight * .9f, screenWidth * .1f, screenHeight * .1f}, "Clear")) {
            for (const auto & instrument : instrumentsVec) {
                instrument->clearNotesShared();
            }
        }
        /** Create a second button that will read the sharedNotesVec and use PlaySound to play appropriate notes **/
        if (GuiButton((Rectangle){screenWidth * .9f, screenHeight * .8f, screenWidth * .1f, screenHeight * .1f}, "Play")) {
            if (instrSoundChoice == "Guitar") {
                instrumentsVec[0]->playSound();
            }
            else if (instrSoundChoice == "Piano") {
                instrumentsVec[1]->playSound();
            }
        }

        // TODO: Make this logic its own separate drop down menu for all scales
        // TODO: Do the same thing again for chords
        if (GuiButton((Rectangle){screenWidth * .9f, screenHeight * .7f, screenWidth * .1f, screenHeight * .1f}, "C Major")) {
            //newNotesVec.clear();  // TODO: Would prefer this as part of instrument class, but struggling to implement
            std::vector<std::string> newNotesVec;
            newNotesVec.emplace_back("C");
            newNotesVec.emplace_back("D");
            newNotesVec.emplace_back("E");
            newNotesVec.emplace_back("F");
            newNotesVec.emplace_back("G");
            newNotesVec.emplace_back("A");
            newNotesVec.emplace_back("B");
            for (const auto & instrument : instrumentsVec) {
                instrument->setNotesShared(newNotesVec);
            }
        }
        // Add another button for C Minor
        else if (GuiButton((Rectangle){screenWidth * .9f, screenHeight * .6f, screenWidth * .1f, screenHeight * .1f}, "C Minor")) {
            std::vector<std::string> newNotesVec;
            newNotesVec.emplace_back("C");
            newNotesVec.emplace_back("D");
            newNotesVec.emplace_back("Eb");
            newNotesVec.emplace_back("F");
            newNotesVec.emplace_back("G");
            newNotesVec.emplace_back("Ab");
            newNotesVec.emplace_back("Bb");
            for (const auto & instrument : instrumentsVec) {
                instrument->setNotesShared(newNotesVec);
            }
        }

        // Want Menu to be drawn last so it's on top
        menu.drawTopMenu(screenWidth, screenHeight);

        EndDrawing();
    }

    /** Object Destruction **/
    for (const auto & inst : instrumentsVec) {
        inst->destroy();
    }
    // CloseAudioDevice();
    instrumentsVec[1]->unloadAudio();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}