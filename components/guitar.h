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
    std::vector<std::vector<int>> noteClickedBoolVec;  // TODO: Read more about why vector<bool> is bad practice.

    // Text and Font
    const char *testText;
    const char *noteName;
    Font testFont;
    float fontSize;
    Vector2 fontPosition;
    Vector2 textSize;
    int currentFontFilter;
    Vector2 tempNoteLoc;

    const char *lowE[12] = {"F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E"};
    const char *a[12] = {"Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A"};
    const char *d[12] = {"Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D"};
    const char *g[12] = {"Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G"};
    const char *b[12] = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
    const char *highE[12] = {"F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E"};
    std::vector<const char **> noteTextVec;

    // Audio
    Sound testSound;

public:

    // Constructors
    Guitar(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    virtual ~Guitar() = default;

    // Guitar Methods
    void draw(float windowScale) override;
    void hover(Vector2 mousePos) override;
    void selectNote(Vector2 mousePos) override;
    void clickAndDrag(Vector2 mousePos) override;
    void notesActivate() override;
    bool isHovering(Vector2 mousePos) override;

    // Getters
    bool getCanDraw() override;

    // Setters
    void setCanDraw(bool state) override;

    void destroy() override;
};


#endif //GUITAR_APP_GUITAR_H
