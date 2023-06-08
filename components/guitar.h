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

    Vector2 bezierStart;
    Vector2 bezierEnd;

    const char *lowE[12] = {"F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E"};
    const char *a[12] = {"Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A"};
    const char *d[12] = {"Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D"};
    const char *g[12] = {"Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G"};
    const char *b[12] = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
    const char *highE[12] = {"F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E"};
    std::vector<const char **> noteTextVec;
//    std::string lowE[12] = {"F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E"};
//    std::string a[12] = {"Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A"};
//    std::string d[12] = {"Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D"};
//    std::string g[12] = {"Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G"};
//    std::string b[12] = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
//    std::string highE[12] = {"F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E"};
//    std::vector<std::string> noteTextVec;

    // Audio
    Sound testSound;

    std::vector<std::string> activeNotesVec;



public:

    // Constructors
    Guitar(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    virtual ~Guitar() = default;

    // Guitar Methods
    void draw(float windowScale) override;
    void hover(Vector2 mousePos) override;
    void clickColorHold(Vector2 mousePos) override;
    void soundTests() override;
    bool connectionHover(Vector2 mousePos);
    void clickAndDrag(Vector2 mousePos) override;
    void notesActivate() override;

    // Getters
    bool getStateActive() override;
    bool getCanDraw() override;
    bool getCanDrawConnection() override;
    Rectangle getContainer() override;
    Rectangle getConnectionRec() override;
    std::vector<std::string> getSelectedNotes() override;
//    std::vector<std::vector<int>> getNoteClickedBoolVec() override;
    bool isHovering(Vector2 mousePos) override;

    // Setters
    void setStateActive(bool state) override;
    void setCanDraw(bool state) override;
    void setCanDrawConnection(bool state) override;
//    void setNoteClickBoolVec(std::vector<std::vector<int>> newVec) override;
    //void setConnectionRec(Rectangle pos) override;
//    void addSelectNote(const std::string &notes) override;
    void setActiveNotes(std::vector<std::string> newVec) override;


    void destroy();
};


#endif //GUITAR_APP_GUITAR_H
