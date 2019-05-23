//
// Created by camix on 13/05/19.
//

#include "Menu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <yaml-cpp/yaml.h>
#include "RockButton.h"
#include "MouseButtonUp.h"

#define BRICK_BLOCK_POS 0
#define METAL_BLOCK_POS 1
#define ROCK1_POS 2
#define ROCK2_POS 3
#define ROCK3_POS 4
#define BUTTON_POS 5
#define GATE_POS 6

#define TOTAL_OPTIONS 7
#define NAME_METAL_BLOCK "MetalBlock"
#define PATH_METAL_BLOCK "resources/blocks/metal-block.png"
#define NAME_ROCK_BLOCK "RockBlock"
#define PATH_ROCK_BLOCK "resources/blocks/rock-block.png"
#define BACKGROUND "resources/editor-menu-bg.png"
#define NO_BUTTON ""
#define MENU_TEXTURES "editor/menu-textures.yaml"
#define MENU_TEXTURES_KEY "StaticObjects"

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

    this->me = createSDL_Rect(0, 0, (window.getWindowWidth()/WIDTH_PROPORTION), window.getWindowHeight());

    int yPortions = 0;
    YAML::Node texturesInfo = YAML::LoadFile(MENU_TEXTURES);
    const YAML::Node& staticObjects = texturesInfo[MENU_TEXTURES_KEY];

    YAML::const_iterator it = staticObjects.begin();
    for (; it != staticObjects.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int x = node["x"].as<int>();
        int y = node["y"].as<int>();
        struct SDL_Rect* rect = createSDL_Rect(0,0, x, y);
        MenuButton* mb = new MenuButton(rect, name, path);
        this->options.push_back(mb);
        yPortions += y;
    }


    // Set the rectangles
    int totalY = window.getWindowHeight() / yPortions;
    int spaceBetweenY = totalY/6;

    int w = totalY - spaceBetweenY;
    int spaceBetweenX = (window.getWindowWidth()/WIDTH_PROPORTION) - w;



    auto optionsIt = options.begin();
    int acum = 0;
    int i = 0;
    for (; optionsIt != options.end(); optionsIt++) {
        MenuButton* option = *optionsIt;
        acum += option->setRectangle(spaceBetweenX/2, spaceBetweenY + acum, w, w);
        acum += spaceBetweenY;
        i++;
    }

}

void Menu::draw() {
    Sprite bgSprite(BACKGROUND, window);
    bgSprite.draw(window, this->me);

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

void Menu::handle(MouseButtonDown *event) {
    auto it = options.begin();
    for (; it != options.end(); it++) {
        if ((**it).has(event->getX(), event->getY())) {
            current = (**it).getName();
            return;
        }
    }
}

void Menu::handle(MouseButtonUp *event) {
    SDL_Point sdlPoint = {event->getX(), event->getY()};
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
