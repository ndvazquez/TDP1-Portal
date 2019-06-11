//
// Created by camix on 22/05/19.
//

#include <string>
#include "StaticObject.h"
#include "../../../common/Window.h"

StaticObject::StaticObject(std::string& path, Window& window, const std::string &name, int w, int h) :
    Object(name, w, h),
    window(window),
    sprite(path, window) {}

void StaticObject::draw(SDL_Rect *rect) {
    int pixelsAbove = rect->h * (POSITIONS_ABOVE);
    SDL_Rect newRect = {rect->x, rect->y - pixelsAbove, rect->w * w, rect->h * h};
    sprite.draw(&newRect);
}

StaticObject::~StaticObject() = default;
