#include "scalesMenu.h"
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

ScalesMenu::ScalesMenu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    containerCenter = {container.width / 2, container.height / 2};
    containerTexture = LoadTexture("../images/plaid.png");

    dropdownBox001Active = 0;
    dropDown001EditMode = false;
    currentKey = "A";
}

void ScalesMenu::draw() {
    // DrawRectangle(container.x, container.y, container.width, container.height, bgColor);
    DrawRectangleRounded(container, 0.05f, 0, bgColor);
}

void ScalesMenu::setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>>& instrumentsVec) {

    // TODO: Make GuiButton for each scale type
    if (GuiButton((Rectangle){container.x + (container.width * .35f), container.y + (container.height * .05f), container.width * .3f, container.height * .1f}, "Major")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < scaleNoteVec.size(); i++) {
            if (currentKey == scaleNoteVec[i]) {
                // The minor scale pattern is W-W-H-W-W-W-H
                newNotesVec.emplace_back(scaleNoteVec[i]);
                newNotesVec.emplace_back(scaleNoteVec[i + 2]);
                newNotesVec.emplace_back(scaleNoteVec[i + 4]);
                newNotesVec.emplace_back(scaleNoteVec[i + 5]);
                newNotesVec.emplace_back(scaleNoteVec[i + 7]);
                newNotesVec.emplace_back(scaleNoteVec[i + 9]);
                newNotesVec.emplace_back(scaleNoteVec[i + 11]);
                break;
            }
        }
        // TODO: Not sure I want to do this, maybe just return the newly created vec and assign in main
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    if (GuiButton((Rectangle){container.x + (container.width * .35f), container.y + (container.height * .175f), container.width * .3f, container.height * .1f}, "Minor")) {
        std::vector<std::string> newNotesVec;
        for (int i = 0; i < scaleNoteVec.size(); i++) {
            if (currentKey == scaleNoteVec[i]) {
                // The minor scale pattern is W-H-W-W-H-W-W
                newNotesVec.emplace_back(scaleNoteVec[i]);
                newNotesVec.emplace_back(scaleNoteVec[i + 2]);
                newNotesVec.emplace_back(scaleNoteVec[i + 3]);
                newNotesVec.emplace_back(scaleNoteVec[i + 5]);
                newNotesVec.emplace_back(scaleNoteVec[i + 7]);
                newNotesVec.emplace_back(scaleNoteVec[i + 8]);
                newNotesVec.emplace_back(scaleNoteVec[i + 10]);
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
    if (GuiDropdownBox((Rectangle){ container.x + (container.width * .025f), container.y + (container.height * .05f), container.width * .3f, container.height * .05f},
                       "A;A#/Bb;B;C;C#/Db;D;D#/Eb;E;F;F#/Gb;G;G#/Ab", &dropdownBox001Active, dropDown001EditMode)) {
        dropDown001EditMode = !dropDown001EditMode;
        currentKey = scaleNoteVec[dropdownBox001Active];  // Checks current key as a string based on the index of the dropdown box
    }
    // TODO: The (#num# is for the symbol before the text
//    if (GuiDropdownBox((Rectangle){ container.x + (container.width * .05f), container.y + (container.height * .05f), 125, 30 },
//                       "#01#A;#02#A#/Bb;#03#B;#04#C;#05#C#/Db;#06#D;", &dropdownBox001Active, dropDown001EditMode)) {
//        dropDown001EditMode = !dropDown001EditMode;
//        currentKey = scaleNoteVec[dropdownBox001Active];  // Checks current key as a string based on the index of the dropdown box
//    }
}

void ScalesMenu::setKey(std::string key) {
    currentKey = std::move(key);
}

std::string ScalesMenu::getKey() {return currentKey;}
