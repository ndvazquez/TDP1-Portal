//
// Created by ndv on 6/14/19.
//

#include "GateView.h"

GateView::GateView(Window &window, int xPos, int yPos,
                                   int factor, YAML::Node texturesData) :
        View(window, xPos, yPos, factor, GATE_WIDTH, GATE_HEIGHT){
    const YAML::Node& spriteData = texturesData[TEXTURES_GATE_KEY];
    std::string path = spriteData["path"].as<std::string>();
    sprite = new Sprite(path, window);
    currentState = GATE_CLOSED;
}

GateView::~GateView() {
    delete sprite;
}

void GateView::playAnimation(const SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    SDL_Rect portalRect = {viewPosX - camera.x,
                           viewPosY - camera.y,
                           int(viewWidthInMeters * mtpFactor),
                           int(viewHeightInMeters * mtpFactor)};
    sprite->draw(&portalRect);
}

void GateView::setState(int state) {
    currentState = state;
}