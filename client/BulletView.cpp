//
// Created by ndv on 5/23/19.
//

#include "BulletView.h"
//TODO: Hacer que herede de View.
BulletView::BulletView(Window &window, int xPos, int yPos,
                   YAML::Node texturesData) :
        window(window),
        xPos(xPos),
        yPos(yPos) {
    YAML::Node animationData = texturesData[TEXTURES_BULLET_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
    bulletHeight = animation->getHeight();
    bulletWidth = animation->getWidth();
    animation->setFrameRate(1000 / totalFrames / FRAMERATE_ADJUSTMENT);
}

BulletView::~BulletView(){
    delete animation;
}

void BulletView::move(int newPosX, int newPosY) {
    xPos = newPosX;
    yPos = newPosY;
}

void BulletView::playAnimation(double angle) {
    animation->draw(xPos, yPos, angle);
    animation->updateFrameStep();
}