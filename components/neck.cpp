#include "cmath"
#include "neck.h"

Neck::Neck(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {

    /** State Managing **/
    stateActive = false;  // TODO: May use to 'pause'
    canDraw = false;

    /** The parent container **/
    containerImage = LoadImage("../images/blue_background.png");     // Loaded in CPU memory (RAM)
    containerTexture = LoadTextureFromImage(containerImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(containerImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    // Only change the position and size of neckContainer (Make this the params the user can change, drop down menu)
    container = {posX, posY, static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height

    containerCenter = {container.width / 2, container.height / 2};
    containerLocAdded = false;

    /** Neck **/
    neckImage = LoadImage("../images/wood_dark.png");     // Loaded in CPU memory (RAM)
    neckTexture = LoadTextureFromImage(neckImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(neckImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    // Use the container position +/- some integer to move child objects
    // Use the size of the container * some float to resize child object
    neckRectangle = {container.x, container.y, container.width, container.height * .9f}; // TODO: Fill container with neck (Currently have padding for testing)
    neckCenter = {static_cast<float>(neckRectangle.width / 2), static_cast<float>(neckRectangle.height / 2)};

    /** Frets **/
    fretImage = LoadImage("../images/fret.png");
    fretTexture = LoadTextureFromImage(fretImage);
    UnloadImage(fretImage);
    fretRectangle = {neckRectangle.x, neckRectangle.y, static_cast<float>(neckRectangle.width * .01), neckRectangle.height};
    fretCenter = {static_cast<float>(fretRectangle.width / 2), static_cast<float>(fretRectangle.height / 2)};

    /** Strings **/
    stringImage = LoadImage("../images/silver.png");
    stringTexture = LoadTextureFromImage(stringImage);
    UnloadImage(stringImage);

    stringRectangle = {neckRectangle.x, neckRectangle.y, neckRectangle.width, neckRectangle.height * .02f};
    stringCenter = {static_cast<float>(stringRectangle.width / 2), static_cast<float>(stringRectangle.height / 2)};

    /** Note Containers **/
    // Create a rectangle for the note containers
    noteRectangle = {neckRectangle.x, neckRectangle.y, neckRectangle.width * .05f, neckRectangle.height * .15f};
    // noteCenter = {static_cast<float>(noteRectangle.width / 2), static_cast<float>(noteRectangle.height / 2)};

    notesLocAdded = false;
    testText = "Test Text";
    noteName = "X";
    testFont = LoadFontEx("../resources/OpenSans-Light.ttf", 200, nullptr, 100);

    // Generate mipmap levels to use trilinear filtering
    // NOTE: On 2D drawing it won't be noticeable, it looks like FILTER_BILINEAR
    GenTextureMipmaps(&testFont.texture);
    fontSize = (float)testFont.baseSize;
    fontPosition = { 500.0f, 1200.0f};
    textSize = { 10.0f, 10.0f };

    // Setup texture scaling filter
    SetTextureFilter(testFont.texture, TEXTURE_FILTER_TRILINEAR);

    // Colors
    hoverColor = Color{190, 33, 55, 200};
    rootColor = Color{0, 121, 241, 200};
    secondColor = MAROON;
    thirdColor = GREEN;
    fourthColor = YELLOW;
    fifthColor = PURPLE;

    // TODO: Just filling to 100 for room, but don't want to hardcode this 100
    for (int i = 0; i < 100; i++) {
        std::vector<Vector2> tempLoc;
        std::vector<Color> tempColor;
        for (int j = 0; j < 100; j++) {
            tempLoc.push_back({0, 0});
            tempColor.push_back(rootColor);
        }
        noteLocations.push_back(tempLoc);
        noteColorVec.push_back(tempColor);
    }
}

int Neck::drawGuitarNeck(float windowScale) {

    /** Container **/
    DrawTexturePro(containerTexture,
                   container,
                   (Rectangle) {container.x, container.y, container.width, container.height},  /** Params = (x-pos, y-pos, height, width) **/
                   containerCenter, 0, WHITE);

    // Get the location of the container
    containerLoc = {container.x, container.y};  // TODO: Want to update location only when container is moved, not every frame
    std::cout << "Guitar Container Coordinates: " << containerLoc.x << ", " << containerLoc.y << std::endl;


    /** Neck **/
    DrawTexturePro(neckTexture,
                   neckRectangle,
                   (Rectangle) {neckRectangle.x, neckRectangle.y, neckRectangle.width, neckRectangle.height},
                   neckCenter, 0, WHITE);

    /** Frets **/
    // Frets separated by 1/8 width of neck
    DrawTexturePro(stringTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x - (neckRectangle.width * .49)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x - (neckRectangle.width * .41)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x - (neckRectangle.width * .33)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x - (neckRectangle.width * .25)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x - (neckRectangle.width * .17)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x - (neckRectangle.width * .09)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x - (neckRectangle.width * .01)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x + (neckRectangle.width * .07)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x + (neckRectangle.width * .15)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x + (neckRectangle.width * .23)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x + (neckRectangle.width * .31)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x + (neckRectangle.width * .39)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    DrawTexturePro(fretTexture,
                   fretRectangle,
                   (Rectangle) {static_cast<float>(fretRectangle.x + (neckRectangle.width * .47)), fretRectangle.y, fretRectangle.width, fretRectangle.height},
                   fretCenter, 0, WHITE);

    /** Strings **/
    // Strings separated 1/6 height of neck
    DrawTexturePro(stringTexture,
                   stringRectangle,
                   (Rectangle) {stringRectangle.x, static_cast<float>(stringRectangle.y - (neckRectangle.height * .40)), stringRectangle.width, stringRectangle.height},
                   stringCenter, 0, WHITE);
    DrawTexturePro(stringTexture,
                   stringRectangle,
                   (Rectangle) {stringRectangle.x, static_cast<float>(stringRectangle.y - (neckRectangle.height * .24)), stringRectangle.width, stringRectangle.height},
                   stringCenter, 0, WHITE);
    DrawTexturePro(stringTexture,
                   stringRectangle,
                   (Rectangle) {stringRectangle.x, static_cast<float>(stringRectangle.y - (neckRectangle.height * .08)), stringRectangle.width, stringRectangle.height},
                   stringCenter, 0, WHITE);
    DrawTexturePro(stringTexture,
                   stringRectangle,
                   (Rectangle) {stringRectangle.x, static_cast<float>(stringRectangle.y + (neckRectangle.height * .08)), stringRectangle.width, stringRectangle.height},
                   stringCenter, 0, WHITE);
    DrawTexturePro(stringTexture,
                   stringRectangle,
                   (Rectangle) {stringRectangle.x, static_cast<float>(stringRectangle.y + (neckRectangle.height * .24)), stringRectangle.width, stringRectangle.height},
                   stringCenter, 0, WHITE);
    DrawTexturePro(stringTexture,
                   stringRectangle,
                   (Rectangle) {stringRectangle.x, static_cast<float>(stringRectangle.y + (neckRectangle.height * .40)), stringRectangle.width, stringRectangle.height},
                   stringCenter, 0, WHITE);


    /** Note Containers **/
    for (int i = 1; i <= 12; i++) {  // Rows
        for (int j = 1; j <= 6; j++) {  // Columns

            // Calculate the diagnonal line of the noteRectangle
            float diagonal = sqrt(pow(noteRectangle.width, 2) + pow(noteRectangle.height, 2));
            DrawRectangle(static_cast<float>(neckRectangle.x - (neckRectangle.width * .53f) + ((neckRectangle.width * .08) * i) - (noteRectangle.width / 2)), static_cast<float>((neckRectangle.y) - ((neckRectangle.height * .16) * j) + (neckRectangle.height * .56f) - (noteRectangle.height / 2)), noteRectangle.width, noteRectangle.height, BLACK);

            // Using DrawEllipse, draw and ellipse that fills and scales with the noteRectangle
            DrawEllipse(static_cast<float>(neckRectangle.x - (neckRectangle.width * .53f) + ((neckRectangle.width * .08) * i)), static_cast<float>((neckRectangle.y) - ((neckRectangle.height * .16) * j) + (neckRectangle.height * .56f)), static_cast<float>(noteRectangle.width / 2), static_cast<float>(noteRectangle.height / 2), noteColorVec[i][j]);

            // Store the container coordinates (only need to once for now)
            if (!notesLocAdded) {
                noteLocations[i][j] = {static_cast<float>(neckRectangle.x - (neckRectangle.width * .53f) + ((neckRectangle.width * .08) * i) - (noteRectangle.width / 2)), static_cast<float>((neckRectangle.y) - ((neckRectangle.height * .16) * j) + (neckRectangle.height * .56f) - (noteRectangle.height / 2))};
            }

            float noteTextSize = (noteRectangle.width > noteRectangle.height) ? static_cast<float>(noteRectangle.height) : static_cast<float>(noteRectangle.width);
            Vector2 noteNewLoc = {static_cast<float>(neckRectangle.x - (neckRectangle.width * .53f) + ((neckRectangle.width * .08) * i) - (noteRectangle.width / 3)), static_cast<float>((neckRectangle.y) - ((neckRectangle.height * .16) * j) + (neckRectangle.height * .56f) - (noteRectangle.height / 2))};
            DrawTextEx(testFont, lowE[i - 1], noteNewLoc, noteTextSize, 0, WHITE);

        }
    }

    return 0;
}

void Neck::hover(Vector2 mousePos) {
    for (int i = 0; i < noteLocations.size(); i++) {
        for (int j = 0; j < noteLocations[i].size(); j++) {
            if (mousePos.x > noteLocations[i][j].x && mousePos.x < noteLocations[i][j].x + (noteRectangle.width) &&
                mousePos.y > noteLocations[i][j].y && mousePos.y < noteLocations[i][j].y + (noteRectangle.height)) {
                std::cout << "Guitar Neck -> Currently Hovering at Coordinates:" << std::endl;
                std::cout << noteLocations[i][j].x << ", " << noteLocations[i][j].y << std::endl;
                noteColorVec[i][j] = hoverColor;
            } else {
                noteColorVec[i][j] = rootColor;
            }

        }
    }
}

void Neck::clickAndDrag(Vector2 mousePos) {
    if (mousePos.x > containerLoc.x - (container.width * .5f) && mousePos.x < containerLoc.x + (container.width * .5f) &&
        mousePos.y > containerLoc.y - (container.height * .5f) && mousePos.y < containerLoc.y + (container.height * .5f)) {
        std::cout << "Within Guitar Container Area" << std::endl;

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            // Make the container follow the mouse position
            // TODO: Should only have to change the container?? Maybe since initial build is in constructor.
            container.x = mousePos.x;
            container.y = mousePos.y;
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

    // Update the container location
    containerLoc = {container.x, container.y};

}

// To remove textures from memory after program closes, must be after main loop ends
void Neck::destroy() {
    UnloadTexture(containerTexture);
    UnloadTexture(neckTexture);
    UnloadTexture(fretTexture);
    UnloadTexture(stringTexture);
}
