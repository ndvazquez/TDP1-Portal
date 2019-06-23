//
// Created by ndv on 6/22/19.
//

#include "EnergyBarView.h"

EnergyBarView::EnergyBarView(Window &window, int xPos, int yPos,
                   int factor, YAML::Node texturesData) :
        View(window, xPos, yPos, factor, ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT) {
    const YAML::Node& spritesData = texturesData[TEXTURES_ENERGY_BAR_KEY];
    for (YAML::const_iterator it = spritesData.begin();
         it != spritesData.end(); ++it) {
        YAML::Node node = *it;
        std::string path = node["path"].as<std::string>();
        Sprite *newSprite = new Sprite(path, window);
        sprites.push_back(newSprite);
    }
}

EnergyBarView::~EnergyBarView() {
    for (auto it = sprites.begin(); it != sprites.end(); ++it) {
        delete *it;
    }
}

void EnergyBarView::playAnimation(const SDL_Rect& camera) {
    if (!checkCollisionWithCamera(camera)) return;
    Sprite* sprite = sprites[currentState];
    SDL_Rect destRect = {viewPosX - camera.x,
                         viewPosY - camera.y,
                         int(viewWidthInMeters * mtpFactor),
                         int(viewHeightInMeters * mtpFactor)};
    sprite->draw(&destRect);
}

void EnergyBarView::setState(int state) {
    if (state == ENERGY_BAR_VERTICAL) {
        viewWidthInMeters = ENERGY_BAR_WIDTH;
        viewHeightInMeters = ENERGY_BAR_HEIGHT;
    }
    if (state == ENERGY_BAR_HORIZONTAL) {
        viewWidthInMeters = ENERGY_BAR_HEIGHT;
        viewHeightInMeters = ENERGY_BAR_WIDTH;
    }
    currentState = state;
}
