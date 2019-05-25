//
// Created by ndv on 5/14/19.
//

#include "ChellView.h"
#include <SDL.h>
#include <unordered_map>
#include "../common/AnimatedSprite.h"
#include <string>
#include <yaml-cpp/yaml.h>

ChellView::ChellView(Window &window, int xPos, int yPos, int factor,
        YAML::Node texturesData) :
            View(window, xPos, yPos, factor),
            isJumping(false),
            flip(SDL_FLIP_NONE){
    viewWidth = 0;
    viewHeight = 0;
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
        if (name == CHELL_RESTING_IDLE) {
            viewWidth = spriteWidth;
            viewHeight = spriteHeight;
        }
        animations[name] = newSprite;
    }
    currentAnimation = CHELL_RESTING_IDLE;
}

ChellView::~ChellView() {
    for (auto it = animations.begin(); it != animations.end(); ++it){
        delete it->second;
    }
}

void ChellView::playAnimation() {}

void ChellView::playAnimation(SDL_Rect& camera) {
    AnimatedSprite* animation = animations[currentAnimation];
    animation->draw(viewPosX - camera.x, viewPosY - camera.y, flip);
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


void ChellView::updateCamera(SDL_Rect &camera, int levelWidth, int levelHeight) {
    camera.x = (viewPosX + viewWidth / 2) - camera.w / 2;
    camera.y = (viewPosY + viewHeight / 2) - camera.h / 2;

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

void ChellView::changeJumpingStatus(bool isChellJumping) {
    isJumping = isChellJumping;
    if (isJumping) {
        currentAnimation = CHELL_JUMPING;
    } else {
        // We'll fire a fake event just to get the handleEvent method going.
        // Otherwise we'll be stuck on the Jumping animation.
        SDL_Event fakeEvent;
        fakeEvent.type = SDL_KEYDOWN;
        fakeEvent.key.keysym.sym = SDLK_l;
        SDL_PushEvent(&fakeEvent);
    }
}
