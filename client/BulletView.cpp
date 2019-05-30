//
// Created by ndv on 5/23/19.
//

#include "BulletView.h"
#include "View.h"

//TODO: Hacer que herede de View.
BulletView::BulletView(Window &window, int xPos, int yPos, int factor,
                   YAML::Node texturesData) :
        View(window, xPos, yPos, factor) {
    YAML::Node animationData = texturesData[TEXTURES_BULLET_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
    viewHeightInMeters = animation->getHeight();
    viewWidthInMeters = animation->getWidth();
    animation->setFrameRate(1000 / totalFrames / FRAMERATE_ADJUSTMENT);
}

void BulletView::playAnimation(){}

BulletView::~BulletView(){
    delete animation;
}

void BulletView::playAnimation(double angle) {
    animation->draw(viewPosX, viewPosY, angle);
    animation->updateFrameStep();
}
