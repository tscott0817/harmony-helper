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
    if (GuiButton((Rectangle){container.x + (container.width * .01f), container.y + (container.height * .21f), container.width * .3f, container.height * .1f}, "Major")) {
        std::vector<std::string> newNotesVec;

        // TODO: Make this a function
        if (currentKey == "A") {
            newNotesVec.emplace_back("A");
            newNotesVec.emplace_back("B");
            newNotesVec.emplace_back("Db");
            newNotesVec.emplace_back("D");
            newNotesVec.emplace_back("E");
            newNotesVec.emplace_back("Gb");
        }
        else if (currentKey == "Bb") {
            newNotesVec.emplace_back("Bb");
            newNotesVec.emplace_back("C");
            newNotesVec.emplace_back("Eb");
            newNotesVec.emplace_back("F");
            newNotesVec.emplace_back("G");
            newNotesVec.emplace_back("A");
        }
        // TODO: Just doing C for testing
        else {
            newNotesVec.emplace_back("C");
            newNotesVec.emplace_back("D");
            newNotesVec.emplace_back("E");
            newNotesVec.emplace_back("F");
            newNotesVec.emplace_back("G");
            newNotesVec.emplace_back("A");
            newNotesVec.emplace_back("B");
        }

        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }

    // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding
    GuiUnlock();
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    if (GuiDropdownBox((Rectangle){ 25, 65, 125, 30 }, "#01#A;#02#A#/Bb;#03#B;#04#C", &dropdownBox001Active, dropDown001EditMode)) {
        dropDown001EditMode = !dropDown001EditMode;
        if (dropdownBox001Active == 0) {
            // setKey("A");
            currentKey = "A";
        }
        else if (dropdownBox001Active == 1) {
            // setKey("Bb");
            currentKey = "Bb";
        }
        else if (dropdownBox001Active == 2) {
            // setKey("B");
            currentKey = "B";
        }
        else if (dropdownBox001Active == 3) {
            // setKey("C");
            currentKey = "C";
        }
    }
}

void ScalesMenu::setKey(std::string key) {
    currentKey = std::move(key);
}

std::string ScalesMenu::getKey() {return currentKey;}
