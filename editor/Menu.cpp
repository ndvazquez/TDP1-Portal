//
// Created by camix on 13/05/19.
//

#include "Menu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
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

    // Set de rectangles
    int totalY = window.getWindowHeight() / TOTAL_OPTIONS;
    int spaceBetweenY = totalY/6;

    int w = totalY - spaceBetweenY;
    int spaceBetweenX = (window.getWindowWidth()/WIDTH_PROPORTION) - w;

    std::vector<struct SDL_Rect*> rectangles;
    for (int i = 0; i < TOTAL_OPTIONS; i++) {
        struct SDL_Rect* rect = createSDL_Rect(spaceBetweenX/2, spaceBetweenY + i*totalY, w, w);
        rectangles.push_back(rect);
    }
    MenuButton* mbb = new MenuButton(rectangles[0], NAME_METAL_BLOCK, PATH_METAL_BLOCK);
    MenuButton* rbb = new MenuButton(rectangles[1], NAME_ROCK_BLOCK, PATH_ROCK_BLOCK);
    this->options.push_back(mbb);
    this->options.push_back(rbb);
 }

void Menu::draw() {
    //std::cerr << "\nMenu draw: \n";

    Sprite bgSprite(BACKGROUND, window);
    //std::cerr << "Sprite creado \n";

    bgSprite.draw(window, this->me);
    //std::cerr << "Sprite draweado \n";

    auto it = options.begin();
    //std::cerr << "Creo iterador \n";
    int i = 0;
    for (; it != options.end(); it++) {

        (**it).draw(this->window);
        //std::cerr << "dibujo OPTION " << i << std::endl;
        //Sprite sprite(path[i], this->window);
        //sprite.draw(this->window, this->options[i]);
        i++;
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
            std::cerr << "New current is: " << current<< std::endl;
            return;
        }
    }
}

void Menu::handle(MouseButtonUp *event) {
    SDL_Point sdlPoint = {event->getX(), event->getY()};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (isIn) {
        current = NO_BUTTON;
        std::cerr << "New current is: " << current<< std::endl;
        return;
    }
}


Menu::Menu(Window &window, std::string &current) :
        window(window), current(current) {
    this->set();
}

