#include "neck.h"

// TODO: Points of origin are inconsistent between layers (some are top left corner of parent object, others center)
Neck::Neck(int screenWidth, int screenHeight, float width, float height) {

    /** The parent container **/
    containerImage = LoadImage("../blue_background.png");     // Loaded in CPU memory (RAM)
    containerTexture = LoadTextureFromImage(containerImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(containerImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    // Only change the position and size of neckContainer (Make this the params the user can change, drop down menu)
    container = {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2),
                 static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};  // @params: x-pos, y-pos, width, height

    containerCenter = {container.width / 2, container.height / 2};

    /** Neck **/
    neckImage = LoadImage("../wood.png");     // Loaded in CPU memory (RAM)
    neckTexture = LoadTextureFromImage(neckImage);  // Image converted to texture, GPU memory (VRAM)
    UnloadImage(neckImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    // Use the container position +/- some integer to move child objects
    // Use the size of the container * some float to resize child object
    neckRectangle = {container.x, container.y, container.width, container.height * .5f}; // TODO: Fill container with neck (Currently have padding for testing)
    neckCenter = {static_cast<float>(neckRectangle.width / 2), static_cast<float>(neckRectangle.height / 2)};

    /** Frets **/
    fretImage = LoadImage("../fret.png");
    fretTexture = LoadTextureFromImage(fretImage);
    UnloadImage(fretImage);

    fretRectangle = {neckRectangle.x, neckRectangle.y, static_cast<float>(neckRectangle.width * .02), neckRectangle.height};
    fretCenter = {static_cast<float>(fretRectangle.width / 2), static_cast<float>(fretRectangle.height / 2)};

    /** Strings **/
    stringImage = LoadImage("../silver.png");
    stringTexture = LoadTextureFromImage(stringImage);
    UnloadImage(stringImage);

    stringRectangle = {neckRectangle.x, neckRectangle.y, neckRectangle.width, neckRectangle.height * .04f};
    stringCenter = {static_cast<float>(stringRectangle.width / 2), static_cast<float>(stringRectangle.height / 2)};

    /** Note Containers **/
    *noteColor = BLUE;
    noteRectangle = {neckRectangle.x, neckRectangle.y, stringRectangle.width * .025f, stringRectangle.height * 3.0f};
    noteCenter = {static_cast<float>(noteRectangle.width / 2), static_cast<float>(noteRectangle.height / 2)};
    noteLocations = {};
    notesLocAdded = false;
    *noteColorVec = {};
    for (int i = 0; i < 100; i++) {
        noteColorVec->push_back(BLUE);
    }

    // Not in use currently
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

}

int Neck::drawGuitarNeck(float windowScale) {

    /** Container **/
    DrawTexturePro(containerTexture,
                   container,
                   (Rectangle) {container.x, container.y, container.width, container.height},  /** Params = (x-pos, y-pos, height, width) **/
                   containerCenter, 0, WHITE);

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
    // TODO: Probably make a nested loop; so number of strings can be chosen and applied in loop rather than having 6 here
    for (int i = 1; i <= 12; i++) {

        // Draw the note container
        DrawRectangle(neckRectangle.x - (neckRectangle.width * .54f) + ((neckRectangle.width * .08) * i), static_cast<float>(neckRectangle.y - (neckRectangle.height * .40) - (noteRectangle.height * .5f)), noteRectangle.width, noteRectangle.height, noteColorVec->at(0));
        // Store the container coordinates (since iterated here in loop)
        if (!notesLocAdded) {
            noteLocations.push_back({static_cast<float>(neckRectangle.x - (neckRectangle.width * .54f) + ((neckRectangle.width * .08) * i)), static_cast<float>(neckRectangle.y - (neckRectangle.height * .40) - (noteRectangle.height * .5f))});
        }

        DrawRectangle(stringRectangle.x - (stringRectangle.width * .54f) + ((stringRectangle.width * .08) * i), static_cast<float>(stringRectangle.y - (neckRectangle.height * .24) - (noteRectangle.height * .5f)), noteRectangle.width, noteRectangle.height, noteColorVec->at(1));
        if (!notesLocAdded) {
            noteLocations.push_back({static_cast<float>(neckRectangle.x - (neckRectangle.width * .54f) + ((neckRectangle.width * .08) * i)), static_cast<float>(neckRectangle.y - (neckRectangle.height * .24) - (noteRectangle.height * .5f))});
        }

        DrawRectangle(stringRectangle.x - (stringRectangle.width * .54f) + ((stringRectangle.width * .08) * i), static_cast<float>(stringRectangle.y - (neckRectangle.height * .08) - (noteRectangle.height * .5f)), noteRectangle.width, noteRectangle.height, *noteColor);
        if (!notesLocAdded) {
            noteLocations.push_back({static_cast<float>(neckRectangle.x - (neckRectangle.width * .54f) + ((neckRectangle.width * .08) * i)), static_cast<float>(neckRectangle.y - (neckRectangle.height * .08) - (noteRectangle.height * .5f))});
        }

        DrawRectangle(stringRectangle.x - (stringRectangle.width * .54f) + ((stringRectangle.width * .08) * i), static_cast<float>(stringRectangle.y + (neckRectangle.height * .08) - (noteRectangle.height * .5f)), noteRectangle.width, noteRectangle.height, *noteColor);
        if (!notesLocAdded) {
        noteLocations.push_back({static_cast<float>(neckRectangle.x - (neckRectangle.width * .54f) + ((neckRectangle.width * .08) * i)), static_cast<float>(neckRectangle.y + (neckRectangle.height * .08) - (noteRectangle.height * .5f))});
        }

        DrawRectangle(stringRectangle.x - (stringRectangle.width * .54f) + ((stringRectangle.width * .08) * i), static_cast<float>(stringRectangle.y + (neckRectangle.height * .24) - (noteRectangle.height * .5f)), noteRectangle.width, noteRectangle.height, *noteColor);
        if (!notesLocAdded) {
            noteLocations.push_back({static_cast<float>(neckRectangle.x - (neckRectangle.width * .54f) + ((neckRectangle.width * .08) * i)), static_cast<float>(neckRectangle.y + (neckRectangle.height * .24) - (noteRectangle.height * .5f))});
        }

        DrawRectangle(stringRectangle.x - (stringRectangle.width * .54f) + ((stringRectangle.width * .08) * i), static_cast<float>(stringRectangle.y + (neckRectangle.height * .40) - (noteRectangle.height * .5f)), noteRectangle.width, noteRectangle.height, *noteColor);
        if (!notesLocAdded) {
            noteLocations.push_back({static_cast<float>(neckRectangle.x - (neckRectangle.width * .54f) + ((neckRectangle.width * .08) * i)), static_cast<float>(neckRectangle.y + (neckRectangle.height * .40) - (noteRectangle.height * .5f))});
        }

        notesLocAdded = true;
    }
    //std::cout << containerCenter.x << ", " << containerCenter.y << std::endl;




    return 0;
}

void Neck::hover(Vector2 mousePos) {
    //std::cout << mousePos.x << ", " << mousePos.y << std::endl;
    for (int i = 0; i < noteLocations.size(); i++) {
        if (mousePos.x > noteLocations[i].x && mousePos.x < noteLocations[i].x + (noteRectangle.width) &&
            mousePos.y > noteLocations[i].y && mousePos.y < noteLocations[i].y + (noteRectangle.height)) {
            std::cout << "Currently Hovering" << std::endl;
            std::cout << noteLocations[i].x << ", " << noteLocations[i].y << std::endl;
            //*noteColor = MAROON;
            noteColorVec->at(i) = MAROON;
        } else {
            //*noteColor = BLUE;
            noteColorVec->at(i) = BLUE;
        }

    }
}

// To remove textures from memory after program closes, must be after main loop ends
void Neck::destroy() {
    UnloadTexture(containerTexture);
    UnloadTexture(neckTexture);
    UnloadTexture(fretTexture);
    UnloadTexture(stringTexture);
}
