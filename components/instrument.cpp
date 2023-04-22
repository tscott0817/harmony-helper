#include "instrument.h"

void Instrument::hover(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, container)) {
        std::cout << "Hovering over Instrument" << std::endl;
    }
}

void Instrument::clickColorHold(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, container)) {
        std::cout << "Clicking Instrument" << std::endl;
    }
}

void Instrument::draw(float windowScale) {
    std::cout << "Drawing Instrument" << std::endl;
}

void Instrument::clickAndDrag(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, container)) {
        std::cout << "Clicking and Dragging Instrument" << std::endl;
    }
}

void Instrument::playSound(Vector2 mousePos) {
    std::cout << "Playing Instrument Sound" << std::endl;
}

/** Getters **/
bool Instrument::getStateActive() {return false;}
bool Instrument::getCanDraw() {return false;}
bool Instrument::getCanDrawConnection() {return false;}
Rectangle Instrument::getContainer() {return Rectangle();}
Rectangle Instrument::getConnectionRec() {return Rectangle();}

/** Setters **/
void Instrument::setStateActive(bool state) {this->active = state;}
void Instrument::setCanDraw(bool state) {this->canDraw = state;}
void Instrument::setCanDrawConnection(bool state) {this->canDrawConnection = state;}

void Instrument::destroy() {
    std::cout << "Destroying Instrument" << std::endl;
}





