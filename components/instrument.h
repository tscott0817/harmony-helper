#ifndef GUITAR_APP_INSTRUMENT_H
#define GUITAR_APP_INSTRUMENT_H
#include "raylib.h"
#include "instrument.h"
#include <iostream>
#include <vector>
#include <memory>

class Instrument {
private:

protected:
    int screenWidth{};
    int screenHeight{};

    /** Every Instrument is Held in a Container **/
    Image containerImage{};
    Texture2D containerTexture{};
    Rectangle container{};
    Vector2 containerCenter{};
    Vector2 containerLoc{};
    bool containerLocAdded{};

    /** Colors **/
    // Colors for individual notes
    Color rootColor = Color{238, 238, 238, 200};
    Color cNoteColor = Color{168, 50, 50, 255};
    Color dbNoteColor = Color{184, 171, 61, 255};
    Color dNoteColor = Color{38, 128, 80, 255};
    Color ebNoteColor = Color{168, 111, 50, 255};
    Color eNoteColor = Color{168, 50, 152, 255};
    Color fNoteColor = Color{48, 102, 150, 255};
    Color gbNoteColor = Color{60, 194, 183, 255};
    Color gNoteColor = Color{126, 74, 247, 255};
    Color abNoteColor = Color{49, 62, 158, 255};
    Color aNoteColor = Color{130, 176, 49, 255};
    Color bbNoteColor = Color{127, 50, 168, 255};
    Color bNoteColor = Color{179, 64, 117, 255};
    std::vector<Color> noteColorVecBase = {cNoteColor, dbNoteColor, dNoteColor, ebNoteColor, eNoteColor, fNoteColor, gbNoteColor, gNoteColor, abNoteColor, aNoteColor, bbNoteColor, bNoteColor};

    // TODO: Do not want these in the base class
    std::vector<Color> whiteKeyColorVec = {cNoteColor, dNoteColor, eNoteColor, fNoteColor, gNoteColor, aNoteColor, bNoteColor};
    std::vector<Color> blackKeyColorVec = {dbNoteColor, ebNoteColor, gbNoteColor, abNoteColor, bbNoteColor};


    /** States Each Object Has **/
    bool active{};  // TODO: Make this private with a getter/setter;
    bool canDraw{};

    /** Track All Shared Notes **/
    static std::vector<std::string> sharedNotesVec;
    // std::vector<Sound> notesSoundVec;


public:
public:
    Instrument();
    ~Instrument();

    /** Base Class Specific Methods **/
    static void addNoteShared(const std::string& item);
    static void removeNoteShared(const std::string& note);
    static void clearNotesShared();
    static void setNotesShared(std::vector<std::string> notesVec);
    static std::vector<std::string> getNotesShared();
    static void printNotesShared();

    /** Methods to be Overridden **/
    virtual void selectNote(Vector2 mousePos) = 0;
    virtual void draw(float windowScale) = 0;
    virtual void clickAndDrag(Vector2 mousePos) = 0;
    virtual void notesActivate() = 0;
    virtual void destroy() = 0;

    // TODO: Want these to be pure but can't implement guitar audio yet
    virtual void playSound(){};
    virtual void initAudio(){};
    virtual void unloadAudio(){};

    // Setters
    virtual void setCanDraw(bool state) = 0;

    // Getters
    virtual bool getCanDraw() = 0;

};


#endif //GUITAR_APP_INSTRUMENT_H
