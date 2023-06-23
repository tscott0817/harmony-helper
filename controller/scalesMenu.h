#ifndef GUITAR_APP_SCALESMENU_H
#define GUITAR_APP_SCALESMENU_H
#include "raylib.h"
#define RAYGUI_STATIC
#include "../raygui.h"
#undef RAYGUI_STATIC
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../components/instrument.h"
class ScalesMenu {

private:

    Rectangle container;
    Vector2 containerCenter;
    Texture2D containerTexture;

    Color bgColor = Color({25, 25, 25, 125});

    // To choose scale.
    std::vector<std::string> scaleTypeVec = {"Major", "Minor", "Pentatonic", "Blues", "Harmonic Minor", "Melodic Minor", "Dorian", "Mixolydian", "Lydian", "Phrygian", "Locrian"};
    // TODO: Just repeating for now, but want to just loop back to beginning
    std::vector<std::string> scaleNoteVec = {"A", "Bb/A#", "B", "C", "Db/C#", "D", "Eb/D#", "E", "F", "Gb/F#", "G", "Ab/G#",
                                             "A", "Bb/A#", "B", "C", "Db/C#", "D", "Eb/D#", "E", "F", "Gb/F#", "G", "Ab/G#"};

    int dropdownBox001Active;
    bool dropDown001EditMode;
    std::string currentKey;

public:

    ScalesMenu(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~ScalesMenu() = default;

    void draw();

//    std::vector<std::string> setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>> &instrumentsVec);
    void setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>> &instrumentsVec);
    void setKey(std::string key);
    std::string getKey();
    // std::vector<std::unique_ptr<Instrument>> getScale();



};


#endif //GUITAR_APP_SCALESMENU_H
