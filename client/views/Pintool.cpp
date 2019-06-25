//
// Created by ndv on 6/24/19.
//

#include "Pintool.h"
#include <string>

PintoolView::PintoolView(Window &window, int xPos, int yPos,
                   int factor, YAML::Node& texturesData) :
        View(window, xPos, yPos, factor, PINTOOL_WIDTH, PINTOOL_HEIGHT) {
    const YAML::Node& spriteData = texturesData[TEXTURES_PIN_KEY];
    std::string path = spriteData["path"].as<std::string>();
    sprite = new Sprite(path, window);
}

PintoolView::~PintoolView() {
    delete sprite;
}

void PintoolView::playAnimation(const SDL_Rect& camera) {
    if (!checkCollisionWithCamera(camera)) return;
    SDL_Rect destRect = {viewPosX - camera.x,
                         viewPosY - camera.y,
                         int(viewWidthInMeters * mtpFactor),
                         int(viewHeightInMeters * mtpFactor)};
    sprite->draw(&destRect);
}

void PintoolView::setState(int state) {
}
