#ifndef GUITAR_APP_UIOBJECTS_H
#define GUITAR_APP_UIOBJECTS_H
#include "raylib.h"
#include "uiObjects.h"
#include <iostream>
#include <vector>
#include <memory>

class UIObjects {
private:

protected:
    int screenWidth;
    int screenHeight;

    Image containerImage;
    Texture2D containerTexture;
    Rectangle container;
    Vector2 containerCenter;
    Vector2 containerLoc;
    bool containerLocAdded;

    /** Colors **/
    Color hoverColor;
    Color rootColor;
    Color secondColor;
    Color thirdColor;
    Color fourthColor;
    Color fifthColor;

    bool canDraw;
    bool canDrawConnection;

public:

    virtual void hover(Vector2 mousePos);

    // Getters
    bool getStateActive();
    bool getCanDraw();
    bool getCanDrawConnection();
    Rectangle getContainer();
    Rectangle getConnectionRec();

    // Setters
    void setStateActive(bool state);
    void setCanDraw(bool state);
    void setCanDrawConnection(bool state);
    void setConnectionRec(Rectangle pos);

};


#endif //GUITAR_APP_UIOBJECTS_H
