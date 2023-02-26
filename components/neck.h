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

    // TODO: Need to collect these all in structs
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
    //Circle noteCircle;
    Vector2 containerCenter;
    Vector2 neckCenter;
    Vector2 fretCenter;
    Vector2 stringCenter;
    Vector2 noteCenter;
    std::vector<std::vector<Vector2>> noteLocations;
    bool notesLocAdded;
    std::vector<std::vector<Color>> noteColorVec;

public:

    // Constructors
    Neck(int screenWidth, int screenHeight, float posX, float posY, float width, float height);

    // Guitar Methods
    void initGuitarNeck();
    int drawGuitarNeck(float windowScale);
    void hover(Vector2 mousePos);
    void destroy();

};


#endif //GUITAR_APP_NECK_H
