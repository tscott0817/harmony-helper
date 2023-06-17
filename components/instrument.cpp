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

/** Getters **/
bool Instrument::getCanDraw() {return false;}

/** Setters **/
void Instrument::setCanDraw(bool state) {this->canDraw = state;}
void Instrument::notesActivate() {;}

void Instrument::destroy() {
    std::cout << "Destroying Instrument" << std::endl;
}

// TODO: This seems weird, but get undefined reference otherwise
std::vector<std::string> Instrument::sharedNotesVec;
void Instrument::addNoteShared(const std::string& note) {
    // Only add if not currently in sharedNotesVec
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), note) == sharedNotesVec.end()) {
        sharedNotesVec.emplace_back(note);
        std::cout << "Note added to Share Notes Vec: " << note << std::endl;
        printNotesShared();
    }
}

void Instrument::removeNoteShared(const std::string& note) {
    auto it = std::find(sharedNotesVec.begin(), sharedNotesVec.end(), note);
    if (it != sharedNotesVec.end()) {
        sharedNotesVec.erase(it);
        std::cout << "Note removed from Share Notes Vec: " << note << std::endl;
    } else {
        std::cout << "Note not found in Share Notes Vec: " << note << std::endl;
    }
    printNotesShared();
}


void Instrument::printNotesShared() {
    std::cout << "Full sharedNotesVec: ";
    for (const auto& item : sharedNotesVec) {
        std::cout << item << " ";
    }
    std::cout << "\n" << std::endl;
}













