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
    int active;
    bool editMode;

    Rectangle container;
    Vector2 containerCenter;
    Texture2D containerTexture;

    Rectangle buttonOneRec;
    Vector2 buttonOneCenter;

    Color blackBackground;



public:

    // Menu constructor
    Menu(int screenWidth, int screenHeight, float posX, float posY, float width, float height);

    void setBackground(int width, int height);
    void drawTopMenu(int width, int height);



};

#endif //GUITAR_APP_MENU_H
