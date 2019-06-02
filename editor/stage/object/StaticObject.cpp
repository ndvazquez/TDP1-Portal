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
    sprite.draw(rect);
}

StaticObject::~StaticObject() = default;
