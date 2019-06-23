//
// Created by camix on 13/05/19.
//

#include "Menu.h"
#include "../common/constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <yaml-cpp/yaml.h>
#include <iostream>

#define BACKGROUND "resources/editor-menu-bg.png"
#define NO_BUTTON 0
#define MENU_TEXTURES "editor/textures-info.yaml"
#define MENU_TEXTURES_KEY "MenuData"

struct SDL_Rect* createSDL_Rect(int x, int y, int w, int h) {
    struct SDL_Rect* rect = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    return rect;
}


void Menu::set() {
    //this->current = current;
    int window_h = window.getWindowHeight();
    int yStart = (window_h - window_h/HEIGHT_PROPORTION);
    this->me = createSDL_Rect(0, yStart, window.getWindowWidth(), window_h);

    int options_space = 0;
    YAML::Node texturesInfo = YAML::LoadFile(MENU_TEXTURES);
    const YAML::Node& staticObjects = texturesInfo[MENU_TEXTURES_KEY];

    YAML::const_iterator it = staticObjects.begin();
    for (; it != staticObjects.end(); ++it) {
        const YAML::Node& node = *it;
        int name = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int x = node[OBJECT_WIDTH].as<int>();
        int y = node[OBJECT_HEIGHT].as<int>();
        struct SDL_Rect* rect = createSDL_Rect(0,0, x, y);
        MenuButton* mb = new MenuButton(rect, name, path);
        this->options.push_back(mb);
        options_space += x;
    }


    // Set the rectangles
    int totalX  = window.getWindowWidth() / options_space * 1.90;
    int spaceBetweenX = totalX/6;


    int h = totalX - spaceBetweenX;
    int spaceBetweenY = (window.getWindowHeight()/HEIGHT_PROPORTION) - h;

    //SDL_Rect rec = {totalX,  yStart + spaceBetweenY/2, h, h};


    auto optionsIt = options.begin();
    int acum = 0;
    int i = 0;
    for (; optionsIt != options.end(); optionsIt++) {
        MenuButton* option = *optionsIt;
        acum = option->setRectangle(spaceBetweenX + acum, yStart + spaceBetweenY/2, h, h);
        i++;
    }

}

void Menu::draw() {
    Sprite bgSprite(BACKGROUND, window);
    bgSprite.draw(this->me);

    auto it = options.begin();
    for (; it != options.end(); it++) {
        (**it).draw(this->window);
    }
}


Menu::~Menu() {
    auto it = this->options.begin();
    while (it != this->options.end()) {
        auto act = it;
        it++;
        delete(*act);
    }
    delete(this->me);
}

void Menu::handleMouseButtonDown(MouseButton& event) {
    auto it = options.begin();
    for (; it != options.end(); it++) {
        if ((**it).has(event.getX(), event.getY())) {
            *current = (**it).getName();
            return;
        }
    }
}

void Menu::handleMouseButtonUp(MouseButton& event) {
    SDL_Point sdlPoint = {event.getX(), event.getY()};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (isIn) {
        *current = NO_BUTTON;
        return;
    }
}


Menu::Menu(Window &window, int *current) :
        window(window), current(current) {
    this->set();
}
