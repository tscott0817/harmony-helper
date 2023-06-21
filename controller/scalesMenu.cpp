#include "scalesMenu.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

ScalesMenu::ScalesMenu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    containerCenter = {container.width / 2, container.height / 2};
    containerTexture = LoadTexture("../images/plaid.png");
}

void ScalesMenu::draw() {
    DrawRectangle(container.x, container.y, container.width, container.height, bgColor);
}

void ScalesMenu::setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>>& instrumentsVec) const {
    if (GuiButton((Rectangle){container.x + (container.width * .01f), container.y + (container.height * .01f), container.width * .3f, container.height * .1f}, "Major")) {
        std::vector<std::string> newNotesVec;
        newNotesVec.emplace_back("C");
        newNotesVec.emplace_back("D");
        newNotesVec.emplace_back("E");
        newNotesVec.emplace_back("F");
        newNotesVec.emplace_back("G");
        newNotesVec.emplace_back("A");
        newNotesVec.emplace_back("B");

        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    else if (GuiButton((Rectangle){container.x + (container.width * .01f), container.y + (container.height * .11f), container.width * .3f, container.height * .1f}, "Minor")) {
        std::vector<std::string> newNotesVec;
        newNotesVec.emplace_back("C");
        newNotesVec.emplace_back("D");
        newNotesVec.emplace_back("Eb");
        newNotesVec.emplace_back("F");
        newNotesVec.emplace_back("G");
        newNotesVec.emplace_back("Ab");
        newNotesVec.emplace_back("Bb");
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
}
