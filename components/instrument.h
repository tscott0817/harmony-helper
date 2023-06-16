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
    int screenWidth;
    int screenHeight;

    /** Every Instrument is Held in a Container **/
    Image containerImage{};
    Texture2D containerTexture{};
    Rectangle container{};
    Vector2 containerCenter{};
    Vector2 containerLoc{};
    bool containerLocAdded;

    // TODO: Not sure if i will end up doing the bezier, might just stack instr in rows
    /** Connection Point **/
    Image connectImage{};
    Texture2D connectTexture{};
    Rectangle connectRectangle{};
    Vector2 connectCenter{};
    Vector2 connectLoc{};
    bool connectLocAdded;

    /** Colors **/
    Color rootColor{};
    Color hoverColor{};
    Color clickColor{};
    Color secondColor{};
    Color thirdColor{};
    Color fourthColor{};
    Color fifthColor{};

    /** States Each Object Has **/
    bool active;  // TODO: Make this private with a getter/setter;
    bool canDraw;
    bool canDrawConnection;

    /** Track Currently Selected  **/
    // TODO: Maybe just hold string that can be used to search. Like 'if the current note is selected'
    std::vector<std::string> selectedNotesVec;  // Hold index of each note that is selected,

    /** Track All Shared Notes **/
    static std::vector<std::string> sharedNotesVec;


public:

    // Constructors
    Instrument();
    virtual void hover(Vector2 mousePos);
    virtual bool isHovering(Vector2 mousePos);
    virtual void clickColorHold(Vector2 mousePos);
    virtual void soundTests();
    virtual void draw(float windowScale);
    virtual void clickAndDrag(Vector2 mousePos);
    //virtual void playSound(Vector2 mousePos);

    // Getters
    virtual bool getStateActive();
    virtual bool getCanDraw();
    virtual bool getCanDrawConnection();
    virtual Rectangle getContainer();
    virtual Rectangle getConnectionRec();
    virtual std::vector<std::string> getSelectedNotes();
    virtual std::vector<std::string> getActiveNotes();
//    virtual std::vector<std::vector<int>> getNoteClickedBoolVec();

    // Setters
    virtual void setStateActive(bool state);
    virtual void setCanDraw(bool state);
    virtual void setCanDrawConnection(bool state);
    virtual void setActiveNotes(std::vector<std::string> newVec);
    virtual void appendActiveNotes(std::string appendedNote);
    virtual void notesActivate();
//    virtual void setNoteClickBoolVec(std::vector<std::vector<int>> newVec);
//    virtual void setConnectionRec(Rectangle pos);
//    virtual void addSelectNote(const std::string &notes);

    void addNoteShared(const std::string& item);
    void printNotesShared();
    void removeNoteShared(const std::string& note);
    static std::vector<std::string> getNotesShared();

    virtual void destroy();

};


#endif //GUITAR_APP_INSTRUMENT_H
