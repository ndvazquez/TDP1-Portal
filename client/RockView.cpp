//
// Created by ndv on 5/26/19.
//

#include "RockView.h"

RockView::RockView(Window &window, int xPos, int yPos,
        int factor, YAML::Node texturesData) :
        View(window, xPos, yPos, factor) {
    const YAML::Node& spriteData = texturesData[TEXTURES_ROCK_KEY];
    std::string path = spriteData["path"].as<std::string>();
    sprite = new Sprite(path, window);
    viewHeight = sprite->getHeight();
    viewWidth = sprite->getWidth();
}

RockView::~RockView() {
    delete sprite;
}

void RockView::playAnimation() {
    // Force rock to be the same size as a block.
    SDL_Rect destRect = {viewPosX, viewPosY, mtpFactor, mtpFactor};
    sprite->draw(&destRect);

}
