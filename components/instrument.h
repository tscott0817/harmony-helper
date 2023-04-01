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

    /** Every Object Gets a Container **/
    Image containerImage;
    Texture2D containerTexture;
    Rectangle container;
    Vector2 containerCenter;
    Vector2 containerLoc;
    bool containerLocAdded;

    /** Connection Point **/
    Image connectImage;
    Texture2D connectTexture;
    Rectangle connectRectangle;
    Vector2 connectCenter;
    Vector2 connectLoc;
    bool connectLocAdded;

    /** Colors **/
    Color hoverColor;
    Color rootColor;
    Color secondColor;
    Color thirdColor;
    Color fourthColor;
    Color fifthColor;

    /** States Each Object Has **/
    bool active;  // TODO: Make this private with a getter/setter;
    bool canDraw;
    bool canDrawConnection;

public:

    virtual void hover(Vector2 mousePos);
    virtual void draw(float windowScale);
    virtual void clickAndDrag(Vector2 mousePos);

    // Getters
    virtual bool getStateActive();
    virtual bool getCanDraw();
    virtual bool getCanDrawConnection();
    virtual Rectangle getContainer();
    virtual Rectangle getConnectionRec();

    // Setters
    virtual void setStateActive(bool state);
    virtual void setCanDraw(bool state);
    virtual void setCanDrawConnection(bool state);
//    virtual void setConnectionRec(Rectangle pos);

};


#endif //GUITAR_APP_INSTRUMENT_H
