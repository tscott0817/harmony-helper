#ifndef GUITAR_APP_GUITAR_H
#define GUITAR_APP_GUITAR_H
#include "raylib.h"
#include "instrument.h"
#include <iostream>
#include <vector>
#include <memory>

class Guitar : public Instrument {
private:

    Image neckImage;
    Texture2D neckTexture;
    Rectangle neckRectangle;
    Vector2 neckCenter;

    Image fretImage;
    Texture2D fretTexture;
    Rectangle fretRectangle;
    Vector2 fretCenter;

    Image fretMarkerImage;
    Texture2D fretMarkerTexture;
    Rectangle fretMarkerRectangle;
    Vector2 fretMarkerCenter;

    Image stringImage;
    Texture2D stringTexture;
    Rectangle stringRectangle;
    Vector2 stringCenter;

    Image noteImage;
    Texture2D noteTexture;
    Rectangle noteRectangle;
    Vector2 noteCenter;

    bool notesLocAdded;
    std::vector<std::vector<Vector2>> noteLocations;
    std::vector<std::vector<Color>> noteColorVec;
    std::vector<std::vector<int>> noteClickedBoolVec;

    // Text and Font
    Font testFont;
    float fontSize;
    Vector2 fontPosition;
    Vector2 textSize;
    int currentFontFilter;

    // TODO: Need to do add sharp keys (probably just share with enharmonic flat keys)
    const char *lowE[13] = {"E", "F", "Gb/F#", "G", "Ab/G#", "A", "Bb/A#", "B", "C", "Db/C#", "D", "Eb/D#", "E"};
    const char *a[13] = {"A", "Bb/A#", "B", "C", "Db/C#", "D", "Eb/D#", "E", "F", "Gb/F#", "G", "Ab/G#", "A"};
    const char *d[13] = {"D", "Eb/D#", "E", "F", "Gb/F#", "G", "Ab/G#", "A", "Bb/A#", "B", "C", "Db/C#", "D"};
    const char *g[13] = {"G", "Ab/G#", "A", "Bb/A#", "B", "C", "Db/C#", "D", "Eb/D#", "E", "F", "Gb/F#", "G"};
    const char *b[13] = {"B","C", "Db/C#", "D", "Eb/D#", "E", "F", "Gb/F#", "G", "Ab/G#", "A", "Bb/A#", "B"};
    const char *highE[13] = {"E", "F", "Gb/F#", "G", "Ab/G#", "A", "Bb/A#", "B", "C", "Db/C#", "D", "Eb/D#", "E"};
//    const char *lowE[13] = {"E", "F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E"};
//    const char *a[13] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A"};
//    const char *d[13] = {"D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D"};
//    const char *g[13] = {"G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G"};
//    const char *b[13] = {"B","C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
//    const char *highE[13] = {"E", "F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E"};
    std::vector<const char **> noteTextVec;

    /** Colors **/
    Color containerColor;
    Color neckColor = Color{135, 98, 51, 255};
    Color outlineColor = Color{179, 130, 68, 255};

    /** Audio **/
    Sound testSound;

public:
    Guitar(int screenWidth, int screenHeight, float posX, float posY, float width, float height);
    ~Guitar() = default;

    /** Inherited Methods **/
    void draw(float windowScale) override;
    void selectNote(Vector2 mousePos) override;
    void clickAndDrag(Vector2 mousePos) override;
    void notesActivate() override;
    void destroy() override;
//    void playSound() override;
//    void initAudio() override;
//    void unloadAudio() override;

    // Setters
    void setCanDraw(bool state) override;

    // Getters
    bool getCanDraw() override;

};


#endif //GUITAR_APP_GUITAR_H
