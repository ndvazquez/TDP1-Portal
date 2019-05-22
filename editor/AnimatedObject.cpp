//
// Created by camix on 22/05/19.
//

#include "AnimatedObject.h"

AnimatedObject::AnimatedObject(const std::string& path, Window& window, int totalFrames) :
    sprite(path, window, totalFrames), window(window) {}

void AnimatedObject::draw(SDL_Rect* rect) {
    sprite.draw(window, rect, SDL_FLIP_NONE);
    sprite.updateFrameStep();
}

AnimatedObject::~AnimatedObject() = default;
