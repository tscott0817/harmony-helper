#ifndef GUITAR_APP_NECK_H
#define GUITAR_APP_NECK_H

#include "raylib.h"
#include <iostream>
#include <vector>
#include <memory>


class Neck {

private:
    int screenWidth;
    int screenHeight;
    Image containerImage;
    Image neckImage;
    Image fretImage;
    Image stringImage;
    Image noteImage;
    Texture2D containerTexture;
    Texture2D neckTexture;
    Texture2D fretTexture;
    Texture2D stringTexture;
    Texture2D noteTexture;
    Rectangle container;
    Rectangle neckRectangle;
    Rectangle fretRectangle;
    Rectangle stringRectangle;
    Rectangle noteRectangle;
    Vector2 containerCenter;
    Vector2 neckCenter;
    Vector2 fretCenter;
    Vector2 stringCenter;
    Vector2 noteCenter;
    std::vector<Vector2> noteLocations;
    bool notesLocAdded;
    std::vector<Color>* noteColorVec = new std::vector<Color>;
    //Color noteColor;
    Color* noteColor = new Color;
    //std::unique_ptr<Color> noteColor;

public:

    Neck(int screenWidth, int screenHeight, float width, float height);

    void initGuitarNeck();
    int drawGuitarNeck(float windowScale);
    void hover(Vector2 mousePos);
    void destroy();

};


#endif //GUITAR_APP_NECK_H
