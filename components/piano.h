#ifndef GUITAR_APP_PIANO_H
#define GUITAR_APP_PIANO_H
#include "raylib.h"
#include <iostream>
#include <vector>
#include <memory>

class Piano {

private:
    int screenWidth;
    int screenHeight;

    Image containerImage;
    Texture2D containerTexture;
    Rectangle container;
    Vector2 containerCenter;
    Vector2 containerLoc;
    bool containerLocAdded;

    Image keyWhiteImage;
    Texture2D keyWhiteTexture;
    Rectangle keyWhiteRectangle;
    Vector2 keyWhiteCenter;
    Vector2 keyWhiteLoc;
    bool keyWhiteLocAdded;

    Image keyBlackImage;
    Texture2D keyBlackTexture;
    Rectangle keyBlackRectangle;
    Vector2 keyBlackCenter;
    Vector2 keyBlackLoc;
    bool keyBlackLocAdded;

    Image connectImage;
    Texture2D connectTexture;
    Rectangle connectRectangle;
    Vector2 connectCenter;
    Vector2 connectLoc;
    bool connectLocAdded;
    bool canDrawConnection;

    Color hoverColor;
    Color rootColor;
    Color secondColor;
    Color thirdColor;
    Color fourthColor;
    Color fifthColor;

    bool notesLocAdded;
    std::vector<Vector2> keyWhiteLocations;
    std::vector<Vector2> keyBlackLocations;
    std::vector<Color> keyWhiteColorVec;
    std::vector<Color> keyBlackColorVec;
    bool whiteKeyHover;
    bool blackKeyHover;
    Color whiteKeyColor;
    Color blackKeyColor;



    bool canDraw;

public:
    Piano(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~Piano();

    void drawPiano(float windowScale);
    void hover(Vector2 mousePos);
    void clickAndDrag(Vector2 mousePos);

    // Getters
    bool getCanDraw();
    Rectangle getContainer();
    Rectangle getConnectionRectangle();


    // Setters
    void setCanDraw(bool canDraw);
    void setConnectionRectangle(Rectangle connectRectangle);

    void destroy();

};


#endif //GUITAR_APP_PIANO_H
