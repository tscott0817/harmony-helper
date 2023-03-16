#include "menu.h"


// Create constructor for menu
Menu::Menu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    active = 0;
    editMode = false;
    blackBackground = {0, 0, 0, 150};
    canDraw = true;

    // Only change the position and size of neckContainer (Make this the params the user can change, drop down menu)
    // container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    containerCenter = {container.width / 2, container.height / 2};
    containerTexture = LoadTexture("../images/plaid.png");

    // Use the container position +/- some integer to move child objects
    // Use the size of the container * some float to resize child object
    buttonOneRec = {container.x, + (container.height * .06f), container.width * .1f, container.height * .9f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonOneCenter = {static_cast<float>(buttonOneRec.width / 2), static_cast<float>(buttonOneRec.height / 2)};

    buttonTwoRec = {container.x + (container.width * .25f), container.y + (container.height * .06f), container.width * .1f, container.height * .9f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonTwoCenter = {static_cast<float>(buttonTwoRec.width / 2), static_cast<float>(buttonTwoRec.height / 2)};

    buttonLocAdded = false;

    // TODO: Just filling to 100 for room, but don't want to hardcode this 100
    baseColor = BLUE;
    currentColor = BLUE;
    hoverColor = RED;
    activeColor = GREEN;
    for (int i = 0; i < 100; i++) {
        buttonLocations.push_back({0, 0});
        buttonColorVec.push_back(baseColor);
        activeVec.push_back(0);
    }
    // Insert random colors into index 1, 2, 3
    buttonColorVec[0] = BLACK;
    buttonColorVec[1] = PURPLE;
    buttonColorVec[2] = GREEN;
    buttonColorVec[3] = YELLOW;
    isHovering = false;
    currentButton = 0;

    /** GUI Stuff **/
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);  // Default text size
}

void Menu::setBackground(int screenWidth, int screenHeight) {
        GuiGrid((Rectangle){0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight)}, "Guitar Grid", 40.0f, 4); // Draw a fancy grid
}

void Menu::drawTopMenu(int width, int height) {
    /** Container **/
//    DrawTexturePro(containerTexture,
//                   container,
//                   (Rectangle) {container.x, container.y, container.width, container.height},  /** Params = (x-pos, y-pos, height, width) **/
//                   containerCenter, 0, WHITE);

    // Draw a rectangle that is the size of the container
    DrawRectangle(container.x, container.y, container.width, container.height, blackBackground);
    DrawRectangle(buttonOneRec.x, buttonOneRec.y, buttonOneRec.width, buttonOneRec.height, buttonColorVec[0]);
    DrawRectangle(buttonTwoRec.x, buttonTwoRec.y, buttonTwoRec.width, buttonTwoRec.height, buttonColorVec[1]);
    if (!buttonLocAdded) {
        buttonLocations[0] = {buttonOneRec.x, buttonOneRec.y + (container.height * .06f)};
        buttonLocations[1] = {buttonTwoRec.x, buttonTwoRec.y + (container.height * .06f)};
        buttonLocAdded = true;
    }


    //----------------------------------------------------------------------------------
    // Check all possible events that require GuiLock
//    if (editMode) GuiLock();
//    // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding
//    GuiUnlock();
//    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
//    if (GuiDropdownBox((Rectangle){ buttonOneRec.x, buttonOneRec.y + (container.height * .06f), buttonOneRec.width, buttonOneRec.height }, "Guitar;Piano;THREE;FOUR;FIVE;SIX", &active, editMode)) editMode = !editMode;
//    if (!buttonLocAdded) {
//        buttonLocations[0] = {buttonOneRec.x, buttonOneRec.y + (container.height * .06f)};
//    }
    // listViewExActive = GuiListViewEx((Rectangle){ 165, 180, 140, 200 }, listViewExList, 8, &listViewExFocus, &listViewExScrollIndex, listViewExActive);
}

void Menu::hover(Vector2 mousePos) {
    for (int i = 0; i < buttonLocations.size(); i++) {
        // If button currently inactive
        if (mousePos.x > buttonLocations[i].x && mousePos.x < buttonLocations[i].x + (buttonOneRec.width) &&
            mousePos.y > buttonLocations[i].y && mousePos.y < buttonLocations[i].y + (buttonOneRec.height)) {
            currentButton = i;
            buttonColorVec[currentButton] = hoverColor;
            click(currentButton);
        }
        else {
            buttonColorVec[currentButton] = buttonColorVec[currentButton];
        }
    }
}

void Menu::click(int currentButton) {
    // Check if left mouse clicked
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        std::cout << "Left Clicked" << std::endl;
        if (activeVec[currentButton] == 0) {
            activeVec[currentButton] = 1;
            // currentColor = activeColor;
            buttonColorVec[currentButton] = activeColor;
        }
        else {
            activeVec[currentButton] = 0;
            // currentColor = baseColor;
            buttonColorVec[currentButton] = baseColor;
        }
    }
}

// Setters
void Menu::setActiveButton(int activeButton){
    this->active = activeButton;
}

// Getters
std::vector<int> Menu::getActiveButtons(){
    // return the active vector
    return activeVec;
}
