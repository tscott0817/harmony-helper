#include "menu.h"

// Create constructor for menu
Menu::Menu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    /** Init **/
    active = 0;
    editMode = false;
//    blackBackground = {25, 25, 25, 125};
    blackBackground = {25, 25, 25, 200};

    canDraw = true;

    /** Parent Container **/
    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    containerCenter = {container.width / 2, container.height / 2};
    containerTexture = LoadTexture("../images/plaid.png");


    /** Buttons **/
    // TODO: Want the put all instruments into own menu
    buttonOneRec = {container.x + (container.width * .005f), container.y + (container.height * .12f), container.width * .1f, container.height * .75f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonOneCenter = {static_cast<float>(buttonOneRec.width / 2), static_cast<float>(buttonOneRec.height / 2)};

    buttonTwoRec = {container.x + (container.width * .1095f), container.y + (container.height * .12f), container.width * .1f, container.height * .75f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonTwoCenter = {static_cast<float>(buttonTwoRec.width / 2), static_cast<float>(buttonTwoRec.height / 2)};

    // TODO: The menu items
    buttonThreeRec = {container.x + (container.width * .2130f), container.y + (container.height * .12f), container.width * .1f, container.height * .75f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonThreeCenter = {static_cast<float>(buttonThreeRec.width / 2), static_cast<float>(buttonThreeRec.height / 2)};

    buttonFourRec = {container.x + (container.width * .3175f), container.y + (container.height * .12f), container.width * .1f, container.height * .75f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonFourCenter = {static_cast<float>(buttonThreeRec.width / 2), static_cast<float>(buttonThreeRec.height / 2)};

    buttonLocAdded = false;

    /** Colors **/
    baseColor = Color{225, 225, 225, 255};
    currentColor = BLUE;
    hoverColor = RED;
//    activeColor = {150, 150, 150, 255};
//    activeColor = {173, 82, 59, 255};
    activeColor = {76, 127, 194, 255};

    /** Vector Inits **/
    // TODO: Just filling to 100 for room, but don't want to hardcode this 100
    for (int i = 0; i < 100; i++) {
        buttonLocations.emplace_back(Vector2 {0, 0});
        buttonColorVec.emplace_back(baseColor);
        activeVec.emplace_back(0);
    }
    isHovering = false;  // TODO: This is never used
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
//    DrawRectangle(container.x, container.y, container.width, container.height, blackBackground);
//    DrawRectangle(buttonOneRec.x, buttonOneRec.y, buttonOneRec.width, buttonOneRec.height, buttonColorVec[0]);
//    DrawRectangle(buttonTwoRec.x, buttonTwoRec.y, buttonTwoRec.width, buttonTwoRec.height, buttonColorVec[1]);
//    DrawRectangle(buttonThreeRec.x, buttonThreeRec.y, buttonThreeRec.width, buttonThreeRec.height, buttonColorVec[2]);
//    DrawRectangle(buttonFourRec.x, buttonFourRec.y, buttonFourRec.width, buttonFourRec.height, buttonColorVec[3]);

    DrawRectangleRounded(container, 0.05f, 0, blackBackground);
    DrawRectangleRounded(buttonOneRec, 0.75f, 0, buttonColorVec[0]);
    DrawRectangleRounded(buttonTwoRec, 0.75f, 0, buttonColorVec[1]);
    DrawRectangleRounded(buttonThreeRec, 0.75f, 0, buttonColorVec[2]);
    DrawRectangleRounded(buttonFourRec, 0.75f, 0, buttonColorVec[3]);

    if (!buttonLocAdded) {
        buttonLocations[0] = {buttonOneRec.x, buttonOneRec.y};
        buttonLocations[1] = {buttonTwoRec.x, buttonTwoRec.y};
        buttonLocations[2] = {buttonThreeRec.x, buttonThreeRec.y};
        buttonLocations[3] = {buttonFourRec.x, buttonFourRec.y};
        buttonLocAdded = true;
    }

    float buttonTextSize = (buttonOneRec.width > buttonOneRec.height) ? static_cast<float>(buttonOneRec.height) : static_cast<float>(buttonOneRec.width);
    Vector2 buttonOneLoc = {buttonOneRec.x + (buttonOneRec.width * .25f), buttonOneRec.y};
    DrawTextEx(testFont, "Guitar", buttonOneLoc, buttonTextSize, 0, BLACK);

    float buttonTwoTextSize = (buttonTwoRec.width > buttonTwoRec.height) ? static_cast<float>(buttonTwoRec.height) : static_cast<float>(buttonTwoRec.width);
    Vector2 buttonTwoNewLoc = {buttonTwoRec.x + (buttonTwoRec.width * .25f), buttonTwoRec.y};
    DrawTextEx(testFont, "Piano", buttonTwoNewLoc, buttonTwoTextSize, 0, BLACK);

    float buttonThreeTextSize = (buttonThreeRec.width > buttonThreeRec.height) ? static_cast<float>(buttonThreeRec.height) : static_cast<float>(buttonThreeRec.width);
    Vector2 buttonThreeNewLoc = {buttonThreeRec.x + (buttonThreeRec.width * .25f), buttonThreeRec.y};
    DrawTextEx(testFont, "Scales", buttonThreeNewLoc, buttonThreeTextSize, 0, BLACK);

    float buttonFourTextSize = (buttonFourRec.width > buttonFourRec.height) ? static_cast<float>(buttonFourRec.height) : static_cast<float>(buttonFourRec.width);
    Vector2 buttonFourNewLoc = {buttonFourRec.x + (buttonFourRec.width * .21f), buttonFourRec.y};
    DrawTextEx(testFont, "Chords", buttonFourNewLoc, buttonFourTextSize, 0, BLACK);
}

void Menu::hover(Vector2 mousePos) {
    for (int i = 0; i < buttonLocations.size(); i++) {
        // For individual buttons
        if (mousePos.x > buttonLocations[i].x && mousePos.x < buttonLocations[i].x + (buttonOneRec.width) &&
            mousePos.y > buttonLocations[i].y && mousePos.y < buttonLocations[i].y + (buttonOneRec.height)) {
            currentButton = i;
            click(currentButton);
            isHovering = true;
        }
        else {
            buttonColorVec[currentButton] = buttonColorVec[currentButton];
            isHovering = false;
        }

        // For entire menu bar
        if (mousePos.x > container.x && mousePos.x < container.x + (container.width) &&
            mousePos.y > container.y && mousePos.y < container.y + (container.height)) {
            isHovering = true;
        }
        else {
            isHovering = false;
        }
    }
}

void Menu::click(int currButton) {  // Don't need param, could use currentButton, but feel this shows intent better
    // Check if left mouse clicked
    // TODO: Need to add a check to not allow more than one menu item visible at a time.
    // TODO: Need some separattion between menus and instrument selection, probably put instrument selection in its own menu
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (activeVec[currButton] == 0) {
            activeVec[currButton] = 1;
            buttonColorVec[currButton] = activeColor;
        }
        else {
            activeVec[currButton] = 0;
            buttonColorVec[currButton] = baseColor;
        }
    }
}

// Setters
void Menu::setActiveButton(int activeButton, int index){
    //this->active = activeButton;
    // set activeButton in activeVec at index
    activeVec[index] = activeButton;
}

// Getters
std::vector<int> Menu::getActiveButtons(){
    // return the active vector
    return activeVec;
}

void Menu::deactivateButton(int index) {
    activeVec[index] = 0;
    buttonColorVec[index] = baseColor;
}
