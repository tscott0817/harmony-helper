#ifndef GUITAR_APP_GUITAR_H
#define GUITAR_APP_GUITAR_H

#include "raylib.h"
#include "instrument.h"
#include <iostream>
#include <vector>
#include <memory>

class Guitar : public Instrument {
private:

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

    // Text and Font
    const char *testText;
    const char *noteName;
    Font testFont;
    float fontSize;
    Vector2 fontPosition;
    Vector2 textSize;
    int currentFontFilter;
    Vector2 tempNoteLoc;

    Vector2 bezierStart;
    Vector2 bezierEnd;

    const char *lowE[12] = {"E", "F", "F#", "G", "G#", "A", "A#", "B", "C", "C#", "D", "D#"};

public:

    // Constructors
    Guitar(int screenWidth, int screenHeight, float posX, float posY, float width, float height);

    // Guitar Methods
    void draw(float windowScale) override;
    void hover(Vector2 mousePos) override;
    bool connectionHover(Vector2 mousePos);
    void clickAndDrag(Vector2 mousePos) override;

    // Getters
    bool getStateActive() override;
    bool getCanDraw() override;
    bool getCanDrawConnection() override;
    Rectangle getContainer() override;
    Rectangle getConnectionRec() override;

    // Setters
    void setStateActive(bool state) override;
    void setCanDraw(bool state) override;
    void setCanDrawConnection(bool state) override;
    //void setConnectionRec(Rectangle pos) override;

    void destroy();
};


#endif //GUITAR_APP_GUITAR_H
