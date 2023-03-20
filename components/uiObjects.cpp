#include "uiObjects.h"

void UIObjects::hover(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, container)) {
        std::cout << "Hovering over UIObjects" << std::endl;
    }
}
