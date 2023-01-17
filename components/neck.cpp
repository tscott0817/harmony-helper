#include "neck.h"


Neck::Neck(int screenWidth, int screenHeight) {
    neckImage = LoadImage("../wood.png");     // Loaded in CPU memory (RAM)
    neckTexture = LoadTextureFromImage(neckImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(neckImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    neckRectangle = {0, 0, static_cast<float>(neckTexture.width), static_cast<float>(neckTexture.height)};
    neckCenter = { static_cast<float>(neckTexture.width / 2), static_cast<float>(neckTexture.height / 2)};
    neckPosition = {static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f};

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

}

int Neck::drawGuitarNeck() {

    /**
     * Neck:
     *   width = 80% of screen size
     *   height = 20% of screen height
     *
     * **/
    DrawTexturePro(neckTexture,
                   neckRectangle,
                   (Rectangle) {neckPosition.x, neckPosition.y, neckRectangle.width, neckRectangle.height},  /** Params = (x-pos, y-pos, height, width) **/
                   neckCenter, 0, WHITE);

    /**
     * Strings:
     *
     */
    DrawRectangleV({static_cast<float>(neckPosition.x / 4), neckPosition.y}, {neckRectangle.width, 10}, LIGHTGRAY);
//    DrawRectangleV({static_cast<float>(neckPosition.x / 8), neckPosition.y + (neckRectangle.y * (1/6))}, {neckRectangle.width, 10}, LIGHTGRAY);
//    DrawRectangleV({static_cast<float>(neckPosition.x / 8), neckPosition.y + (neckRectangle.y * (1/6))}, {neckRectangle.width, 10}, LIGHTGRAY);
//    DrawRectangleV({static_cast<float>(neckPosition.x / 8), neckPosition.y + (neckRectangle.y * (1/6))}, {neckRectangle.width, 10}, LIGHTGRAY);
//    DrawRectangleV({static_cast<float>(neckPosition.x / 8), neckPosition.y + (neckRectangle.y * (1/6))}, {neckRectangle.width, 10}, LIGHTGRAY);
//    DrawRectangleV({static_cast<float>(neckPosition.x / 8), neckPosition.y + (neckRectangle.y * (1/6))}, {neckRectangle.width, 10}, LIGHTGRAY);

    return 0;
}

void Neck::destroy() {
    UnloadTexture(neckTexture);       // Texture unloading
}
