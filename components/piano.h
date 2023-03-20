#ifndef GUITAR_APP_PIANO_H
#define GUITAR_APP_PIANO_H
#include "raylib.h"
#include "uiObjects.h"
#include <iostream>
#include <vector>
#include <memory>

class Piano : public UIObjects {

private:

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

    bool notesLocAdded;
    std::vector<Vector2> keyWhiteLocations;
    std::vector<Vector2> keyBlackLocations;
    std::vector<Color> keyWhiteColorVec;
    std::vector<Color> keyBlackColorVec;
    bool whiteKeyHover;
    bool blackKeyHover;
    Color whiteKeyColor;
    Color blackKeyColor;

public:
    Piano(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~Piano();

    void drawPiano(float windowScale);
    void hover(Vector2 mousePos) override;
    bool connectionHover(Vector2 mousePos);
    void clickAndDrag(Vector2 mousePos);

    // Getters
    bool getCanDraw();
    Rectangle getContainer();
    Rectangle getConnectionRec();
    bool getCanDrawConnection();


    // Setters
    void setCanDraw(bool canDraw);
    void setConnectionRectangle(Rectangle connectRectangle);
    void setCanDrawConnection(bool state);

    void destroy();

};


#endif //GUITAR_APP_PIANO_H
