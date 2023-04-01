#ifndef GUITAR_APP_PIANO_H
#define GUITAR_APP_PIANO_H
#include "raylib.h"
#include "instrument.h"
#include <iostream>
#include <vector>
#include <memory>

class Piano : public Instrument {

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
    ~Piano() = default;

    void draw(float windowScale) override;
    void hover(Vector2 mousePos) override;
    bool connectionHover(Vector2 mousePos);
    void clickAndDrag(Vector2 mousePos) override;

    // Getters
    bool getCanDraw() override;
    Rectangle getContainer() override;
    Rectangle getConnectionRec() override;
    bool getCanDrawConnection() override;
    bool getStateActive() override;


    // Setters
    void setCanDraw(bool canDraw) override;
    //void setConnectionRec(Rectangle connectRectangle) override;
    void setCanDrawConnection(bool state) override;
    void setStateActive(bool state) override;

    void destroy();

};


#endif //GUITAR_APP_PIANO_H
