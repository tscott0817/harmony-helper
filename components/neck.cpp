#include "neck.h"


Neck::Neck(int screenWidth, int screenHeight, float width, float height) {

    /** The parent container **/
    containerImage = LoadImage("../plaid.png");     // Loaded in CPU memory (RAM)
    containerTexture = LoadTextureFromImage(containerImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(containerImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    // Only change the position and size of neckContainer (Make this the params the user can change, drop down menu)
    container = {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2),
                     width, height};  // @params: x-pos, y-pos, width, height

    containerCenter = {container.width / 2, container.height / 2};

    /** Neck **/
    neckImage = LoadImage("../wood.png");     // Loaded in CPU memory (RAM)
    neckTexture = LoadTextureFromImage(neckImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(neckImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    // Use the container position +/- some integer to move child objects
    // Use the size of the container * some float to resize child object
    neckRectangle = {container.x, container.y, container.width, container.height * .5f};
    neckCenter = {static_cast<float>(neckRectangle.width / 2), static_cast<float>(neckRectangle.height / 2)};

    /** Strings **/
    stringImage = LoadImage("../silver.png");
    stringTexture = LoadTextureFromImage(stringImage);
    UnloadImage(stringImage);

    stringRectangle = {neckRectangle.x, neckRectangle.y, neckRectangle.width, neckRectangle.height * .25f};
    stringCenter = {static_cast<float>(stringRectangle.width / 2), static_cast<float>(stringRectangle.height / 2)};

    // Not in use currently
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

}

int Neck::drawGuitarNeck() {

    /** Container **/
    DrawTexturePro(containerTexture,
                   container,
                   (Rectangle) {container.x, container.y, container.width, container.height},  /** Params = (x-pos, y-pos, height, width) **/
                   containerCenter, 0, WHITE);
    /** Neck **/
    DrawTexturePro(neckTexture,
                   neckRectangle,
                   (Rectangle) {neckRectangle.x, neckRectangle.y, neckRectangle.width, neckRectangle.height},  /** Params = (x-pos, y-pos, height, width) **/
                   neckCenter, 0, WHITE);

    /** Strings **/
    DrawTexturePro(stringTexture,
                   stringRectangle,
                   (Rectangle) {stringRectangle.x, stringRectangle.y, stringRectangle.width, stringRectangle.height},  /** Params = (x-pos, y-pos, height, width) **/
                   stringCenter, 0, WHITE);

    return 0;
}

// To remove textures from memory after program closes, must be after main loop ends
void Neck::destroy() {
    UnloadTexture(containerTexture);
    UnloadTexture(neckTexture);
    UnloadTexture(stringTexture);
}
