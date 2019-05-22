#include <utility>

//
// Created by camix on 18/05/19.
//

#include "MenuButton.h"
#include "../common/Sprite.h"

MenuButton::MenuButton(struct SDL_Rect* rect, std::string name, std::string& path) :
        myPosition(rect), name(std::move(name)), path(path) {}

MenuButton::~MenuButton() {
    delete(myPosition);
}

void MenuButton::set(struct SDL_Rect* rect) {
    myPosition = rect;
}

bool MenuButton::has(Sint32 x, Sint32 y) {
    SDL_Point sdlPoint = {x, y};
    return (bool) SDL_PointInRect(&sdlPoint, this->myPosition);
}

std::string MenuButton::getName() {
    return this->name;
}

void MenuButton::draw(Window &window) {
    Sprite sprite(this->path, window);
    sprite.draw(window, this->myPosition);
}

MenuButton& MenuButton::operator=(MenuButton origin) {
    this->myPosition = origin.myPosition;
    this->name = origin.name;
    this->path = origin.path;
    return *this;
}

MenuButton::MenuButton(const MenuButton& origin)  :
        myPosition(origin.myPosition), name(origin.name), path(origin.path) {}

int MenuButton::setRectangle(int x, int y, int w, int h) {
    myPosition->x = x;
    myPosition->y = y;
    myPosition->w = myPosition->w * w;
    myPosition->h = myPosition->h * h;
    return myPosition->h;
}
