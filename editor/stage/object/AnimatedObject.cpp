//
// Created by camix on 22/05/19.
//

#include "AnimatedObject.h"

AnimatedObject::AnimatedObject(std::string &path, Window &window, int totalFrames, int id, int w, int h) :
        Object(id, w , h),
        sprite(path, window, totalFrames),
        window(window) {}

void AnimatedObject::draw(SDL_Rect* rect) {
    int pixelsAbove = rect->h * (POSITIONS_ABOVE);
    SDL_Rect newRect = {rect->x, rect->y - pixelsAbove, rect->w * w, rect->h * h};
    sprite.draw(&newRect, SDL_FLIP_NONE);
    sprite.updateFrameStep();
}


AnimatedObject::~AnimatedObject() = default;
