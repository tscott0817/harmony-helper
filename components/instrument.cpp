#include "instrument.h"
#include <utility>
#include <algorithm>

// Make constructor
Instrument::Instrument() {
    std::cout << "Creating Instrument" << std::endl;
}

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

void Instrument::soundTests() {
    //std::cout << "Playing Instrument Sound" << std::endl;
    int random_thing = 0;
}

//void Instrument::playSound(Vector2 mousePos) {
//    std::cout << "Playing Instrument Sound" << std::endl;
//}

/** Getters **/
bool Instrument::getStateActive() {return false;}
bool Instrument::getCanDraw() {return false;}
bool Instrument::getCanDrawConnection() {return false;}
Rectangle Instrument::getContainer() {return Rectangle();}
Rectangle Instrument::getConnectionRec() {return Rectangle();}
std::vector<std::string> Instrument::getSelectedNotes() {return selectedNotesVec;}

/** Setters **/
void Instrument::setStateActive(bool state) {this->active = state;}
void Instrument::setCanDraw(bool state) {this->canDraw = state;}
void Instrument::setCanDrawConnection(bool state) {this->canDrawConnection = state;}
void Instrument::setActiveNotes(std::vector<std::string> newVec) {selectedNotesVec = std::move(newVec);}
//void Instrument::notesActivate() {std::cout << "Activating Notes" << std::endl;}
void Instrument::notesActivate() {;}

//void Instrument::addSelectNote(std::vector<std::string> newVec) {selectedNotesVec = std::move(newVec);}

void Instrument::destroy() {
    std::cout << "Destroying Instrument" << std::endl;
}

bool Instrument::isHovering(Vector2 mousePos) {
    return false;
}

std::vector<std::string> Instrument::getActiveNotes() {
    return {};
}

void Instrument::appendActiveNotes(std::string appendedNote) {
    int x = 2;  // Placeholder
}


// TODO: This seems weird
std::vector<std::string> Instrument::sharedNotesVec;
void Instrument::addNoteShared(const std::string& note) {
    // Only add if not currently in sharedNotesVec
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), note) == sharedNotesVec.end()) {
        sharedNotesVec.emplace_back(note);
        std::cout << "Note added to Share Notes Vec: " << note << std::endl;
    }
}

void Instrument::printNotesShared() {
    for (const auto& item : sharedNotesVec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void Instrument::removeNoteShared(const std::string& note) {
    auto it = std::find(sharedNotesVec.begin(), sharedNotesVec.end(), note);
    if (it != sharedNotesVec.end()) {
        sharedNotesVec.erase(it);
        std::cout << "Note removed from Share Notes Vec: " << note << std::endl;
    } else {
        std::cout << "Note not found in Share Notes Vec: " << note << std::endl;
    }
}

std::vector<std::string> Instrument::getNotesShared() {return sharedNotesVec;}

//std::vector<std::vector<int>> Instrument::getNoteClickedBoolVec() {
//    return {};
//}

//void Instrument::setNoteClickBoolVec(std::vector<std::vector<int>> newVec) {
//    int x  = 2;  // Placeholder
//}












