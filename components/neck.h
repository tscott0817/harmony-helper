#ifndef GUITAR_APP_NECK_H
#define GUITAR_APP_NECK_H

#include "raylib.h"
#include <iostream>


class Neck {

private:
    int screenWidth;
    int screenHeight;
    Image containerImage;
    Image neckImage;
    Image stringImage;
    Texture2D containerTexture;
    Texture2D neckTexture;
    Texture2D stringTexture;
    Rectangle container;
    Rectangle neckRectangle;
    Rectangle stringRectangle;
    Vector2 containerCenter;
    Vector2 neckCenter;
    Vector2 stringCenter;

public:

    Neck(int screenWidth, int screenHeight, float width, float height);

    void initGuitarNeck();
    int drawGuitarNeck();
    void destroy();

};


#endif //GUITAR_APP_NECK_H
