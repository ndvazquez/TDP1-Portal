//
// Created by ndv on 5/30/19.
//

#include "BluePortalView.h"
#include <string>

BluePortalView::BluePortalView(Window &window, int xPos, int yPos,
        int factor, YAML::Node texturesData) :
        View(window, xPos, yPos, factor, PORTAL_WIDTH, PORTAL_HEIGHT){
    YAML::Node animationData = texturesData[TEXTURES_BLUE_PORTAL_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
}

BluePortalView::~BluePortalView() {
    delete animation;
}

void BluePortalView::playAnimation(const SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    SDL_Rect portalRect = {viewPosX - camera.x,
                           viewPosY - camera.y,
                           int(viewWidthInMeters * mtpFactor),
                           int(viewHeightInMeters * mtpFactor)};
    animation->draw(&portalRect);
    animation->updateFrameStep();
}

void BluePortalView::setState(int state) {
    if (state == PORTAL_HORIZONTAL) {
        viewWidthInMeters = PORTAL_HEIGHT;
        viewHeightInMeters = PORTAL_WIDTH;
    }
    if (state == PORTAL_VERTICAL) {
        viewWidthInMeters = PORTAL_WIDTH;
        viewHeightInMeters = PORTAL_HEIGHT;
    }
}
