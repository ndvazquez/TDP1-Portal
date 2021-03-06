//
// Created by ndv on 5/26/19.
//

#include "RockView.h"
#include <string>

RockView::RockView(Window &window, int xPos, int yPos,
        int factor, YAML::Node& texturesData) :
        View(window, xPos, yPos, factor, ROCK_WIDTH, ROCK_HEIGHT) {
    const YAML::Node& spriteData = texturesData[TEXTURES_ROCK_KEY];
    std::string path = spriteData["path"].as<std::string>();
    sprite = new Sprite(path, window);
}

RockView::~RockView() {
    delete sprite;
}

void RockView::playAnimation(const SDL_Rect& camera) {
    // Force rock to be the same size as a block.
    if (!checkCollisionWithCamera(camera)) return;
    SDL_Rect destRect = {viewPosX - camera.x,
                         viewPosY - camera.y,
                         int(viewWidthInMeters * mtpFactor),
                         int(viewHeightInMeters * mtpFactor)};
    sprite->draw(&destRect);
}

void RockView::setState(int state) {
}
