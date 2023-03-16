#ifndef GUITAR_APP_MENU_H
#define GUITAR_APP_MENU_H
#include "raylib.h"
#define RAYGUI_STATIC
#include "../raygui.h"
#undef RAYGUI_STATIC            // Avoid including raygui implementation again


#include "../components/modal_chart.h"
#include <iostream>
#include <vector>
#include <memory>

// #define RAYGUI_STATIC


class Menu {
private:
    int tempVal;
    // GUI init
    //----------------------------------------------------------------------------------
    // bool active; // TODO: Will need one of these for each button
    int active;
    bool editMode;
    std::vector<int> activeVec;

    Rectangle container;
    Vector2 containerCenter;
    Texture2D containerTexture;

    Rectangle buttonOneRec;
    Vector2 buttonOneCenter;

    Rectangle buttonTwoRec;
    Vector2 buttonTwoCenter;

    Color blackBackground;
    int listViewExScrollIndex = 0;
    int listViewExActive = 2;
    int listViewExFocus = -1;
    const char *listViewExList[8] = { "This", "is", "a", "list view", "with", "disable", "elements", "amazing!" };

    std::vector<Vector2> buttonLocations;
    bool buttonLocAdded;
    std::vector<Color> buttonColorVec;
    // Neck Colors
    Color hoverColor;
    Color baseColor;
    Color currentColor;
    Color activeColor;
    Color secondColor;
    Color thirdColor;
    Color fourthColor;
    Color fifthColor;

    int currentButton;



public:

    bool canDraw;  // TODO: Make this private with a getter/setter
    bool isHovering;

    // Menu constructor
    Menu(int screenWidth, int screenHeight, float posX, float posY, float width, float height);

    void setBackground(int width, int height);
    void drawTopMenu(int width, int height);
    //bool isHovering(Vector2 mousePos);  // TODO: Combine the two hovering into one function, have a bool switch for if currently hovering
    void hover(Vector2 mousePos);
    void click(int currentButton);

    // Setters
    void setActiveButton(int activeButton);

    // Getters
    std::vector<int> getActiveButtons();

};

#endif //GUITAR_APP_MENU_H
