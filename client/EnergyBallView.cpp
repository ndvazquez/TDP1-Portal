//
// Created by ndv on 5/21/19.
//

#include "EnergyBallView.h"
#include "../common/AnimatedSprite.h"
#include "../common/Window.h"
#include <string>
#include <yaml-cpp/yaml.h>
#include "View.h"

EnergyBallView::EnergyBallView(Window &window, int xPos, int yPos, int factor,
        YAML::Node texturesData) :
        View(window, xPos, yPos, factor) {
    YAML::Node animationData = texturesData[TEXTURES_EB_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
    viewHeightInMeters = animation->getHeight();
    viewWidthInMeters = animation->getWidth();
}

EnergyBallView::~EnergyBallView() {
    delete animation;
}

void EnergyBallView::playAnimation() {
    animation->draw(viewPosX, viewPosY);
    animation->updateFrameStep();
}
