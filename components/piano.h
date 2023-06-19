#ifndef GUITAR_APP_PIANO_H
#define GUITAR_APP_PIANO_H
#include "raylib.h"
#include "instrument.h"
#include <iostream>
#include <vector>
#include <memory>

class Piano : public Instrument {

private:

    Rectangle containerLoc;
    Rectangle bgLoc;
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

    Sound F;
    Sound Fs;
    Sound G;
    Sound Gs;
    Sound A;
    Sound As;
    Sound B;
    Sound C;
    Sound Cs;
    Sound D;
    Sound Ds;
    Sound E;
    Sound soundNoteTest;
    std::vector<Sound> notesVec;

    std::vector<std::vector<Color>> noteColorVec;
    std::vector<int> noteClickedBoolVecWhite;
    std::vector<int> noteClickedBoolVecBlack;
    std::vector<std::string> activeNotesVec;

    // White keys
    const char *keysWhite[7] = {"C",  "D", "E", "F", "G", "A", "B"};
    const char *keysBlack[5] = {"Db",  "Eb", "Gb", "Ab", "Bb"};
    std::vector<const char **> noteTextVec;

    Color containerColor;

public:
    Piano(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~Piano() = default;

    /** Inherited Methods **/
    void draw(float windowScale) override;
    void selectNote(Vector2 mousePos) override;
    void clickAndDrag(Vector2 mousePos) override;
    void notesActivate() override;
    void destroy() override;

    // Setters
    void setCanDraw(bool canDraw) override;

    // Getters
    bool getCanDraw() override;

    /** Derived Class Specific Methods **/
    bool hoverBlackNotes(Vector2 mousePos);  // If mouse hovers over black notes, don't allow white note interactions

};


#endif //GUITAR_APP_PIANO_H
