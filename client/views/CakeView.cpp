//
// Created by ndv on 6/11/19.
//

#include "CakeView.h"
#include <string>

CakeView::CakeView(Window &window, int xPos, int yPos, int factor,
                   YAML::Node& texturesData) :
        View(window, xPos, yPos, factor, CAKE_WIDTH, CAKE_HEIGHT) {
    YAML::Node animationData = texturesData[TEXTURES_CAKE_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
}

CakeView::~CakeView(){
    delete animation;
}

void CakeView::playAnimation(const SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    SDL_Rect destRect = {viewPosX - camera.x,
                         viewPosY - camera.y,
                         int(viewWidthInMeters * mtpFactor),
                         int(viewHeightInMeters * mtpFactor)};
    animation->draw(&destRect);
    animation->updateFrameStep();
}

void CakeView::setState(int state) {}
