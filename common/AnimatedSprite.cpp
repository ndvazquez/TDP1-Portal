//
// Created by ndv on 5/6/19.
//

#include "AnimatedSprite.h"
#include "Window.h"
#include <SDL.h>
#include <SDL_image.h>
#include <exception>
#include <string>

AnimatedSprite::AnimatedSprite(const std::string &path, Window &window,
        int totalFrames) :
        Sprite(path, window),
        frames(totalFrames),
        currentFrame(0),
        currentFrameStep(0),
        timeSinceLastUpdate(0){
    this->frameWidth = (this->imageWidth / this->frames) - 1;
    this->frameHeight = this->imageHeight;
    this->framerate = 1000 / frames;
}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::updateFrameStep() {
    if (timeSinceLastUpdate + framerate > SDL_GetTicks()){
        return;
    }

    timeSinceLastUpdate = SDL_GetTicks();

    if (currentFrame  >= frames - 1){
        currentFrame = 0;
    }
    currentFrameStep = (frameWidth + 1) * currentFrame;
    ++currentFrame;
}

void AnimatedSprite::draw(int x, int y, SDL_RendererFlip flip) {
    SDL_Rect sourceRect = {currentFrameStep, 0, frameWidth, frameHeight};
    SDL_Rect destRect = {x, y, frameWidth, frameHeight};
    window.draw(*texture, sourceRect, destRect, flip);
}

int AnimatedSprite::getWidth() {
    return this->frameWidth;
}

int AnimatedSprite::getHeight() {
    return this->frameHeight;
}

void AnimatedSprite::draw(SDL_Rect *destRect, SDL_RendererFlip flip) {
    SDL_Rect sourceRect = {currentFrameStep, 0, frameWidth, frameHeight};
    window.draw(*texture, sourceRect, *destRect, flip);
}
