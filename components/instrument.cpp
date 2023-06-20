#include "instrument.h"
#include <utility>
#include <algorithm>

// Make constructor
Instrument::Instrument() = default;
Instrument::~Instrument() = default;

/**
 *  The base class shares a vector of data (notes) between the inherited classes (instruments).
 *  The vector is used to set appropriate notes for every instrument as they are selected.
 *  These methods allow interactions with that shared vector of notes.
 */
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

void Instrument::clearNotesShared() {
    sharedNotesVec.clear();
    std::cout << "Shared Notes Vec cleared: " << std::endl;
    printNotesShared();
}

// TODO: This needs to replace the entire sharedNotesVec, right now it just adds to the end of it?
void Instrument::setNotesShared(std::vector<std::string> notesVec) {
        sharedNotesVec = std::move(notesVec);
        std::cout << "Shared Notes Vec Replaced With: " << std::endl;
        printNotesShared();
}

std::vector<std::string> Instrument::getNotesShared() {return sharedNotesVec;}

void Instrument::printNotesShared() {
    std::cout << "Full sharedNotesVec: ";
    for (const auto& item : sharedNotesVec) {
        std::cout << item << " ";
    }
    std::cout << "\n" << std::endl;
}













