#ifndef GUITAR_APP_NECK_H
#define GUITAR_APP_NECK_H

#include "raylib.h"
#include "uiObjects.h"
#include <iostream>
#include <vector>
#include <memory>

class Neck : public UIObjects {
private:
    int screenWidth;
    int screenHeight;

    // TODO: Need to collect these all in structs
    Image containerImage;
    Texture2D containerTexture;
    Rectangle container;
    Vector2 containerCenter;
    Vector2 containerLoc;
    bool containerLocAdded;

    Image neckImage;
    Texture2D neckTexture;
    Rectangle neckRectangle;
    Vector2 neckCenter;

    Image fretImage;
    Texture2D fretTexture;
    Rectangle fretRectangle;
    Vector2 fretCenter;

    Image stringImage;
    Texture2D stringTexture;
    Rectangle stringRectangle;
    Vector2 stringCenter;

    Image noteImage;
    Texture2D noteTexture;
    Rectangle noteRectangle;
    Vector2 noteCenter;

    bool notesLocAdded;
    std::vector<std::vector<Vector2>> noteLocations;
    std::vector<std::vector<Color>> noteColorVec;

    // Neck Colors
    Color hoverColor;
    Color rootColor;
    Color secondColor;
    Color thirdColor;
    Color fourthColor;
    Color fifthColor;

    // Text and Font
    const char *testText;
    const char *noteName;
    Font testFont;
    float fontSize;
    Vector2 fontPosition;
    Vector2 textSize;
    int currentFontFilter;
    Vector2 tempNoteLoc;

    // Connection Point
    Image connectImage;
    Texture2D connectTexture;
    Rectangle connectRectangle;
    Vector2 connectCenter;
    Vector2 connectLoc;
    bool connectLocAdded;
    bool canDrawConnection;

    Vector2 bezierStart;
    Vector2 bezierEnd;
    bool stateActive;  // TODO: Make this private with a getter/setter;
    bool canDraw;

    const char *lowE[12] = {"E", "F", "F#", "G", "G#", "A", "A#", "B", "C", "C#", "D", "D#"};


public:

    // Constructors
    Neck(int screenWidth, int screenHeight, float posX, float posY, float width, float height);

    // Guitar Methods
    void initGuitarNeck();
    int drawGuitarNeck(float windowScale);
    void hover(Vector2 mousePos);
    void clickAndDrag(Vector2 mousePos);
    void destroy();

    // Getters
    bool getStateActive();
    bool getCanDraw();
    bool getCanDrawConnection();
    Rectangle getContainer();
//    Vector2 getConnectionPos();
    Rectangle getConnectionRec();

    // Setters
    void setStateActive(bool state);
    void setCanDraw(bool state);
    void setCanDrawConnection(bool state);
    void setConnectionPos(Rectangle pos);

};


#endif //GUITAR_APP_NECK_H
