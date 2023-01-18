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
    Image fretImage;
    Image stringImage;
    Texture2D containerTexture;
    Texture2D neckTexture;
    Texture2D fretTexture;
    Texture2D stringTexture;
    Rectangle container;
    Rectangle neckRectangle;
    Rectangle fretRectangle;
    Rectangle stringRectangle;
    Vector2 containerCenter;
    Vector2 neckCenter;
    Vector2 fretCenter;
    Vector2 stringCenter;

public:

    Neck(int screenWidth, int screenHeight, float width, float height);

    void initGuitarNeck();
    int drawGuitarNeck(float windowScale);
    void destroy();

};


#endif //GUITAR_APP_NECK_H
