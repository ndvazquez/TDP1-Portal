//
// Created by ndv on 5/23/19.
//

#include "BulletView.h"
#include "View.h"
#include <string>

BulletView::BulletView(Window &window, int xPos, int yPos, int factor,
                   YAML::Node texturesData) :
        View(window, xPos, yPos, factor, BULLET_WIDTH, BULLET_HEIGHT) {
    YAML::Node animationData = texturesData[TEXTURES_BULLET_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
    animation->setFrameRate(1000 / totalFrames / FRAMERATE_ADJUSTMENT);
}

void BulletView::playAnimation(const SDL_Rect &camera){
    if (!checkCollisionWithCamera(camera)) return;
    animation->draw(viewPosX - camera.x, viewPosY - camera.y);
    animation->updateFrameStep();
}

BulletView::~BulletView(){
    delete animation;
}

void BulletView::setState(int state) {}
