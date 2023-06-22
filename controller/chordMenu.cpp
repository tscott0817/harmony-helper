#include "chordMenu.h"
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

ChordMenu::ChordMenu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    containerCenter = {container.width / 2, container.height / 2};
    containerTexture = LoadTexture("../images/plaid.png");

    dropdownBox001Active = 0;
    dropDown001EditMode = false;
    currentRoot = "A";

    // Custom GUI font loading
    Font font = LoadFontEx("../resources/fonts/OpenSans-Light.ttf", 25, nullptr, 0);
    GuiSetFont(font);

    // Setup texture scaling filter
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);
}

void ChordMenu::draw() {
    // DrawRectangle(container.x, container.y, container.width, container.height, bgColor);
    DrawRectangleRounded(container, 0.05f, 0, bgColor);
}

void ChordMenu::setChord(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>>& instrumentsVec) {

    // TODO: Put these before each GUI element to style them individually
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, buttonTextColor);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, buttonColor);   // TODO: Don't hard code this
    GuiSetStyle(BUTTON, BORDER_WIDTH, 2);

    /** Triads **/
    if (GuiButton((Rectangle){container.x + (container.width * .35f), container.y + (container.height * .05f), container.width * .3f, container.height * .1f}, "Major")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                // Find the index of the third and fifth degrees based on the major scale
                int thirdIndex = (i + 4) % 12;
                int fifthIndex = (i + 7) % 12;

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .675f), container.y + (container.height * .05f), container.width * .3f, container.height * .1f}, "Minor")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                // Find the index of the third and fifth degrees based on the major scale
                int thirdIndex = (i + 3) % 12;
                int fifthIndex = (i + 7) % 12;

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .35f), container.y + (container.height * .175f), container.width * .3f, container.height * .1f}, "Diminished")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                int thirdIndex = (i + 3) % 12;
                int fifthIndex = (i + 6) % 12;

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);

                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .675f), container.y + (container.height * .175f), container.width * .3f, container.height * .1f}, "Augmented")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                int thirdIndex = (i + 4) % 12;
                int fifthIndex = (i + 8) % 12;

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }

    /** 7th Chords **/
    if (GuiButton((Rectangle){container.x + (container.width * .35f), container.y + (container.height * .3f), container.width * .3f, container.height * .1f}, "Major7")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                int thirdIndex = (i + 4) % 12;  // Major 3rd interval
                int fifthIndex = (i + 7) % 12;  // Perfect 5th interval
                int seventhIndex = (i + 11) % 12;  // Major 7th interval

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                newNotesVec.emplace_back(rootNoteVec[seventhIndex]);

                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .675f), container.y + (container.height * .3f), container.width * .3f, container.height * .1f}, "Minor7")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                int thirdIndex = (i + 3) % 12;  // Minor 3rd interval
                int fifthIndex = (i + 7) % 12;  // Perfect 5th interval
                int seventhIndex = (i + 10) % 12;  // Minor 7th interval

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                newNotesVec.emplace_back(rootNoteVec[seventhIndex]);
                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .35f), container.y + (container.height * .425f), container.width * .3f, container.height * .1f}, "Dominant7")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                int thirdIndex = (i + 4) % 12;  // Major 3rd interval
                int fifthIndex = (i + 7) % 12;  // Perfect 5th interval
                int seventhIndex = (i + 10) % 12;  // Minor 7th interval

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                newNotesVec.emplace_back(rootNoteVec[seventhIndex]);

                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .675f), container.y + (container.height * .425f), container.width * .3f, container.height * .1f}, "Diminished7")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                int thirdIndex = (i + 3) % 12;  // Minor 3rd interval
                int fifthIndex = (i + 6) % 12;  // Diminished 5th interval
                int seventhIndex = (i + 9) % 12;  // Diminished 7th interval

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                newNotesVec.emplace_back(rootNoteVec[seventhIndex]);

                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .35f), container.y + (container.height * .55f), container.width * .3f, container.height * .1f}, "Half-Dim7")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                int thirdIndex = (i + 3) % 12;  // Minor 3rd interval
                int fifthIndex = (i + 6) % 12;  // Diminished 5th interval
                int seventhIndex = (i + 10) % 12;  // Minor 7th interval

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                newNotesVec.emplace_back(rootNoteVec[seventhIndex]);

                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .675f), container.y + (container.height * .55f), container.width * .3f, container.height * .1f}, "Min-Maj7")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < rootNoteVec.size(); i++) {
            if (currentRoot == rootNoteVec[i]) {
                int thirdIndex = (i + 3) % 12;  // Minor 3rd interval
                int fifthIndex = (i + 7) % 12;  // Perfect 5th interval
                int seventhIndex = (i + 11) % 12;  // Major 7th interval

                newNotesVec.emplace_back(rootNoteVec[i]);
                newNotesVec.emplace_back(rootNoteVec[thirdIndex]);
                newNotesVec.emplace_back(rootNoteVec[fifthIndex]);
                newNotesVec.emplace_back(rootNoteVec[seventhIndex]);

                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }

    // TODO: Put in separate function?
    // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding
    GuiUnlock();
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_NORMAL, buttonTextColor);
    GuiSetStyle(DROPDOWNBOX, BASE_COLOR_NORMAL, buttonColor);   // TODO: Don't hard code this
    GuiSetStyle(DROPDOWNBOX, BORDER_WIDTH, 2);
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    if (GuiDropdownBox((Rectangle){ container.x + (container.width * .025f), container.y + (container.height * .05f), container.width * .3f, container.height * .05f},
                       "A;A#/Bb;B;C;C#/Db;D;D#/Eb;E;F;F#/Gb;G;G#/Ab", &dropdownBox001Active, dropDown001EditMode)) {
        dropDown001EditMode = !dropDown001EditMode;
        currentRoot = rootNoteVec[dropdownBox001Active];  // Checks current key as a string based on the index of the dropdown box
    }
    // TODO: The (#num# is for the symbol before the text
//    if (GuiDropdownBox((Rectangle){ container.x + (container.width * .05f), container.y + (container.height * .05f), 125, 30 },
//                       "#01#A;#02#A#/Bb;#03#B;#04#C;#05#C#/Db;#06#D;", &dropdownBox001Active, dropDown001EditMode)) {
//        dropDown001EditMode = !dropDown001EditMode;
//        currentKey = scaleNoteVec[dropdownBox001Active];  // Checks current key as a string based on the index of the dropdown box
//    }
}

void ChordMenu::setKey(std::string key) {
    currentRoot = std::move(key);
}

std::string ChordMenu::getKey() {return currentRoot;}