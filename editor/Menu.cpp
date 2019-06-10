//
// Created by camix on 13/05/19.
//

#include "Menu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <yaml-cpp/yaml.h>

#define BACKGROUND "resources/editor-menu-bg.png"
#define NO_BUTTON ""
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
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int x = node["w"].as<int>();
        int y = node["h"].as<int>();
        struct SDL_Rect* rect = createSDL_Rect(0,0, x, y);
        MenuButton* mb = new MenuButton(rect, name, path);
        this->options.push_back(mb);
        options_space += x;
    }


    // Set the rectangles
    int totalX = window.getWindowWidth() / options_space;
    int spaceBetweenX = totalX/6;

    int h = totalX - spaceBetweenX;
    int spaceBetweenY = (window.getWindowHeight()/HEIGHT_PROPORTION) - h;

    auto optionsIt = options.begin();
    int acum = 0;
    int i = 0;
    for (; optionsIt != options.end(); optionsIt++) {
        MenuButton* option = *optionsIt;
        acum += option->setRectangle(spaceBetweenX + acum, yStart + spaceBetweenY/2, h, h);
        acum += spaceBetweenX;
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
    delete(this->me);
    auto it = this->options.begin();
    while (it != this->options.end()) {
        delete(*it);
    }
}

void Menu::handleMouseButtonDown(MouseButton& event) {
    auto it = options.begin();
    for (; it != options.end(); it++) {
        if ((**it).has(event.getX(), event.getY())) {
            current = (**it).getName();
            return;
        }
    }
}

void Menu::handleMouseButtonUp(MouseButton& event) {
    SDL_Point sdlPoint = {event.getX(), event.getY()};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (isIn) {
        current = NO_BUTTON;
        return;
    }
}


Menu::Menu(Window &window, std::string &current) :
        window(window), current(current) {
    this->set();
}
