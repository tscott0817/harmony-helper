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

    InitAudioDevice();  // TODO: Not sure if best here in main, or if each class should have one
    // Sound fxWav = LoadSound("resources/sound.wav");         // Load WAV audio file
    Sound noteC = LoadSound("../resources/audio/key08.ogg");  // TODO: Not sure why I have to go up a folder
    Sound noteDb = LoadSound("../resources/audio/key09.ogg");  // TODO: Not sure why I have to go up a folder
    Sound noteD = LoadSound("../resources/audio/key10.ogg");  // TODO: Not sure why I have to go up a folder
    Sound noteEb = LoadSound("../resources/audio/key11.ogg");
    Sound noteE = LoadSound("../resources/audio/key12.ogg");
    Sound noteF = LoadSound("../resources/audio/key13.ogg");
    Sound noteGb = LoadSound("../resources/audio/key14.ogg");
    Sound noteG = LoadSound("../resources/audio/key15.ogg");
    Sound noteAb = LoadSound("../resources/audio/key16.ogg");
    Sound noteA = LoadSound("../resources/audio/key17.ogg");
    Sound noteBb = LoadSound("../resources/audio/key18.ogg");
    Sound noteB = LoadSound("../resources/audio/key19.ogg");

    std::vector<Sound> notesSoundVec;
    notesSoundVec.emplace_back(noteC);
    notesSoundVec.emplace_back(noteDb);
    notesSoundVec.emplace_back(noteD);
    notesSoundVec.emplace_back(noteEb);
    notesSoundVec.emplace_back(noteE);
    notesSoundVec.emplace_back(noteF);
    notesSoundVec.emplace_back(noteGb);
    notesSoundVec.emplace_back(noteG);
    notesSoundVec.emplace_back(noteAb);
    notesSoundVec.emplace_back(noteA);
    notesSoundVec.emplace_back(noteBb);
    notesSoundVec.emplace_back(noteB);

    /** Main Loop **/
    SetTargetFPS(60);
    std::vector<std::string> newNotesVec;  // TODO: Don't like this here
    while (!WindowShouldClose())
    {

        // TODO: Sound tests
        // if (IsKeyPressed(KEY_SPACE)) PlaySound(noteOgg);

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
            for (const auto & instrument : instrumentsVec) {
                for (const auto &note: instrument->getNotesShared()) {
                    if (note == "C") {
                        PlaySound(notesSoundVec[0]);
                    }
                    if (note == "Db") {
                        PlaySound(notesSoundVec[1]);
                    }
                    if (note == "D") {
                        PlaySound(notesSoundVec[2]);
                    }
                    if (note == "Eb") {
                        PlaySound(notesSoundVec[3]);
                    }
                    if (note == "E") {
                        PlaySound(notesSoundVec[4]);
                    }
                    if (note == "F") {
                        PlaySound(notesSoundVec[5]);
                    }
                    if (note == "Gb") {
                        PlaySound(notesSoundVec[6]);
                    }
                    if (note == "G") {
                        PlaySound(notesSoundVec[7]);
                    }
                    if (note == "Ab") {
                        PlaySound(notesSoundVec[8]);
                    }
                    if (note == "A") {
                        PlaySound(notesSoundVec[9]);
                    }
                    if (note == "Bb") {
                        PlaySound(notesSoundVec[10]);
                    }
                    if (note == "B") {
                        PlaySound(notesSoundVec[11]);
                    }
                }
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
    UnloadSound(noteC);     // Unload sound data
    UnloadSound(noteDb);     // Unload sound data
    UnloadSound(noteD);     // Unload sound data
    UnloadSound(noteEb);     // Unload sound data
    UnloadSound(noteE);     // Unload sound data
    UnloadSound(noteF);     // Unload sound data
    UnloadSound(noteGb);     // Unload sound data
    UnloadSound(noteG);     // Unload sound data
    UnloadSound(noteAb);     // Unload sound data
    UnloadSound(noteA);     // Unload sound data
    UnloadSound(noteBb);     // Unload sound data
    UnloadSound(noteB);     // Unload sound data
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
