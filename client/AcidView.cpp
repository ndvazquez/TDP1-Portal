//
// Created by ndv on 5/23/19.
//

#include "AcidView.h"

AcidView::AcidView(Window &window, int xPos, int yPos,
                               YAML::Node texturesData) :
        window(window),
        xPos(xPos),
        yPos(yPos) {
    YAML::Node animationData = texturesData[TEXTURES_ACID_KEY];
    std::string path = animationData["path"].as<std::string>();
    int totalFrames = animationData["frames"].as<int>();
    animation = new AnimatedSprite(path, window, totalFrames);
    acidHeight = animation->getHeight();
    acidWidth = animation->getWidth();
}

AcidView::~AcidView(){
    delete animation;
}

void AcidView::move(int newPosX, int newPosY) {
    xPos = newPosX;
    yPos = newPosY;
}

void AcidView::playAnimation() {
    animation->draw(xPos, yPos);
    animation->updateFrameStep();
}
