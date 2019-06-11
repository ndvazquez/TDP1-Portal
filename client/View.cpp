//
// Created by ndv on 5/25/19.
//

#include "View.h"

View::View(Window &newWindow, int xPos, int yPos,
        int factor, float width, float height) :
    window(newWindow),
    viewWidthInMeters(width),
    viewHeightInMeters(height),
    viewPosX(xPos),
    viewPosY(yPos),
    mtpFactor(factor) {
    collisionBox.x = viewPosX;
    collisionBox.y = viewPosY;
    collisionBox.w = int(viewWidthInMeters * mtpFactor);
    collisionBox.h = int(viewHeightInMeters * mtpFactor);
}

void View::move(float newPosX, float newPosY, int levelHeight) {
    viewPosX = (newPosX - viewWidthInMeters / 2) * mtpFactor;
    viewPosY = (newPosY + viewHeightInMeters / 2) * mtpFactor * -1 +
            levelHeight;
    collisionBox.x = viewPosX;
    collisionBox.y = viewPosY;
}

int View::getViewPositionX() {
    return viewPosX;
}

int View::getViewPositionY() {
    return viewPosY;
}

bool View::checkCollisionWithCamera(const SDL_Rect &camera) {
    bool result = SDL_HasIntersection(&collisionBox, &camera);
    return result;
}

int View::getCenterPosX() {
    int centerPosX = viewPosX + viewWidthInMeters * mtpFactor / 2;
    return centerPosX;
}

int View::getCenterPosY() {
    int centerPosY = viewPosY + viewHeightInMeters * mtpFactor / 2;
    return centerPosY;
}
