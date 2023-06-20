//
// Created by tyler on 6/20/2023.
//

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

void ScalesMenu::setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>>& instrumentsVec) {
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

    // TODO: Chord Test
    else if (GuiButton((Rectangle){container.x + (container.width * .01f), container.y + (container.height * .21f), container.width * .3f, container.height * .1f}, "Major7 Chord")) {
        std::vector<std::string> newNotesVec;
        newNotesVec.emplace_back("C");
        newNotesVec.emplace_back("E");
        newNotesVec.emplace_back("G");
        newNotesVec.emplace_back("B");
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
    else if (GuiButton((Rectangle){container.x + (container.width * .01f), container.y + (container.height * .31f), container.width * .3f, container.height * .1f}, "Minor Triad")) {
        std::vector<std::string> newNotesVec;
        newNotesVec.emplace_back("C");
        newNotesVec.emplace_back("Eb");
        newNotesVec.emplace_back("G");
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }
    }
}

//std::vector<std::string> ScalesMenu::setScale(float screenWidth, float screenHeight, const std::vector<std::unique_ptr<Instrument>>& instrumentsVec) {
//    std::vector<std::string> newNotesVec;
//    if (GuiButton((Rectangle){screenWidth * .9f, screenHeight * .7f, screenWidth * .1f, screenHeight * .1f}, "C Major")) {
//        //newNotesVec.clear();  // TODO: Would prefer this as part of instrument class, but struggling to implement
//        newNotesVec.emplace_back("C");
//        newNotesVec.emplace_back("D");
//        newNotesVec.emplace_back("E");
//        newNotesVec.emplace_back("F");
//        newNotesVec.emplace_back("G");
//        newNotesVec.emplace_back("A");
//        newNotesVec.emplace_back("B");
//
//        for (const auto & instrument : instrumentsVec) {
//                instrument->setNotesShared(newNotesVec);
//        }
//    }
//    return newNotesVec;
//}
