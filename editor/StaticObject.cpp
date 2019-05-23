//
// Created by camix on 22/05/19.
//

#include <string>
#include "StaticObject.h"
#include "../common/Window.h"

StaticObject::StaticObject(const std::string& path, Window& window, const std::string &name) :
    Object(name),
    window(window),
    sprite(path, window) {}

void StaticObject::draw(SDL_Rect *rect) {
    sprite.draw(window, rect);
}

StaticObject::~StaticObject() = default;
