//
// Created by ndv on 5/23/19.
//

#include "AcidView.h"

AcidView::AcidView(Window &window, int xPos, int yPos, int factor,
                               YAML::Node texturesData) :
                               View(window, xPos, yPos, factor) {
    YAML::Node animationData = texturesData[TEXTURES_ACID_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
    viewHeight = animation->getHeight();
    viewWidth = animation->getWidth();
}

AcidView::~AcidView(){
    delete animation;
}

void AcidView::playAnimation() {
    animation->draw(viewPosX, viewPosY);
    animation->updateFrameStep();
}
