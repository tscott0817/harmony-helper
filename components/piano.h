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
    Color blackKeyClickColor;

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
    std::vector<Sound> notesVec;

    std::vector<std::vector<Color>> noteColorVec;
    std::vector<int> noteClickedBoolVec;
    std::vector<std::string> activeNotesVec;

    // White keys
    const char *keysWhite[7] = {"C",  "D", "E", "F", "G", "A", "B"};
    const char *keysBlack[5] = {"Db",  "Eb", "Gb", "Ab", "Bb"};
    std::vector<const char **> noteTextVec;

    bool cExists = false;



public:
    Piano(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~Piano() = default;

    void draw(float windowScale) override;
    void hover(Vector2 mousePos) override;
    bool connectionHover(Vector2 mousePos);
    void clickColorHold(Vector2 mousePos) override;
    void clickAndDrag(Vector2 mousePos) override;
    //void playSound(Vector2 mousePos) override;
    bool isHovering(Vector2 mousePos) override;

    // Getters
    bool getCanDraw() override;
    Rectangle getContainer() override;
    Rectangle getConnectionRec() override;
    bool getCanDrawConnection() override;
    bool getStateActive() override;
    std::vector<std::string> getSelectedNotes() override;
    std::vector<std::string> getActiveNotes() override;
    void appendActiveNotes(std::string appendedNote) override;
//    std::vector<std::vector<int>> getNoteClickedBoolVec() override;


    // Setters
    void setCanDraw(bool canDraw) override;
    //void setConnectionRec(Rectangle connectRectangle) override;
    void setCanDrawConnection(bool state) override;
    void setStateActive(bool state) override;
//    void setNoteClickBoolVec(std::vector<std::vector<int>> newVec) override;
//    void addSelectNote(const std::string &notes) override;

    void setActiveNotes(std::vector<std::string> newVec) override;
    void notesActivate() override;


    void destroy() override;

};


#endif //GUITAR_APP_PIANO_H
