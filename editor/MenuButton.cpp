#include <utility>

//
// Created by camix on 18/05/19.
//

#include "MenuButton.h"
#include "../common/Sprite.h"

MenuButton::MenuButton(struct SDL_Rect *rect, int id, std::string &path) :
        myPosition(rect), name(id), path(path) {}

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

int MenuButton::getName() {
    return this->name;
}

void MenuButton::draw(Window &window) {
    Sprite sprite(this->path, window);
    sprite.draw(this->myPosition);
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
    if(myPosition->h == 1) {
        myPosition->y += h/4;
    }
    myPosition->w = myPosition->w * w/2;
    myPosition->h = myPosition->h * h/2;
    return myPosition->w + myPosition->x;
}
