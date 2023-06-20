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

    Color bgColor = Color({55, 55, 55, 200});

public:

    ScalesMenu(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~ScalesMenu() = default;

    void draw();

//    std::vector<std::string> setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>> &instrumentsVec);
    void setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>> &instrumentsVec);


};


#endif //GUITAR_APP_SCALESMENU_H
