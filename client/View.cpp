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
    viewPosX = newPosX * mtpFactor - viewWidth / 2;
    viewPosY = newPosY * mtpFactor * -1 + levelHeight - viewHeight / 2;
}
