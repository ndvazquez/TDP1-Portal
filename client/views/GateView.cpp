//
// Created by ndv on 6/14/19.
//

#include "GateView.h"
#include <iostream>

GateView::GateView(Window &window, int xPos, int yPos,
                                   int factor, YAML::Node texturesData) :
        View(window, xPos, yPos, factor, GATE_WIDTH, GATE_HEIGHT){
    const YAML::Node& spriteData = texturesData[TEXTURES_GATE_KEY];
    std::string path = spriteData["path"].as<std::string>();
    int frames = spriteData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, frames);
    previousState = GATE_OPEN;
    currentState = GATE_OPEN;
    transitionAnimation = false;
    lastFrame = frames - 1;
}

GateView::~GateView() {
    delete animation;
}

void GateView::playAnimation(const SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    SDL_Rect destRect = {viewPosX - camera.x,
                           viewPosY - camera.y,
                           int(viewWidthInMeters * mtpFactor),
                           int(viewHeightInMeters * mtpFactor)};
    animation->draw(&destRect);
    if (transitionAnimation) {
        animation->updateFrameStep();
        if ((animation->getCurrentFrame() ==  lastFrame && currentState == GATE_OPEN) ||
                (animation->getCurrentFrame() ==  0 && currentState == GATE_CLOSED)) {
            transitionAnimation = false;
        }
    }

}

void GateView::setState(int state) {
    previousState = currentState;
    currentState = state;
    if (previousState != currentState) {
        transitionAnimation = true;
        animation->reverseAnimation();
    }
}