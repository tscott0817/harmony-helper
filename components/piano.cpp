#include "piano.h"
#include <utility>
#include <algorithm>
#include <string>

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
    clickColor = GREEN;
    secondColor = MAROON;
    thirdColor = GREEN;
    fourthColor = YELLOW;
    fifthColor = PURPLE;
    whiteKeyColor = WHITE;
    blackKeyColor = BLACK;
    blackKeyClickColor = RED;
    whiteKeyHover = false;
    blackKeyHover = false;

    /** Vector Inits **/
    for (int i = 0; i < 100; i++) {      // TODO: Just filling to 100 for space right now
        keyWhiteColorVec.push_back(WHITE);
        keyBlackColorVec.push_back(BLACK);
        keyWhiteLocations.push_back({0, 0});
        keyBlackLocations.push_back({0, 0});
        noteClickedBoolVecWhite.push_back(0);
        noteClickedBoolVecBlack.push_back(0);
    }
    notesLocAdded = false;

    F = LoadSound("../resources/audio/CantinaBand3.wav");
//    soundNoteTest = LoadSound("../../resources/audio/key13.ogg");
    soundNoteTest = LoadSound("key13.ogg");
    notesVec.push_back(F);
    noteTextVec.emplace_back(keysWhite);
    noteTextVec.emplace_back(keysBlack);
}

void Piano::draw(float windowScale) {

    /** Parent Container **/
    DrawTexturePro(containerTexture,
                   container,
                   (Rectangle) {container.x, container.y, container.width, container.height},  /** Params = (x-pos, y-pos, height, width) **/
                   containerCenter, 0, WHITE);

    /** White Keys **/
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .39f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[0]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .26f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[1]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .13f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[2]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[3]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .13f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[4]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .26f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[5]);
    DrawRectangle(keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .39f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f), keyWhiteRectangle.width, keyWhiteRectangle.height, keyWhiteColorVec[6]);

    keyWhiteLocations[0] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .39f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
    keyWhiteLocations[1] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .26f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
    keyWhiteLocations[2] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) - (container.width * .13f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
    keyWhiteLocations[3] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
    keyWhiteLocations[4] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .13f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
    keyWhiteLocations[5] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .26f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};
    keyWhiteLocations[6] = {keyWhiteRectangle.x - (keyWhiteRectangle.width * .5f) + (container.width * .39f), keyWhiteRectangle.y - (keyWhiteRectangle.height * .5f)};

    /** Black Keys **/
    DrawRectangle(keyBlackRectangle.x - (container.width * .365f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[0]);
    DrawRectangle(keyBlackRectangle.x - (container.width * .235f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[1]);
    DrawRectangle(keyBlackRectangle.x + (keyWhiteRectangle.width * .2f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[2]);
    DrawRectangle(keyBlackRectangle.x + (container.width * .1575f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[3]);
    DrawRectangle(keyBlackRectangle.x + (container.width * .2875f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f), keyBlackRectangle.width, keyBlackRectangle.height, keyBlackColorVec[4]);

    keyBlackLocations[0] = {keyBlackRectangle.x - (container.width * .365f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
    keyBlackLocations[1] = {keyBlackRectangle.x - (container.width * .235f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
    keyBlackLocations[2] = {keyBlackRectangle.x + (keyWhiteRectangle.width * .2f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
    keyBlackLocations[3] = {keyBlackRectangle.x + (container.width * .1575f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};
    keyBlackLocations[4] = {keyBlackRectangle.x + (container.width * .2875f), keyBlackRectangle.y - (keyBlackRectangle.height * .85f)};

}

bool Piano::isHovering(Vector2 mousePos) {
    if (mousePos.x > containerLoc.x - (container.width * .5f) && mousePos.x < containerLoc.x + (container.width * .5f) &&
        mousePos.y > containerLoc.y - (container.height * .5f) && mousePos.y < containerLoc.y + (container.height * .5f)) {
        std::cout << "Hovering Piano" << std::endl;
        return true;
    }
    else {
        return false;
    }
}

void Piano::selectNote(Vector2 mousePos) {
    for (int i = 0; i < keyBlackLocations.size(); i++) {
        if (mousePos.x > keyBlackLocations[i].x &&
            mousePos.x < keyBlackLocations[i].x + (keyBlackRectangle.width) &&
            mousePos.y > keyBlackLocations[i].y &&
            mousePos.y < keyBlackLocations[i].y + (keyBlackRectangle.height) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && noteClickedBoolVecBlack[i] == 0) {
            std::cout << "Hovering Black" << std::endl;
            noteClickedBoolVecBlack[i] = 1;
            keyBlackColorVec[i] = blackKeyClickColor;
            addNoteShared(noteTextVec[1][i]); // TODO: [1][x] is for black keys, [0][x] is for white keys
            PlaySound(soundNoteTest);
        }
        else if (mousePos.x > keyBlackLocations[i].x &&
                 mousePos.x < keyBlackLocations[i].x + (keyBlackRectangle.width) &&
                 mousePos.y > keyBlackLocations[i].y &&
                 mousePos.y < keyBlackLocations[i].y + (keyBlackRectangle.height) &&
                 IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && noteClickedBoolVecBlack[i] == 1) {

            noteClickedBoolVecBlack[i] = 0;
            keyBlackColorVec[i] = blackKeyColor;
            removeNoteShared(noteTextVec[1][i]);
        }
    }
    if (!hoverBlackNotes(mousePos)) {
        for (int i = 0; i < keyWhiteLocations.size(); i++) {
            if (mousePos.x > keyWhiteLocations[i].x &&
                mousePos.x < keyWhiteLocations[i].x + (keyWhiteRectangle.width) &&
                mousePos.y > keyWhiteLocations[i].y &&
                mousePos.y < keyWhiteLocations[i].y + (keyWhiteRectangle.height) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && noteClickedBoolVecWhite[i] == 0) {
                PlaySound(soundNoteTest);
                noteClickedBoolVecWhite[i] = 1;
                keyWhiteColorVec[i] = clickColor;
                addNoteShared(noteTextVec[0][i]);  // TODO: [1][x] is for black keys, [0][x] is for white keys

            } else if (mousePos.x > keyWhiteLocations[i].x &&
                       mousePos.x < keyWhiteLocations[i].x + (keyWhiteRectangle.width) &&
                       mousePos.y > keyWhiteLocations[i].y &&
                       mousePos.y < keyWhiteLocations[i].y + (keyWhiteRectangle.height) &&
                       IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && noteClickedBoolVecWhite[i] == 1) {

                noteClickedBoolVecWhite[i] = 0;
                keyWhiteColorVec[i] = whiteKeyColor;
                removeNoteShared(noteTextVec[0][i]);
            }
        }
    }
}

bool Piano::hoverBlackNotes(Vector2 mousePos) {

    // TODO: Loop doesn't work?
//    for (auto & keyBlackLocation : keyBlackLocations) {
//        if (mousePos.x > keyBlackLocation.x &&
//            mousePos.x < keyBlackLocation.x + (keyBlackRectangle.width) &&
//            mousePos.y > keyBlackLocation.y &&
//            mousePos.y < keyBlackLocation.y + (keyBlackRectangle.height)) {
//            return true;
//        }
//        else {
//            return false;
//        }
//    }

    // Hardcode instead works well
    if (mousePos.x > keyBlackLocations[0].x &&
        mousePos.x < keyBlackLocations[0].x + (keyBlackRectangle.width) &&
        mousePos.y > keyBlackLocations[0].y &&
        mousePos.y < keyBlackLocations[0].y + (keyBlackRectangle.height)) {  // TODO: This error is probably caused not using loop, but loop doesn't work?
        return true;
    }
    else if (mousePos.x > keyBlackLocations[1].x &&
             mousePos.x < keyBlackLocations[1].x + (keyBlackRectangle.width) &&
             mousePos.y > keyBlackLocations[1].y &&
             mousePos.y < keyBlackLocations[1].y + (keyBlackRectangle.height)) {
        return true;
    }
    else if (mousePos.x > keyBlackLocations[2].x &&
             mousePos.x < keyBlackLocations[2].x + (keyBlackRectangle.width) &&
             mousePos.y > keyBlackLocations[2].y &&
             mousePos.y < keyBlackLocations[2].y + (keyBlackRectangle.height)) {
        return true;
    }
    else if (mousePos.x > keyBlackLocations[3].x &&
             mousePos.x < keyBlackLocations[3].x + (keyBlackRectangle.width) &&
             mousePos.y > keyBlackLocations[3].y &&
             mousePos.y < keyBlackLocations[3].y + (keyBlackRectangle.height)) {
        return true;
    }
    else if (mousePos.x > keyBlackLocations[4].x &&
             mousePos.x < keyBlackLocations[4].x + (keyBlackRectangle.width) &&
             mousePos.y > keyBlackLocations[4].y &&
             mousePos.y < keyBlackLocations[4].y + (keyBlackRectangle.height)) {
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
    containerLoc = {container.x, container.y};
}

void Piano::notesActivate() {
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "C") != sharedNotesVec.end()) {
        keyWhiteColorVec[0] = clickColor;
        noteClickedBoolVecWhite[0] = 1;
    }
    else {
        keyWhiteColorVec[0] = whiteKeyColor;
        noteClickedBoolVecWhite[0] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Db") != sharedNotesVec.end()) {
        keyBlackColorVec[0] = blackKeyClickColor;
        noteClickedBoolVecBlack[0] = 1;
    }
    else {
        keyBlackColorVec[0] = blackKeyColor;
        noteClickedBoolVecBlack[0] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "D") != sharedNotesVec.end()) {
        keyWhiteColorVec[1] = clickColor;
        noteClickedBoolVecWhite[1] = 1;
    }
    else {
        keyWhiteColorVec[1] = whiteKeyColor;
        noteClickedBoolVecWhite[1] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Eb") != sharedNotesVec.end()) {
        keyBlackColorVec[1] = blackKeyClickColor;
        noteClickedBoolVecBlack[1] = 1;
    }
    else {
        keyBlackColorVec[1] = blackKeyColor;
        noteClickedBoolVecBlack[1] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "E") != sharedNotesVec.end()) {
        keyWhiteColorVec[2] = clickColor;
        noteClickedBoolVecWhite[2] = 1;
    }
    else {
        keyWhiteColorVec[2] = whiteKeyColor;
        noteClickedBoolVecWhite[2] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "F") != sharedNotesVec.end()) {
        keyWhiteColorVec[3] = clickColor;
        noteClickedBoolVecWhite[3] = 1;
    }
    else {
        keyWhiteColorVec[3] = whiteKeyColor;
        noteClickedBoolVecWhite[3] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Gb") != sharedNotesVec.end()) {
        keyBlackColorVec[2] = blackKeyClickColor;
        noteClickedBoolVecBlack[2] = 1;
    }
    else {
        keyBlackColorVec[2] = blackKeyColor;
        noteClickedBoolVecBlack[2] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "G") != sharedNotesVec.end()) {
        keyWhiteColorVec[4] = clickColor;
        noteClickedBoolVecWhite[4] = 1;
    }
    else {
        keyWhiteColorVec[4] = whiteKeyColor;
        noteClickedBoolVecWhite[4] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Ab") != sharedNotesVec.end()) {
        keyBlackColorVec[3] = blackKeyClickColor;
        noteClickedBoolVecBlack[3] = 1;
    }
    else {
        keyBlackColorVec[3] = blackKeyColor;
        noteClickedBoolVecBlack[3] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "A") != sharedNotesVec.end()) {
        keyWhiteColorVec[5] = clickColor;
        noteClickedBoolVecWhite[5] = 1;
    }
    else {
        keyWhiteColorVec[5] = whiteKeyColor;
        noteClickedBoolVecWhite[5] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Bb") != sharedNotesVec.end()) {
        keyBlackColorVec[4] = blackKeyClickColor;
        noteClickedBoolVecBlack[4] = 1;
    }
    else {
        keyBlackColorVec[4] = blackKeyColor;
        noteClickedBoolVecBlack[4] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "B") != sharedNotesVec.end()) {
        keyWhiteColorVec[6] = clickColor;
        noteClickedBoolVecWhite[6] = 1;
    }
    else {
        keyWhiteColorVec[6] = whiteKeyColor;
        noteClickedBoolVecWhite[6] = 0;
    }
}

/** Getters **/
bool Piano::getCanDraw() {return canDraw;}

/** Setters **/
void Piano::setCanDraw(bool canDraw) {this->canDraw = canDraw;}

/** Destruct **/
// TODO: Not sure if this is best approach
void Piano::destroy() {UnloadTexture(containerTexture); UnloadSound(F);}



