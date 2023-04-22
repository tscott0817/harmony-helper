#include "piano.h"

Piano::Piano(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    containerImage = LoadImage("../images/blue_background.png");     // Loaded in CPU memory (RAM)
    containerTexture = LoadTextureFromImage(containerImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(containerImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
    container = {static_cast<float>(this->screenWidth * posX), static_cast<float>(this->screenHeight * posY), static_cast<float>(this->screenWidth * width), static_cast<float>(this->screenHeight * height)};
    containerCenter = {container.width * .5f, container.height * .5f};
    containerLocAdded = false;

    keyWhiteImage = LoadImage("../images/silver.png");
    keyWhiteTexture = LoadTextureFromImage(keyWhiteImage);
    UnloadImage(keyWhiteImage);
    keyWhiteRectangle = {container.x, container.y + (container.height * .125f), static_cast<float>(container.width * .125), static_cast<float>(container.height * .75)};
    keyWhiteCenter = {static_cast<float>(keyWhiteRectangle.width * .5f), static_cast<float>(keyWhiteRectangle.height * .5f)};

    keyBlackImage = LoadImage("../images/fret.png");
    keyBlackTexture = LoadTextureFromImage(keyBlackImage);
    UnloadImage(keyBlackImage);
    keyBlackRectangle = {container.x, container.y + (container.height * .125f), static_cast<float>(keyWhiteRectangle.width * .6), static_cast<float>(keyWhiteRectangle.height * .6)};
    keyBlackCenter = {static_cast<float>(keyBlackRectangle.width * .5f), static_cast<float>(keyBlackRectangle.height * .5f)};

    /** Connection Point **/
    connectImage = LoadImage("../images/fret.png");
    connectTexture = LoadTextureFromImage(connectImage);
    UnloadImage(connectImage);
    connectRectangle = {container.x  - (container.width * .55f), container.y, static_cast<float>(container.width * .02f), static_cast<float>(container.width * .02f)};
    connectCenter = {static_cast<float>(connectRectangle.width * .5f), static_cast<float>(connectRectangle.height )};

    /** Colors **/
    hoverColor = RED;
    rootColor = WHITE;
    secondColor = MAROON;
    thirdColor = GREEN;
    fourthColor = YELLOW;
    fifthColor = PURPLE;
    whiteKeyColor = WHITE;
    blackKeyColor = BLACK;
    whiteKeyHover = false;
    blackKeyHover = false;

    /** Vector Inits **/
    for (int i = 0; i < 100; i++) {      // TODO: Just filling to 100 for space right now
        keyWhiteColorVec.push_back(WHITE);
        keyBlackColorVec.push_back(BLACK);
        keyWhiteLocations.push_back({0, 0});
        keyBlackLocations.push_back({0, 0});
    }
    notesLocAdded = false;

    F = LoadSound("../resources/audio/CantinaBand3.wav");
    notesVec.push_back(F);
}

void Piano::draw(float windowScale) {

    /** Parent Container **/
    DrawTexturePro(containerTexture,
                   container,
                   (Rectangle) {container.x, container.y, container.width, container.height},  /** Params = (x-pos, y-pos, height, width) **/
                   containerCenter, 0, WHITE);

    // TODO: Not currently implementing connection points
//    /** Connection Point **/
//    DrawTexturePro(connectTexture,
//                   connectRectangle,
//                   (Rectangle) {connectRectangle.x, connectRectangle.y, connectRectangle.width, connectRectangle.height},
//                   connectCenter, 0, WHITE);

    /** White Keys **/
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .39f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[0]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .26f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[1]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .13f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[2]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[3]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .13f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[4]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .26f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[5]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .39f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[6]);
    // TODO: Always true for now
    if (!notesLocAdded) {
        keyWhiteLocations[0] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .39f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
        keyWhiteLocations[1] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .26f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
        keyWhiteLocations[2] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .13f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
        keyWhiteLocations[3] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
        keyWhiteLocations[4] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .13f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
        keyWhiteLocations[5] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .26f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
        keyWhiteLocations[6] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .39f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
    }

    /** Black Keys **/
    DrawRectangle(keyBlackRectangle.x - (container.width * .365f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[0]);
    DrawRectangle(keyBlackRectangle.x - (container.width * .235f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[1]);
    DrawRectangle(keyBlackRectangle.x + (keyWhiteRectangle.width * .2f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[2]);
    DrawRectangle(keyBlackRectangle.x + (container.width * .1575f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[3]);
    DrawRectangle(keyBlackRectangle.x + (container.width * .2875f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[4]);
    if (!notesLocAdded) {
        keyBlackLocations[0] = {keyBlackRectangle.x - (container.width * .365f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
        keyBlackLocations[1] = {keyBlackRectangle.x - (container.width * .235f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
        keyBlackLocations[2] = {keyBlackRectangle.x + (keyWhiteRectangle.width * .2f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
        keyBlackLocations[3] = {keyBlackRectangle.x + (container.width * .1575f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
        keyBlackLocations[4] = {keyBlackRectangle.x + (container.width * .2875f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
    }
//    notesLocAdded = true;  // TODO: Maybe put this in if statement above


}

// TODO: Makes this inherited from a based Instrument class
void Piano::hover(Vector2 mousePos) {
    // Black Keys
    for (int i = 0; i < keyBlackLocations.size(); i++) {
        if (mousePos.x > keyBlackLocations[i].x &&
            mousePos.x < keyBlackLocations[i].x + (keyBlackRectangle.width) &&
            mousePos.y > keyBlackLocations[i].y &&
            mousePos.y < keyBlackLocations[i].y + (keyBlackRectangle.height)) {
            keyBlackColorVec[i] = hoverColor;
            whiteKeyHover = false;
        }
        else {
            keyBlackColorVec[i] = blackKeyColor;
//            whiteKeyHover = true;
        }
    }

    // White Keys
    for (int i = 0; i < keyWhiteLocations.size(); i++) {
        if (whiteKeyHover) {
            if (mousePos.x > keyWhiteLocations[i].x &&
                mousePos.x < keyWhiteLocations[i].x + (keyWhiteRectangle.width) &&
                mousePos.y > keyWhiteLocations[i].y &&
                mousePos.y < keyWhiteLocations[i].y + (keyWhiteRectangle.height)) {
//                keyWhiteColorVec[i] = hoverColor;
                keyWhiteColorVec[i] = GREEN;
            }
            else {
                keyWhiteColorVec[i] = whiteKeyColor;
            }
        }
    }
}

// play sound
void Piano::playSound(Vector2 mousePos) {
    // Black Keys
    // check if left click

    for (int i = 0; i < keyBlackLocations.size(); i++) {
        if (mousePos.x > keyBlackLocations[i].x &&
            mousePos.x < keyBlackLocations[i].x + (keyBlackRectangle.width) &&
            mousePos.y > keyBlackLocations[i].y &&
            mousePos.y < keyBlackLocations[i].y + (keyBlackRectangle.height) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            std::cout << "Black Key Play sound" << i << " pressed" << std::endl;
        }
    }

    // White Keys
    for (int i = 0; i < keyWhiteLocations.size(); i++) {
        if (mousePos.x > keyWhiteLocations[i].x &&
            mousePos.x < keyWhiteLocations[i].x + (keyWhiteRectangle.width) &&
            mousePos.y > keyWhiteLocations[i].y &&
            mousePos.y < keyWhiteLocations[i].y + (keyWhiteRectangle.height) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            std::cout << "White Key Play sound" << i << " pressed" << std::endl;
            PlaySound(F);
        }
    }
}

bool Piano::connectionHover(Vector2 mousePos) {
    if (mousePos.x > connectRectangle.x - (connectRectangle.width * .5f) && mousePos.x < connectRectangle.x + (connectRectangle.width * .5f) &&
        mousePos.y > connectRectangle.y - (connectRectangle.height * .5f) && mousePos.y < connectRectangle.y + (connectRectangle.height * .5f)) {
        return true;
    }
    else {
        return false;
    }
}

void Piano::clickAndDrag(Vector2 mousePos) {
    if (mousePos.x > containerLoc.x - (container.width * .5f) && mousePos.x < containerLoc.x + (container.width * .5f) &&
        mousePos.y > containerLoc.y - (container.height * .5f) && mousePos.y < containerLoc.y + (container.height * .5f)) {
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            // TODO: Should only have to change the container?? Maybe since initial build is in constructor.
            container.x = mousePos.x;
            container.y = mousePos.y;
            connectRectangle.x = container.x - (container.width * .55f);
            connectRectangle.y = container.y;
            keyWhiteRectangle.x = container.x;
            keyWhiteRectangle.y = container.y + (container.height * .125f);
            keyBlackRectangle.x = container.x;
            keyBlackRectangle.y = container.y + (container.height * .125f);
            whiteKeyHover = false;
            blackKeyHover = false;
        }
        // TODO: Don't think I like this here
        else {
            whiteKeyHover = true;
            blackKeyHover = true;
        }
    }
    // Update the container location
    containerLoc = {container.x, container.y};
}

/** Getters **/
bool Piano::getCanDraw() {return canDraw;}
Rectangle Piano::getContainer() {return container;}
Rectangle Piano::getConnectionRec() {return connectRectangle;}
bool Piano::getCanDrawConnection() { return canDrawConnection;}
bool Piano::getStateActive() {return active;}

/** Setters **/
void Piano::setCanDraw(bool canDraw) {this->canDraw = canDraw;}
//void Piano::setConnectionRec(Rectangle connectRectangle) {this->connectRectangle = connectRectangle;}
void Piano::setCanDrawConnection(bool state) {this->canDrawConnection = state;}
void Piano::setStateActive(bool state) {this->active = state;}

/** Destruct **/
// TODO: Not sure which is best approach
void Piano::destroy() {UnloadTexture(containerTexture); UnloadSound(F);}


