#ifndef GUITAR_APP_CHORDMENU_H
#define GUITAR_APP_CHORDMENU_H
#include "raylib.h"
#define RAYGUI_STATIC
#include "../raygui.h"
#undef RAYGUI_STATIC
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../components/instrument.h"

class ChordMenu {

private:

    Rectangle container;
    Vector2 containerCenter;
    Texture2D containerTexture;

    Color bgColor = Color({55, 55, 55, 200});

    std::vector<std::string> rootNoteVec = {"A", "Bb/A#", "B", "C", "Db/C#", "D", "Eb/D#", "E", "F", "Gb/F#", "G", "Ab/G#",
                                             "A", "Bb/A#", "B", "C", "Db/C#", "D", "Eb/D#", "E", "F", "Gb/F#", "G", "Ab/G#"};

    int dropdownBox001Active;
    bool dropDown001EditMode;
    std::string currentRoot;

    // const int buttonColor = 0xAA5588FF;  // TODO: Learn more about this color format. [Red (AA), Green (55), Blue (88) and Alpha (FF)]
    // Make pure black button color
    const int buttonTextColor = 0x000000FF;
    const int buttonColor = 0xE2E2E2FF;

public:

    ChordMenu(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~ChordMenu() = default;

    void draw();

//    std::vector<std::string> setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>> &instrumentsVec);
    void setChord(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>> &instrumentsVec);
    void setKey(std::string key);
    std::string getKey();
    // std::vector<std::unique_ptr<Instrument>> getScale();



};


#endif //GUITAR_APP_CHORDMENU_H
