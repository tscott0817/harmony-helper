#ifndef GUITAR_APP_NECK_H
#define GUITAR_APP_NECK_H

#include "raylib.h"
#include <iostream>


class Neck {

private:
    int screenWidth;
    int screenHeight;
    Image neckImage;
    Texture2D neckTexture;
    Rectangle boxRec;
    Vector2 boxCenter;

public:

    Neck(int screenWidth, int screenHeight);

    void initGuitarNeck();
    int drawGuitarNeck();
    void destroy();

};


#endif //GUITAR_APP_NECK_H
