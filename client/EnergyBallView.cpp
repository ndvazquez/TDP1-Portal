//
// Created by ndv on 5/21/19.
//

#include "EnergyBallView.h"

EnergyBallView::EnergyBallView(Window &window, int xPos, int yPos,
        YAML::Node texturesData) :
        window(window),
        xPos(xPos),
        yPos(yPos) {
    YAML::Node animationData = texturesData[TEXTURES_EB_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
    energyBallHeight = animation->getHeight();
    energyBallWidth = animation->getWidth();
}

EnergyBallView::~EnergyBallView() {
    delete animation;
}

void EnergyBallView::move(int newPosX, int newPosY) {
    xPos = newPosX;
    yPos = newPosY;
}

void EnergyBallView::playAnimation() {
    animation->draw(window, xPos, yPos);
    animation->updateFrameStep();
}
