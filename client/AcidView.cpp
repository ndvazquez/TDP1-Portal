//
// Created by ndv on 5/23/19.
//

#include "AcidView.h"
#include <string>

AcidView::AcidView(Window &window, int xPos, int yPos, int factor,
        YAML::Node texturesData) :
        View(window, xPos, yPos, factor, ACID_WIDTH, ACID_HEIGHT) {
    YAML::Node animationData = texturesData[TEXTURES_ACID_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
}

AcidView::~AcidView(){
    delete animation;
}

void AcidView::playAnimation(const SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    animation->draw(viewPosX - camera.x, viewPosY - camera.y);
    animation->updateFrameStep();
}

void AcidView::setState(int state) {}
