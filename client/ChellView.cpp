//
// Created by ndv on 5/14/19.
//

#include "ChellView.h"
#include <SDL.h>
#include <vector>
#include "../common/AnimatedSprite.h"
#include <string>
#include <yaml-cpp/yaml.h>

ChellView::ChellView(Window &window, int xPos, int yPos, int factor,
        YAML::Node texturesData) :
            View(window, xPos, yPos, factor, CHELL_WIDTH, CHELL_HEIGHT),
            flip(SDL_FLIP_NONE){
    YAML::Node animationsData = texturesData[TEXTURES_INFO_KEY];
    for (YAML::const_iterator it = animationsData.begin();
        it != animationsData.end(); ++it){
        YAML::Node node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int frames = node["frames"].as<int>();
        AnimatedSprite* newSprite = new AnimatedSprite(path, window, frames);
        // This is wrong, we should use a set Width and Height.
        animations.push_back(newSprite);
    }
    currentState = IDLE;
}

ChellView::~ChellView() {
    for (auto it = animations.begin(); it != animations.end(); ++it){
        delete *it;
    }
}

void ChellView::playAnimation(SDL_Rect& camera) {
    if (!checkCollisionWithCamera(camera)) return;

    int animationIndex = currentState;
    if (currentState == MOVING_RIGHT) {
        --animationIndex;
        flip = SDL_FLIP_NONE;
    }
    if (currentState == MOVING_LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    AnimatedSprite* animation = animations[animationIndex];
    animation->draw(viewPosX - camera.x, viewPosY - camera.y, flip);
    animation->updateFrameStep();
}

void ChellView::updateCamera(SDL_Rect &camera, int levelWidth, int levelHeight) {
    camera.x = (viewPosX + viewWidthInMeters * mtpFactor / 2) - camera.w / 2;
    camera.y = (viewPosY + viewHeightInMeters * mtpFactor / 2) - camera.h / 2;

    if(camera.x < 0){
        camera.x = 0;
    }
    if(camera.y < 0){
        camera.y = 0;
    }
    if(camera.x > levelWidth - camera.w){
        camera.x = levelWidth - camera.w;
    }
    if(camera.y > levelHeight - camera.h){
        camera.y = levelHeight - camera.h;
    }
}

void ChellView::setState(State state) {
    currentState = state;
}