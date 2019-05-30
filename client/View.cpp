//
// Created by ndv on 5/25/19.
//

#include "View.h"

View::View(Window &newWindow, int xPos, int yPos, int factor) :
    window(newWindow),
    viewPosX(xPos),
    viewPosY(yPos),
    mtpFactor(factor){
}

void View::move(float newPosX, float newPosY, int levelHeight) {
    viewPosX = (newPosX - viewWidth / 2) * mtpFactor;
    viewPosY = (newPosY + viewHeight / 2) * mtpFactor * -1 + levelHeight;
}

int View::getViewPositionX() {
    return viewPosX;
}

int View::getViewPositionY() {
    return viewPosY;
}