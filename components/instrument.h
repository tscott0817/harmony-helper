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

    // TODO: Not sure if i will end up doing the bezier, might just stack instr in rows
    /** Connection Point **/
    Image connectImage{};
    Texture2D connectTexture{};
    Rectangle connectRectangle{};
    Vector2 connectCenter{};
    Vector2 connectLoc{};
    bool connectLocAdded{};

    /** Colors **/
    Color rootColor{};
    Color hoverColor{};
    Color clickColor{};
    Color secondColor{};
    Color thirdColor{};
    Color fourthColor{};
    Color fifthColor{};

    /** States Each Object Has **/
    bool active{};  // TODO: Make this private with a getter/setter;
    bool canDraw{};

    /** Track All Shared Notes **/
    static std::vector<std::string> sharedNotesVec;


public:

    Instrument();

    // Functionality
    virtual void hover(Vector2 mousePos);
    virtual bool isHovering(Vector2 mousePos) = 0;
    virtual void selectNote(Vector2 mousePos) = 0;
    virtual void draw(float windowScale) = 0;
    virtual void clickAndDrag(Vector2 mousePos) = 0;

    // Getters
    virtual bool getCanDraw();

    // Setters
    virtual void setCanDraw(bool state);
    virtual void notesActivate();

    void addNoteShared(const std::string& item);
    void printNotesShared();
    void removeNoteShared(const std::string& note);

    virtual void destroy();

};


#endif //GUITAR_APP_INSTRUMENT_H
