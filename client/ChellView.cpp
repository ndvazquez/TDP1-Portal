//
// Created by ndv on 5/14/19.
//

#include "ChellView.h"
#include <SDL.h>
#include <unordered_map>
#include "../common/AnimatedSprite.h"
#include <string>
#include <yaml-cpp/yaml.h>

ChellView::ChellView(Window &window, int xPos, int yPos, YAML::Node texturesData) :
            gameWindow(window),
            chellWidth(0),
            chellHeight(0),
            xPos(xPos),
            yPos(yPos),
            xVelocity(0),
            yVelocity(0),
            flip(SDL_FLIP_NONE){

    YAML::Node animationsData = texturesData[TEXTURES_INFO_KEY];
    for (YAML::const_iterator it = animationsData.begin();
        it != animationsData.end(); ++it){
        YAML::Node node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int frames = node["frames"].as<int>();
        AnimatedSprite* newSprite = new AnimatedSprite(path, window, frames);
        int spriteWidth = newSprite->getWidth();
        int spriteHeight = newSprite->getHeight();
        // This is wrong, we should use a set Width and Height.
        if (spriteWidth > chellWidth) chellWidth = spriteWidth;
        if (spriteHeight > chellHeight) chellHeight = spriteHeight;
        animations[name] = newSprite;
    }
    currentAnimation = CHELL_RESTING_IDLE;
}

ChellView::~ChellView() {
    for (auto it = animations.begin(); it != animations.end(); ++it){
        delete it->second;
    }
}

void ChellView::playAnimation(SDL_Rect& camera) {
    AnimatedSprite* animation = animations[currentAnimation];
    animation->draw(gameWindow, xPos - camera.x, yPos - camera.y, flip);
    animation->updateFrameStep();
}

void ChellView::handleEvent(SDL_Event& e, const Uint8 *keys){
    if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
        currentAnimation = CHELL_RUN;
        flip = flip == SDL_FLIP_NONE ? flip : SDL_FLIP_NONE;
    }
    if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
        currentAnimation = CHELL_RUN;
        flip = flip == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : flip;
    }
    if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]){
        currentAnimation = CHELL_RESTING_IDLE;
    }
}

void ChellView::move(int newPosX, int newPosY, int levelWidth, int levelHeight){
    if (newPosX >= 0 && newPosX + chellWidth < levelWidth){
        xPos = newPosX;
    }

    if (newPosY >= 0 && newPosY + chellHeight < levelHeight){
        yPos = newPosY;
    }
}

void ChellView::updateCamera(SDL_Rect &camera, int levelWidth, int levelHeight) {
    camera.x = (xPos + chellWidth / 2) - camera.w / 2;
    camera.y = (yPos + chellHeight / 2) - camera.h / 2;

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
//This will be gone when we merge server and client.
int ChellView::getPosX() {
    return xPos;
}

int ChellView::getPosY() {
    return yPos;
}
