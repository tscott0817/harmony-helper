#include "chordMenu.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

ChordMenu::ChordMenu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    containerCenter = {container.width / 2, container.height / 2};

    buttonOneRec = {container.x + (container.width * .01f), container.y + (container.height * .25f), container.width * .3f, container.height * .1f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonOneCenter = {static_cast<float>(buttonOneRec.width / 2), static_cast<float>(buttonOneRec.height / 2)};

    buttonTwoRec = {container.x + (container.width * .01f), container.y + (container.height * .5f), container.width * .3f, container.height * .1f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonTwoCenter = {static_cast<float>(buttonOneRec.width / 2), static_cast<float>(buttonOneRec.height / 2)};

    /** Vector Inits **/
    baseColor = BLUE;
    activeColor = {34, 61, 156, 255};
    // TODO: Just filling to 100 for room, but don't want to hardcode this 100
    for (int i = 0; i < 100; i++) {
        buttonLocations.emplace_back(Vector2 {0, 0});
        buttonColorVec.emplace_back(baseColor);
        activeVec.emplace_back(0);
    }
    // isHovering = false;  // TODO: This is never used
    currentButton = 0;

    /** GUI Stuff **/
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);  // Default text size

    testFont = LoadFontEx("../resources/fonts/OpenSans-Light.ttf", 200, nullptr, 100);
    GenTextureMipmaps(&testFont.texture);
    fontSize = (float)testFont.baseSize;
    fontPosition = { 500.0f, 1200.0f};
    textSize = { 10.0f, 10.0f };

    // Setup texture scaling filter
    SetTextureFilter(testFont.texture, TEXTURE_FILTER_TRILINEAR);
}

void ChordMenu::draw() {
    DrawRectangle(container.x, container.y, container.width, container.height, bgColor);

    /** Buttons **/
    DrawRectangle(buttonOneRec.x, buttonOneRec.y, buttonOneRec.width, buttonOneRec.height, buttonColorVec[0]);
    DrawRectangle(buttonTwoRec.x, buttonTwoRec.y, buttonTwoRec.width, buttonTwoRec.height, buttonColorVec[1]);

    if (!buttonLocAdded) {  // Should never change relative to window size, so only need to do this once
        buttonLocations[0] = {buttonOneRec.x, buttonOneRec.y};
        buttonLocations[1] = {buttonTwoRec.x, buttonTwoRec.y};
        buttonLocAdded = true;
    }

    float buttonTextSize = (buttonOneRec.width > buttonOneRec.height) ? static_cast<float>(buttonOneRec.height * .9f) : static_cast<float>(buttonOneRec.width * .9f);
    Vector2 buttonOneLoc = {buttonOneRec.x + (buttonOneRec.width * .05f), buttonOneRec.y};
    DrawTextEx(testFont, "Major 7", buttonOneLoc, buttonTextSize, 0, WHITE);

    float buttonTwoTextSize = (buttonTwoRec.width > buttonTwoRec.height) ? static_cast<float>(buttonTwoRec.height * .9f) : static_cast<float>(buttonTwoRec.width * .9f);
    Vector2 buttonTwoLoc = {buttonTwoRec.x + (buttonTwoRec.width * .05f), buttonTwoRec.y};
    DrawTextEx(testFont, "Minor Triad", buttonTwoLoc, buttonTwoTextSize, 0, WHITE);
}

void ChordMenu::click(int currButton) {  // Don't need param, could use currentButton, but feel this shows intent better
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        std::cout << "Clicked Button" << std::endl;
        if (activeVec[currButton] == 0) {
            activeVec[currButton] = 1;
            // Set all other activeVec[currButton] to 0
            for (int i = 0; i < activeVec.size(); i++) {
                if (i != currButton) {
                    activeVec[i] = 0;
                    buttonColorVec[i] = baseColor;
                }
            }
            buttonColorVec[currButton] = activeColor;
        }
        else {
            activeVec[currButton] = 0;
            buttonColorVec[currButton] = baseColor;
        }

        // If any activeVec[currButton] == 1, then set all others to 0
    }
}

void ChordMenu::chooseButton(Vector2 mousePos) {
    // Determine which button was pressed
    for (int i = 0; i < buttonLocations.size(); i++) {
        // For individual buttons
        if (mousePos.x > buttonLocations[i].x && mousePos.x < buttonLocations[i].x + (buttonOneRec.width) &&
            mousePos.y > buttonLocations[i].y && mousePos.y < buttonLocations[i].y + (buttonOneRec.height)) {
            currentButton = i;
            click(currentButton);
        }
//        else {
//            buttonColorVec[currentButton] = buttonColorVec[currentButton];
//        }
    }
}

void ChordMenu::setChord(const std::vector<std::unique_ptr<Instrument>>& instrumentsVec) {
    if (activeVec[0] == 1) {
        std::vector<std::string> newNotesVec;
        newNotesVec.emplace_back("C");
        newNotesVec.emplace_back("E");
        newNotesVec.emplace_back("G");
        newNotesVec.emplace_back("B");
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }

        // Make all other buttons inactive
        activeVec[1] = 0;
    }
    else if (activeVec[1] == 1) {
        std::vector<std::string> newNotesVec;
        newNotesVec.emplace_back("C");
        newNotesVec.emplace_back("Eb");
        newNotesVec.emplace_back("G");
        for (const auto & instrument : instrumentsVec) {
            instrument->setNotesShared(newNotesVec);
        }

        // Make all other buttons inactive
        activeVec[0] = 0;
    }
    else {
        for (const auto & instrument : instrumentsVec) {
            instrument->clearNotesShared();
        }
    }
}

void ChordMenu::resetMenu(const std::vector<std::unique_ptr<Instrument>>& instrumentsVec) {

    // Clear the instrument notes
//    for (const auto & instrument : instrumentsVec) {
//        // instrument->setNotesShared(newNotesVec);
//        instrument->clearNotesShared();
//    }

    for (int & activeButton : activeVec) {
        activeButton = 0;
    }

    for (auto & buttonColor : buttonColorVec) {
        buttonColor = baseColor;
    }
}
