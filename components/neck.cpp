#include "neck.h"


Neck::Neck(int screenWidth, int screenHeight) {
    neckImage = LoadImage("../wood.png");     // Loaded in CPU memory (RAM)
    neckTexture = LoadTextureFromImage(neckImage);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(neckImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    boxRec = {0, 0, static_cast<float>(neckTexture.width), static_cast<float>(neckTexture.height)};
    boxCenter = { static_cast<float>(neckTexture.width / 2), static_cast<float>(neckTexture.height / 2)};

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
                   boxRec,
                   (Rectangle) {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2), boxRec.width, boxRec.height * .5f},  /** Params = (x-pos, y-pos, height, width) **/
                   boxCenter, 0, WHITE);

    /**
     * Strings:
     *
     */
    DrawRectangleV({boxCenter.x, boxCenter.y}, {boxRec.width, 10}, LIGHTGRAY);

    return 0;
}

void Neck::destroy() {
    UnloadTexture(neckTexture);       // Texture unloading
}
