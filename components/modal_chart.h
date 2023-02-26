#ifndef GUITAR_APP_MODAL_CHART_H
#define GUITAR_APP_MODAL_CHART_H
#include "raylib.h"
#include <iostream>
#include <vector>
#include <memory>


class ModalChart {
private:

    // TODO: Make these structs?
    Image containerImage;
    Texture2D containerTexture;
    Rectangle container;
    Vector2 containerCenter;

    Image chartImage;
    Texture2D chartTexture;
    Rectangle chartRectangle;
    Vector2 chartCenter;

    std::vector<std::vector<Vector2>> chartLocations;
    bool chartLocAdded;
    std::vector<std::vector<Color>> chartColorVec;

public:

    // TOOD: Maybe make setters / getters
    bool canDraw;
    ModalChart(int screenWidth, int screenHeight, float posX, float posY, float width, float height);

    void initModalChart();
    int drawModalChart(float windowScale);
    void hover(Vector2 mousePos);
    void destroy();

};


#endif //GUITAR_APP_MODAL_CHART_H
