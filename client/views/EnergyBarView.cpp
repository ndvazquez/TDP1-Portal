//
// Created by ndv on 6/22/19.
//

#include "EnergyBarView.h"

EnergyBarView::EnergyBarView(Window &window, int xPos, int yPos,
                   int factor, YAML::Node texturesData) :
        View(window, xPos, yPos, factor, ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT) {
    const YAML::Node& spriteData = texturesData[TEXTURES_ENERGY_BAR_KEY];
    std::string path = spriteData["path"].as<std::string>();
    sprite = new Sprite(path, window);
}

EnergyBarView::~EnergyBarView() {
    delete sprite;
}

void EnergyBarView::playAnimation(const SDL_Rect& camera) {
    // Force rock to be the same size as a block.
    if (!checkCollisionWithCamera(camera)) return;
    SDL_Rect destRect = {viewPosX - camera.x,
                         viewPosY - camera.y,
                         int(viewWidthInMeters * mtpFactor),
                         int(viewHeightInMeters * mtpFactor)};
    sprite->draw(&destRect);
}

void EnergyBarView::setState(int state) {
}