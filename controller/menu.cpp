#include "menu.h"


// Create constructor for menu
Menu::Menu(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    /** Init **/
    active = 0;
    editMode = false;
    blackBackground = {0, 0, 0, 150};
    canDraw = true;

    /** Parent Container **/
    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height
    containerCenter = {container.width / 2, container.height / 2};
    containerTexture = LoadTexture("../images/plaid.png");


    /** Buttons **/
    buttonOneRec = {container.x + (container.width * .0005f), container.y + (container.height * .06f), container.width * .1f, container.height * .9f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonOneCenter = {static_cast<float>(buttonOneRec.width / 2), static_cast<float>(buttonOneRec.height / 2)};

    buttonTwoRec = {container.x + (container.width * .1025f), container.y + (container.height * .06f), container.width * .1f, container.height * .9f}; // TODO: Fill container with neck (Currently have padding for testing)
    buttonTwoCenter = {static_cast<float>(buttonTwoRec.width / 2), static_cast<float>(buttonTwoRec.height / 2)};

    buttonLocAdded = false;

    /** Colors **/
    baseColor = BLUE;
    currentColor = BLUE;
    hoverColor = RED;
    activeColor = {34, 61, 156, 255};

    /** Vector Inits **/
    // TODO: Just filling to 100 for room, but don't want to hardcode this 100
    for (int i = 0; i < 100; i++) {
        buttonLocations.push_back({0, 0});
        buttonColorVec.push_back(baseColor);
        activeVec.push_back(0);
    }
    isHovering = false;
    currentButton = 0;

    /** GUI Stuff **/
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);  // Default text size

    testFont = LoadFontEx("../resources/OpenSans-Light.ttf", 200, nullptr, 100);
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
    DrawRectangle(container.x, container.y, container.width, container.height, blackBackground);
    DrawRectangle(buttonOneRec.x, buttonOneRec.y, buttonOneRec.width, buttonOneRec.height, buttonColorVec[0]);
    DrawRectangle(buttonTwoRec.x, buttonTwoRec.y, buttonTwoRec.width, buttonTwoRec.height, buttonColorVec[1]);
    if (!buttonLocAdded) {
        buttonLocations[0] = {buttonOneRec.x, buttonOneRec.y + (container.height * .06f)};
        buttonLocations[1] = {buttonTwoRec.x, buttonTwoRec.y + (container.height * .06f)};
        buttonLocAdded = true;
    }
    float buttonTextSize = (buttonOneRec.width > buttonOneRec.height) ? static_cast<float>(buttonOneRec.height) : static_cast<float>(buttonOneRec.width);
    Vector2 buttonNewLoc = {buttonOneRec.x + (buttonOneRec.width * .25f), buttonOneRec.y};
    DrawTextEx(testFont, "Guitar", buttonNewLoc, buttonTextSize, 0, WHITE);

    float buttonTwoTextSize = (buttonTwoRec.width > buttonTwoRec.height) ? static_cast<float>(buttonTwoRec.height) : static_cast<float>(buttonTwoRec.width);
    Vector2 buttonTwoNewLoc = {buttonTwoRec.x + (buttonTwoRec.width * .25f), buttonTwoRec.y};
    DrawTextEx(testFont, "Piano", buttonTwoNewLoc, buttonTwoTextSize, 0, WHITE);
}

// TODO: Implement hovering color change
void Menu::hover(Vector2 mousePos) {
    for (int i = 0; i < buttonLocations.size(); i++) {
        // For individual buttons
        if (mousePos.x > buttonLocations[i].x && mousePos.x < buttonLocations[i].x + (buttonOneRec.width) &&
            mousePos.y > buttonLocations[i].y && mousePos.y < buttonLocations[i].y + (buttonOneRec.height)) {
            currentButton = i;
            //buttonColorVec[currentButton] = hoverColor;
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
