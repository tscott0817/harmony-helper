#ifndef GUITAR_APP_MENU_H
#define GUITAR_APP_MENU_H
#include "raylib.h"
#include <iostream>
#include <vector>
#include <memory>


class Menu {
private:
    Image containerImage;
    Texture2D containerTexture;
    Rectangle container;
    Vector2 containerCenter;

    Image menuImage;
    Texture2D menuTexture;
    Rectangle menuRectangle;
    Vector2 menuCenter;

    std::vector<std::vector<Vector2>> menuLocations;
    bool menuLocAdded;
    std::vector<std::vector<Color>> menuColorVec;

public:
    Menu(int screenWidth, int screenHeight, float posX, float posY, float width, float height);

    void initMenu();
    int drawMenu(float windowScale);
    void hover(Vector2 mousePos);
    void destroy();


};


#endif //GUITAR_APP_MENU_H
