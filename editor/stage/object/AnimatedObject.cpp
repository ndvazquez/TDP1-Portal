//
// Created by camix on 22/05/19.
//

#include "AnimatedObject.h"

AnimatedObject::AnimatedObject(std::string &path, Window &window, int totalFrames, const std::string &name, int w, int h) :
        Object(name, w , h),
        sprite(path, window, totalFrames),
        window(window) {}

void AnimatedObject::draw(SDL_Rect* rect) {
    sprite.draw(rect, SDL_FLIP_NONE);
    sprite.updateFrameStep();
}


AnimatedObject::~AnimatedObject() = default;
