#include "modal_chart.h"

ModalChart::ModalChart(int screenWidth, int screenHeight, float posX, float posY, float width, float height) {
    containerImage = LoadImage("../images/plaid.png");
    containerTexture = LoadTextureFromImage(containerImage);
    UnloadImage(containerImage);
    container = {posX, posY,
                 static_cast<float>(screenWidth * width), static_cast<float>(screenHeight * height)};
    containerCenter = {container.width / 2, container.height / 2};


//    chartImage = LoadImage("../pink.png");
//    chartTexture = LoadTextureFromImage(containerImage);
    // UnloadImage(chartImage);
    chartRectangle = {container.x, container.y, container.width * .14f, container.height * .15f};
    chartCenter = {static_cast<float>(chartRectangle.width / 2), static_cast<float>(chartRectangle.height / 2)};

    chartLocAdded = false;

    // TODO: Just filling to 100 for room, but don't want to hardcode this 100
    for (int i = 0; i < 100; i++) {
        std::vector<Vector2> tempLoc;
        std::vector<Color> tempColor;
        for (int j = 0; j < 100; j++) {
            tempLoc.push_back({0, 0});
            tempColor.push_back(BLUE);
        }
        chartLocations.push_back(tempLoc);
        chartColorVec.push_back(tempColor);
    }

}

void ModalChart::initModalChart() {

}
int ModalChart::drawModalChart(float windowScale) {
    /** Container **/
    DrawTexturePro(containerTexture,
                   container,
                   (Rectangle) {container.x, container.y, container.width, container.height},
                   containerCenter, 0, WHITE);

    /** Chart **/
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
//            DrawTexturePro(chartTexture,
//                           chartRectangle,
//                           (Rectangle) {container.x * i, container.y * j, chartRectangle.width, chartRectangle.height},
//                           chartCenter, 0, WHITE);

            DrawRectangle(static_cast<float>((container.x) + ((container.width * .1435f) * i) - (container.width * .5f)),
                          static_cast<float>((container.y) - ((container.height * .16f) * j) + (container.height * .325f)),
                          chartRectangle.width, chartRectangle.height, chartColorVec[i][j]);

            // Store the container coordinates (since iterated here in loop)
            if (!chartLocAdded) {
                chartLocations[i][j] = {static_cast<float>((container.x) + ((container.width * .1435f) * i) - (container.width * .5f)),
                                        static_cast<float>((container.y) - ((container.height * .16f) * j) + (container.height * .325f))};
            }
        }
    }

    chartLocAdded = true;

    return 0;  // TODO: Probably no reason to return int, make void

}
void ModalChart::hover(Vector2 mousePos) {
    for (int i = 0; i < chartLocations.size(); i++) {
        for (int j = 0; j < chartLocations[i].size(); j++) {
            if (mousePos.x > chartLocations[i][j].x && mousePos.x < chartLocations[i][j].x + (chartRectangle.width) &&
                mousePos.y > chartLocations[i][j].y && mousePos.y < chartLocations[i][j].y + (chartRectangle.height)) {
                std::cout << "Chord Chart -> Currently Hovering at Coordinates:" << std::endl;
                std::cout << chartLocations[i][j].x << ", " << chartLocations[i][j].y << std::endl;
                //*noteColor = MAROON;
                //noteColorVec->at(i) = MAROON;
                chartColorVec[i][j] = MAROON;
            } else {
                //*noteColor = BLUE;
                //noteColorVec->at(i) = BLUE;
                chartColorVec[i][j] = BLUE;
            }

        }
    }
}
void ModalChart::destroy() {
    UnloadTexture(containerTexture);
    UnloadTexture(chartTexture);
}
