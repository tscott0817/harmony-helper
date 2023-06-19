#include "cmath"
#include "guitar.h"
#include <utility>
#include <algorithm>
#include <string>

Guitar::Guitar(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    /** Window Init **/
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    /** State Managing **/
    canDraw = false;

    /** Parent Container **/
    containerImage = LoadImage("../images/blue_background.png");     // Loaded in CPU memory (RAM)
    containerTexture = LoadTextureFromImage(containerImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(containerImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
    container = {static_cast<float>(this->screenWidth * posX), static_cast<float>(this->screenHeight * posY), static_cast<float>(this->screenWidth * width), static_cast<float>(this->screenHeight * height)};
    containerCenter = {container.width * .5f, container.height * .5f};
    containerLocAdded = false;

    /** Neck **/
    neckImage = LoadImage("../images/wood_dark.png");
    neckTexture = LoadTextureFromImage(neckImage);
    UnloadImage(neckImage);
    // neckRectangle = {container.x + (container.width * .03f), container.y, container.width * .94f, container.height * .9f}; // TODO: Fill container with neck (Currently have padding for testing)
    neckRectangle = {container.x, container.y, container.width, container.height * .9f}; // TODO: Fill container with neck (Currently have padding for testing)
    neckCenter = {static_cast<float>(neckRectangle.width * .5f), static_cast<float>(neckRectangle.height * .5f)};

    /** Frets **/
    fretImage = LoadImage("../images/fret.png");
    fretTexture = LoadTextureFromImage(fretImage);
    UnloadImage(fretImage);
    fretRectangle = {neckRectangle.x, neckRectangle.y, static_cast<float>(neckRectangle.width * .01), neckRectangle.height};
    fretCenter = {static_cast<float>(fretRectangle.width * .5f), static_cast<float>(fretRectangle.height * .5f)};

    /** Strings **/
    stringImage = LoadImage("../images/silver.png");
    stringTexture = LoadTextureFromImage(stringImage);
    UnloadImage(stringImage);
    stringRectangle = {neckRectangle.x, neckRectangle.y, neckRectangle.width, neckRectangle.height * .02f};
    stringCenter = {static_cast<float>(stringRectangle.width * .5f), static_cast<float>(stringRectangle.height * .5f)};
    // Fill stringVec with each const char
    noteTextVec.emplace_back(lowE);
    noteTextVec.emplace_back(a);
    noteTextVec.emplace_back(d);
    noteTextVec.emplace_back(g);
    noteTextVec.emplace_back(b);
    noteTextVec.emplace_back(highE);

    /** Note Containers **/
    noteRectangle = {neckRectangle.x, neckRectangle.y, neckRectangle.width * .05f, neckRectangle.height * .15f};
    notesLocAdded = false;

    /** Text and Font **/
    testFont = LoadFontEx("../resources/fonts/OpenSans-Light.ttf", 200, nullptr, 100);
    fontSize = (float)testFont.baseSize;
    fontPosition = { 500.0f, 1200.0f};
    textSize = { 10.0f, 10.0f };

    // Generate mipmap levels to use trilinear filtering
    GenTextureMipmaps(&testFont.texture);
    SetTextureFilter(testFont.texture, TEXTURE_FILTER_TRILINEAR);

    /** Vector Inits **/
    for (int i = 0; i < 100; i++) {      // TODO: Just filling to 100 for space right now
        std::vector<Vector2> tempLoc;
        std::vector<Color> tempColor;
        std::vector<int> tempClicked;
        for (int j = 0; j < 100; j++) {
            // TODO: Replace all with emplace_back
            tempLoc.emplace_back(Vector2{0, 0});  // With emplace_back, need to specify type
            tempColor.push_back(rootColor);
            tempClicked.push_back(0);
        }
        noteLocations.push_back(tempLoc);
        noteColorVec.push_back(tempColor);
        noteClickedBoolVec.push_back(tempClicked);
    }

    // TODO: The filepath will not play sound, but is same the above font filepath, so it should?
//    testSound = LoadSound("C:/Users/tyler/Dev/guitar-app/resources/audio/key13.ogg");
    testSound = LoadSound("../resources/audio/key13.ogg");


    containerColor = Color{51, 51, 51, 255};
}

void Guitar::draw(float windowScale) {

    /** Container **/
    DrawRectangle(static_cast<int>(container.x - (container.width * .5f)), static_cast<int>(container.y - (container.height * .5f)), static_cast<int>(container.width), static_cast<int>(container.height), containerColor);
    containerLoc = {container.x, container.y};  // TODO: Not sure if needed; Maybe want to update location only when container is moved, not every frame

    /** Neck **/
    DrawRectangle(static_cast<int>(neckRectangle.x - (neckRectangle.width * .5f)), static_cast<int>(neckRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(neckRectangle.width), static_cast<int>(neckRectangle.height), BROWN);

    /** Frets **/
    // Frets separated by 1/8 width of neck, built from a central point outward
    DrawRectangle(static_cast<int>(fretRectangle.x - (neckRectangle.width * .49)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x - (neckRectangle.width * .41)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x - (neckRectangle.width * .33)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x - (neckRectangle.width * .25)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x - (neckRectangle.width * .17)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x - (neckRectangle.width * .09)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x - (neckRectangle.width * .01)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x + (neckRectangle.width * .07)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x + (neckRectangle.width * .15)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x + (neckRectangle.width * .23)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x + (neckRectangle.width * .31)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x + (neckRectangle.width * .39)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);
    DrawRectangle(static_cast<int>(fretRectangle.x + (neckRectangle.width * .47)), static_cast<int>(fretRectangle.y - (neckRectangle.height * .5f)), static_cast<int>(fretRectangle.width), static_cast<int>(fretRectangle.height), GRAY);

    /** Strings **/
    // String are 1/6 the height of the neck, built from the center of the neck
    DrawRectangle(static_cast<int>(stringRectangle.x - (stringRectangle.width * .5f)), static_cast<int>(stringRectangle.y - (neckRectangle.height * .40)), static_cast<int>(stringRectangle.width), static_cast<int>(stringRectangle.height), RED);
    DrawRectangle(static_cast<int>(stringRectangle.x - (stringRectangle.width * .5f)), static_cast<int>(stringRectangle.y - (neckRectangle.height * .24)), static_cast<int>(stringRectangle.width), static_cast<int>(stringRectangle.height), RED);
    DrawRectangle(static_cast<int>(stringRectangle.x - (stringRectangle.width * .5f)), static_cast<int>(stringRectangle.y - (neckRectangle.height * .08)), static_cast<int>(stringRectangle.width), static_cast<int>(stringRectangle.height), RED);
    DrawRectangle(static_cast<int>(stringRectangle.x - (stringRectangle.width * .5f)), static_cast<int>(stringRectangle.y + (neckRectangle.height * .08)), static_cast<int>(stringRectangle.width), static_cast<int>(stringRectangle.height), RED);
    DrawRectangle(static_cast<int>(stringRectangle.x - (stringRectangle.width * .5f)), static_cast<int>(stringRectangle.y + (neckRectangle.height * .24)), static_cast<int>(stringRectangle.width), static_cast<int>(stringRectangle.height), RED);
    DrawRectangle(static_cast<int>(stringRectangle.x - (stringRectangle.width * .5f)), static_cast<int>(stringRectangle.y + (neckRectangle.height * .40)), static_cast<int>(stringRectangle.width), static_cast<int>(stringRectangle.height), RED);

    /** Notes **/
    // TODO: The whole design of the notes
    for (int i = 0; i < 13; i++) {  // Rows
        for (int j = 0; j < 6; j++) {  // Columns
            if (noteClickedBoolVec[i][j] == 1) {
                PlaySound(testSound);
                DrawEllipse(static_cast<float>(neckRectangle.x - (neckRectangle.width * .53f) + ((neckRectangle.width * .08) * i)), static_cast<float>((neckRectangle.y) - ((neckRectangle.height * .16) * j) + (neckRectangle.height * .4f)), static_cast<float>(noteRectangle.width / 2), static_cast<float>(noteRectangle.height / 2), noteColorVec[i][j]);

                float noteTextSize = (noteRectangle.width > noteRectangle.height) ? static_cast<float>(noteRectangle.height) : static_cast<float>(noteRectangle.width);
                Vector2 noteTextLoc = {static_cast<float>(neckRectangle.x - (neckRectangle.width * .53f) + ((neckRectangle.width * .08) * i) - (noteRectangle.width / 3)), static_cast<float>((neckRectangle.y) - ((neckRectangle.height * .16) * j) + (neckRectangle.height * .4f) - (noteRectangle.height / 2))};
                DrawTextEx(testFont, noteTextVec[j][i], noteTextLoc, noteTextSize, 0, WHITE);
            }
            else {
                DrawEllipseLines(static_cast<float>(neckRectangle.x - (neckRectangle.width * .53f) + ((neckRectangle.width * .08) * i)), static_cast<float>((neckRectangle.y) - ((neckRectangle.height * .16) * j) + (neckRectangle.height * .4f)), static_cast<float>(noteRectangle.width / 2), static_cast<float>(noteRectangle.height / 2), GREEN);
            }
            noteLocations[i][j] = {static_cast<float>(neckRectangle.x - (neckRectangle.width * .53f) + ((neckRectangle.width * .08) * i) - (noteRectangle.width / 2)), static_cast<float>((neckRectangle.y) - ((neckRectangle.height * .16) * j) + (neckRectangle.height * .4f) - (noteRectangle.height / 2))};
        }
    }
}

void Guitar::selectNote(Vector2 mousePos) {
    for (int i = 0; i < noteLocations.size(); i++) {
        for (int j = 0; j < noteLocations[i].size(); j++) {
            if (mousePos.x > noteLocations[i][j].x &&
                mousePos.x < noteLocations[i][j].x + (noteRectangle.width) &&
                mousePos.y > noteLocations[i][j].y &&
                mousePos.y < noteLocations[i][j].y + (noteRectangle.height) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && noteClickedBoolVec[i][j] == 0) {

                noteClickedBoolVec[i][j] = 1;
                addNoteShared(noteTextVec[j][i]);
            }
            else if (mousePos.x > noteLocations[i][j].x &&
                     mousePos.x < noteLocations[i][j].x + (noteRectangle.width) &&
                     mousePos.y > noteLocations[i][j].y &&
                     mousePos.y < noteLocations[i][j].y + (noteRectangle.height) &&
                     IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && noteClickedBoolVec[i][j] == 1) {

                noteClickedBoolVec[i][j] = 0;
                removeNoteShared(noteTextVec[j][i]);
            }
        }
    }
}

// TODO: There has to be a way to avoid hard coding everything
void Guitar::notesActivate() {
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "C") != sharedNotesVec.end()) {
        noteColorVec[1][4] = cNoteColor;
        noteColorVec[3][1] = cNoteColor;
        noteColorVec[5][3] = cNoteColor;
        noteColorVec[8][0] = cNoteColor;
        noteColorVec[8][5] = cNoteColor;
        noteColorVec[10][2] = cNoteColor;


        noteClickedBoolVec[1][4] = 1;
        noteClickedBoolVec[3][1] = 1;
        noteClickedBoolVec[5][3] = 1;
        noteClickedBoolVec[8][0] = 1;
        noteClickedBoolVec[8][5] = 1;
        noteClickedBoolVec[10][2] = 1;

    }
    else {
        noteColorVec[1][4] = rootColor;
        noteColorVec[3][1] = rootColor;
        noteColorVec[5][3] = rootColor;
        noteColorVec[8][0] = rootColor;
        noteColorVec[8][5] = rootColor;
        noteColorVec[10][2] = rootColor;

        noteClickedBoolVec[1][4] = 0;
        noteClickedBoolVec[3][1] = 0;
        noteClickedBoolVec[5][3] = 0;
        noteClickedBoolVec[8][0] = 0;
        noteClickedBoolVec[8][5] = 0;
        noteClickedBoolVec[10][2] = 0;

    }

    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Db") != sharedNotesVec.end()) {

        noteColorVec[2][4] = dbNoteColor;
        noteColorVec[4][1] = dbNoteColor;
        noteColorVec[6][3] = dbNoteColor;
        noteColorVec[9][0] = dbNoteColor;
        noteColorVec[9][5] = dbNoteColor;
        noteColorVec[11][2] = dbNoteColor;

        noteClickedBoolVec[2][4] = 1;
        noteClickedBoolVec[4][1] = 1;
        noteClickedBoolVec[6][3] = 1;
        noteClickedBoolVec[9][0] = 1;
        noteClickedBoolVec[9][5] = 1;
        noteClickedBoolVec[11][2] = 1;

    }
    else {
        noteColorVec[2][4] = rootColor;
        noteColorVec[4][1] = rootColor;
        noteColorVec[6][3] = rootColor;
        noteColorVec[9][0] = rootColor;
        noteColorVec[9][5] = rootColor;
        noteColorVec[11][2] = rootColor;

        noteClickedBoolVec[2][4] = 0;
        noteClickedBoolVec[4][1] = 0;
        noteClickedBoolVec[6][3] = 0;
        noteClickedBoolVec[9][0] = 0;
        noteClickedBoolVec[9][5] = 0;
        noteClickedBoolVec[11][2] = 0;
    }

    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "D") != sharedNotesVec.end()) {

        noteColorVec[0][2] = dNoteColor;
        noteColorVec[3][4] = dNoteColor;
        noteColorVec[5][1] = dNoteColor;
        noteColorVec[7][3] = dNoteColor;
        noteColorVec[10][0] = dNoteColor;
        noteColorVec[10][5] = dNoteColor;
        noteColorVec[12][2] = dNoteColor;

        noteClickedBoolVec[0][2] = 1;
        noteClickedBoolVec[3][4] = 1;
        noteClickedBoolVec[5][1] = 1;
        noteClickedBoolVec[7][3] = 1;
        noteClickedBoolVec[10][0] = 1;
        noteClickedBoolVec[10][5] = 1;
        noteClickedBoolVec[12][2] = 1;

    }
    else {
        noteColorVec[0][2] = rootColor;
        noteColorVec[3][4] = rootColor;
        noteColorVec[5][1] = rootColor;
        noteColorVec[7][3] = rootColor;
        noteColorVec[10][0] = rootColor;
        noteColorVec[10][5] = rootColor;
        noteColorVec[12][2] = rootColor;

        noteClickedBoolVec[0][2] = 0;
        noteClickedBoolVec[3][4] = 0;
        noteClickedBoolVec[5][1] = 0;
        noteClickedBoolVec[7][3] = 0;
        noteClickedBoolVec[10][0] = 0;
        noteClickedBoolVec[10][5] = 0;
        noteClickedBoolVec[12][2] = 0;

    }

    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Eb") != sharedNotesVec.end()) {

        noteColorVec[1][2] = ebNoteColor;
        noteColorVec[4][4] = ebNoteColor;
        noteColorVec[6][1] = ebNoteColor;
        noteColorVec[8][3] = ebNoteColor;
        noteColorVec[11][5] = ebNoteColor;
        noteColorVec[11][0] = ebNoteColor;

        noteClickedBoolVec[1][2] = 1;
        noteClickedBoolVec[4][4] = 1;
        noteClickedBoolVec[6][1] = 1;
        noteClickedBoolVec[8][3] = 1;
        noteClickedBoolVec[11][5] = 1;
        noteClickedBoolVec[11][0] = 1;

    }
    else {
        noteColorVec[1][2] = rootColor;
        noteColorVec[4][4] = rootColor;
        noteColorVec[6][1] = rootColor;
        noteColorVec[8][3] = rootColor;
        noteColorVec[11][5] = rootColor;
        noteColorVec[11][0] = rootColor;

        noteClickedBoolVec[1][2] = 0;
        noteClickedBoolVec[4][4] = 0;
        noteClickedBoolVec[6][1] = 0;
        noteClickedBoolVec[8][3] = 0;
        noteClickedBoolVec[11][5] = 0;
        noteClickedBoolVec[11][0] = 0;
    }

    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "E") != sharedNotesVec.end()) {

        noteColorVec[0][0] = eNoteColor;
        noteColorVec[0][5] = eNoteColor;
        noteColorVec[2][2] = eNoteColor;
        noteColorVec[5][4] = eNoteColor;
        noteColorVec[7][1] = eNoteColor;
        noteColorVec[9][3] = eNoteColor;
        noteColorVec[12][5] = eNoteColor;
        noteColorVec[12][0] = eNoteColor;

        noteClickedBoolVec[0][0] = 1;
        noteClickedBoolVec[0][5] = 1;
        noteClickedBoolVec[2][2] = 1;
        noteClickedBoolVec[5][4] = 1;
        noteClickedBoolVec[7][1] = 1;
        noteClickedBoolVec[9][3] = 1;
        noteClickedBoolVec[12][5] = 1;
        noteClickedBoolVec[12][0] = 1;

    }
    else {
        noteColorVec[0][0] = rootColor;
        noteColorVec[0][5] = rootColor;
        noteColorVec[2][2] = rootColor;
        noteColorVec[5][4] = rootColor;
        noteColorVec[7][1] = rootColor;
        noteColorVec[9][3] = rootColor;
        noteColorVec[12][5] = rootColor;
        noteColorVec[12][0] = rootColor;

        noteClickedBoolVec[0][0] = 0;
        noteClickedBoolVec[0][5] = 0;
        noteClickedBoolVec[2][2] = 0;
        noteClickedBoolVec[5][4] = 0;
        noteClickedBoolVec[7][1] = 0;
        noteClickedBoolVec[9][3] = 0;
        noteClickedBoolVec[12][5] = 0;
        noteClickedBoolVec[12][0] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "F") != sharedNotesVec.end()) {

        noteColorVec[1][0] = fNoteColor;
        noteColorVec[1][5] = fNoteColor;
        noteColorVec[3][2] = fNoteColor;
        noteColorVec[6][4] = fNoteColor;
        noteColorVec[8][1] = fNoteColor;
        noteColorVec[10][3] = fNoteColor;

        noteClickedBoolVec[1][0] = 1;
        noteClickedBoolVec[1][5] = 1;
        noteClickedBoolVec[3][2] = 1;
        noteClickedBoolVec[6][4] = 1;
        noteClickedBoolVec[8][1] = 1;
        noteClickedBoolVec[10][3] = 1;
    }
    else {
        noteColorVec[1][0] = rootColor;
        noteColorVec[1][5] = rootColor;
        noteColorVec[3][2] = rootColor;
        noteColorVec[6][4] = rootColor;
        noteColorVec[8][1] = rootColor;
        noteColorVec[10][3] = rootColor;

        noteClickedBoolVec[1][0] = 0;
        noteClickedBoolVec[1][5] = 0;
        noteClickedBoolVec[3][2] = 0;
        noteClickedBoolVec[6][4] = 0;
        noteClickedBoolVec[8][1] = 0;
        noteClickedBoolVec[10][3] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Gb") != sharedNotesVec.end()) {

        noteColorVec[2][0] = gbNoteColor;
        noteColorVec[2][5] = gbNoteColor;
        noteColorVec[4][2] = gbNoteColor;
        noteColorVec[7][4] = gbNoteColor;
        noteColorVec[9][1] = gbNoteColor;
        noteColorVec[11][3] = gbNoteColor;

        noteClickedBoolVec[2][0] = 1;
        noteClickedBoolVec[2][5] = 1;
        noteClickedBoolVec[4][2] = 1;
        noteClickedBoolVec[7][4] = 1;
        noteClickedBoolVec[9][1] = 1;
        noteClickedBoolVec[11][3] = 1;

    }
    else {
        noteColorVec[2][0] = rootColor;
        noteColorVec[2][5] = rootColor;
        noteColorVec[4][2] = rootColor;
        noteColorVec[7][4] = rootColor;
        noteColorVec[9][1] = rootColor;
        noteColorVec[11][3] = rootColor;

        noteClickedBoolVec[2][0] = 0;
        noteClickedBoolVec[2][5] = 0;
        noteClickedBoolVec[4][2] = 0;
        noteClickedBoolVec[7][4] = 0;
        noteClickedBoolVec[9][1] = 0;
        noteClickedBoolVec[11][3] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "G") != sharedNotesVec.end()) {

        noteColorVec[0][3] = gNoteColor;
        noteColorVec[3][0] = gNoteColor;
        noteColorVec[3][5] = gNoteColor;
        noteColorVec[5][2] = gNoteColor;
        noteColorVec[8][4] = gNoteColor;
        noteColorVec[10][1] = gNoteColor;
        noteColorVec[12][3] = gNoteColor;

        noteClickedBoolVec[0][3] = 1;
        noteClickedBoolVec[3][0] = 1;
        noteClickedBoolVec[3][5] = 1;
        noteClickedBoolVec[5][2] = 1;
        noteClickedBoolVec[8][4] = 1;
        noteClickedBoolVec[10][1] = 1;
        noteClickedBoolVec[12][3] = 1;
    }
    else {
        noteColorVec[0][3] = rootColor;
        noteColorVec[3][0] = rootColor;
        noteColorVec[3][5] = rootColor;
        noteColorVec[5][2] = rootColor;
        noteColorVec[8][4] = rootColor;
        noteColorVec[10][1] = rootColor;
        noteColorVec[12][3] = rootColor;

        noteClickedBoolVec[0][3] = 0;
        noteClickedBoolVec[3][0] = 0;
        noteClickedBoolVec[3][5] = 0;
        noteClickedBoolVec[5][2] = 0;
        noteClickedBoolVec[8][4] = 0;
        noteClickedBoolVec[10][1] = 0;
        noteClickedBoolVec[12][3] = 0;

    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Ab") != sharedNotesVec.end()) {

        noteColorVec[1][3] = abNoteColor;
        noteColorVec[4][5] = abNoteColor;
        noteColorVec[4][0] = abNoteColor;
        noteColorVec[6][2] = abNoteColor;
        noteColorVec[9][4] = abNoteColor;
        noteColorVec[11][1] = abNoteColor;

        noteClickedBoolVec[1][3] = 1;
        noteClickedBoolVec[4][5] = 1;
        noteClickedBoolVec[4][0] = 1;
        noteClickedBoolVec[6][2] = 1;
        noteClickedBoolVec[9][4] = 1;
        noteClickedBoolVec[11][1] = 1;

    }
    else {
        noteColorVec[1][3] = rootColor;
        noteColorVec[4][5] = rootColor;
        noteColorVec[4][0] = rootColor;
        noteColorVec[6][2] = rootColor;
        noteColorVec[9][4] = rootColor;
        noteColorVec[11][1] = rootColor;

        noteClickedBoolVec[1][3] = 0;
        noteClickedBoolVec[4][5] = 0;
        noteClickedBoolVec[4][0] = 0;
        noteClickedBoolVec[6][2] = 0;
        noteClickedBoolVec[9][4] = 0;
        noteClickedBoolVec[11][1] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "A") != sharedNotesVec.end()) {

        noteColorVec[0][1] = aNoteColor;
        noteColorVec[2][3] = aNoteColor;
        noteColorVec[5][5] = aNoteColor;
        noteColorVec[5][0] = aNoteColor;
        noteColorVec[7][2] = aNoteColor;
        noteColorVec[10][4] = aNoteColor;
        noteColorVec[12][1] = aNoteColor;

        noteClickedBoolVec[0][1] = 1;
        noteClickedBoolVec[2][3] = 1;
        noteClickedBoolVec[5][5] = 1;
        noteClickedBoolVec[5][0] = 1;
        noteClickedBoolVec[7][2] = 1;
        noteClickedBoolVec[10][4] = 1;
        noteClickedBoolVec[12][1] = 1;
    }
    else {
        noteColorVec[0][1] = rootColor;
        noteColorVec[2][3] = rootColor;
        noteColorVec[5][5] = rootColor;
        noteColorVec[5][0] = rootColor;
        noteColorVec[7][2] = rootColor;
        noteColorVec[10][4] = rootColor;
        noteColorVec[12][1] = rootColor;

        noteClickedBoolVec[0][1] = 0;
        noteClickedBoolVec[2][3] = 0;
        noteClickedBoolVec[5][5] = 0;
        noteClickedBoolVec[5][0] = 0;
        noteClickedBoolVec[7][2] = 0;
        noteClickedBoolVec[10][4] = 0;
        noteClickedBoolVec[12][1] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "Bb") != sharedNotesVec.end()) {

        noteColorVec[1][1] = bbNoteColor;
        noteColorVec[3][3] = bbNoteColor;
        noteColorVec[6][5] = bbNoteColor;
        noteColorVec[6][0] = bbNoteColor;
        noteColorVec[8][2] = bbNoteColor;
        noteColorVec[11][4] = bbNoteColor;

        noteClickedBoolVec[1][1] = 1;
        noteClickedBoolVec[3][3] = 1;
        noteClickedBoolVec[6][5] = 1;
        noteClickedBoolVec[6][0] = 1;
        noteClickedBoolVec[8][2] = 1;
        noteClickedBoolVec[11][4] = 1;

    }
    else {
        noteColorVec[1][1] = rootColor;
        noteColorVec[3][3] = rootColor;
        noteColorVec[6][5] = rootColor;
        noteColorVec[6][0] = rootColor;
        noteColorVec[8][2] = rootColor;
        noteColorVec[11][6] = rootColor;

        noteClickedBoolVec[1][1] = 0;
        noteClickedBoolVec[3][3] = 0;
        noteClickedBoolVec[6][5] = 0;
        noteClickedBoolVec[6][0] = 0;
        noteClickedBoolVec[8][2] = 0;
        noteClickedBoolVec[11][4] = 0;
    }
    if (std::find(sharedNotesVec.begin(), sharedNotesVec.end(), "B") != sharedNotesVec.end()) {

        noteColorVec[0][4] = bNoteColor;
        noteColorVec[2][1] = bNoteColor;
        noteColorVec[4][3] = bNoteColor;
        noteColorVec[7][0] = bNoteColor;
        noteColorVec[7][5] = bNoteColor;
        noteColorVec[9][2] = bNoteColor;
        noteColorVec[12][4] = bNoteColor;

        noteClickedBoolVec[0][4] = 1;
        noteClickedBoolVec[2][1] = 1;
        noteClickedBoolVec[4][3] = 1;
        noteClickedBoolVec[7][0] = 1;
        noteClickedBoolVec[7][5] = 1;
        noteClickedBoolVec[9][2] = 1;
        noteClickedBoolVec[12][4] = 1;
    }
    else {
        noteColorVec[0][4] = rootColor;
        noteColorVec[2][1] = rootColor;
        noteColorVec[4][3] = rootColor;
        noteColorVec[7][0] = rootColor;
        noteColorVec[7][5] = rootColor;
        noteColorVec[9][2] = rootColor;
        noteColorVec[12][4] = rootColor;

        noteClickedBoolVec[0][4] = 0;
        noteClickedBoolVec[2][1] = 0;
        noteClickedBoolVec[4][3] = 0;
        noteClickedBoolVec[7][0] = 0;
        noteClickedBoolVec[7][5] = 0;
        noteClickedBoolVec[9][2] = 0;
        noteClickedBoolVec[12][4] = 0;
    }
}

void Guitar::clickAndDrag(Vector2 mousePos) {
    if (mousePos.x > containerLoc.x - (container.width * .5f) && mousePos.x < containerLoc.x + (container.width * .5f) &&
        mousePos.y > containerLoc.y - (container.height * .5f) && mousePos.y < containerLoc.y + (container.height * .5f)) {
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            container.x = mousePos.x;
            container.y = mousePos.y;
            // TODO: Not sure why these have to be different?
            connectRectangle.x = container.x;
            connectRectangle.y = container.y - (container.height * .55f);
            neckRectangle.x = mousePos.x;
            neckRectangle.y = mousePos.y;
            fretRectangle.x = mousePos.x;
            fretRectangle.y = mousePos.y;
            stringRectangle.x = mousePos.x;
            stringRectangle.y = mousePos.y;
            noteRectangle.x = mousePos.x;
            noteRectangle.y = mousePos.y;
        }
    }
    containerLoc = {container.x, container.y};
}

/** Getter **/
bool Guitar::getCanDraw() { return canDraw; }

/** Setters **/
void Guitar::setCanDraw(bool state) { canDraw = state; }

// To remove textures from memory after program closes, must be after main loop ends
void Guitar::destroy() {
    UnloadTexture(containerTexture);
    UnloadTexture(neckTexture);
    UnloadTexture(fretTexture);
    UnloadTexture(stringTexture);
    UnloadSound(testSound);
}
