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

    int active;
    bool editMode;
    std::vector<int> activeVec;

    Rectangle container;
    Vector2 containerCenter;

    Rectangle buttonOneRec;
    Vector2 buttonOneCenter;

    Rectangle buttonTwoRec;
    Vector2 buttonTwoCenter;

    int currentButton;
    std::vector<Vector2> buttonLocations;
    bool buttonLocAdded;
    std::vector<Color> buttonColorVec;

    Color bgColor = Color({55, 55, 55, 200});
    Color baseColor;
    Color activeColor;

    const char *testText;
    const char *noteName;
    Font testFont;
    float fontSize;
    Vector2 fontPosition;
    Vector2 textSize;
    const char *buttonText[2] = {"Guitar", "Piano"};

    bool scaleChanged;

public:

    ChordMenu(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~ChordMenu() = default;

    void draw();
    void click(int currButton);
    void chooseButton(Vector2 mousePos);
    void resetMenu(const std::vector<std::unique_ptr<Instrument>>& instrumentsVec);

//    std::vector<std::string> setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>> &instrumentsVec);
    void setChord(const std::vector<std::unique_ptr<Instrument>> &instrumentsVec);

};


#endif //GUITAR_APP_CHORDMENU_H
