//
// Created by camix on 13/05/19.
//

#include "Menu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

#define BRICK_BLOCK_POS 0
#define METAL_BLOCK_POS 1
#define ROCK1_POS 2
#define ROCK2_POS 3
#define ROCK3_POS 4
#define BUTTON_POS 5
#define GATE_POS 6

#define TOTAL_OPTIONS 7
#define BRICK_BLOCK_PATH "resources/blocks/breakblock.png"
#define METAL_BLOCK_PATH "resources/blocks/switchblock.png"
#define ROCK1_PATH "resources/rocks/1.png"
#define ROCK2_PATH "resources/rocks/2.png"
#define ROCK3_PATH "resources/rocks/3.png"
#define BUTTON_PATH "resources/button/off.png"
#define GATE_PATH "resources/gate.png"
#define BACKGROUND "resources/editor-menu-bg.png"


struct SDL_Rect* createSDL_Rect(int x, int y, int w, int h) {
    struct SDL_Rect* rect = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    return rect;
}


Menu::Menu(Window &window) :
        window(window){
    this->set();
}

void Menu::set() {
    //this->current = current;

    this->me = createSDL_Rect(0, 0, (window.getWindowWidth()/WIDTH_PROPORTION), window.getWindowHeight());

    // Set de rectangles
    int totalY = window.getWindowHeight() / TOTAL_OPTIONS;
    int spaceBetweenY = totalY/6;
    int w = totalY - spaceBetweenY;
    int spaceBetweenX = (window.getWindowWidth()/WIDTH_PROPORTION) - w; //12 me lo van a pasar por param en futuro
    for (int i = 0; i < TOTAL_OPTIONS; i++) {
        struct SDL_Rect* rect = createSDL_Rect(spaceBetweenX/2, spaceBetweenY + i*totalY, w, w);
        this->options.push_back(rect);
    }
}

void Menu::draw() {
    std::vector<std::string> path = {BRICK_BLOCK_PATH, METAL_BLOCK_PATH,\
        ROCK1_PATH, ROCK2_PATH, ROCK3_PATH, BUTTON_PATH, GATE_PATH};
    Sprite bgSprite(BACKGROUND, window);
    bgSprite.draw(window, this->me);
    for (int i = 0; i < TOTAL_OPTIONS; i++) {
        Sprite sprite(path[i], this->window);
        sprite.draw(this->window, this->options[i]);
    }
}


Menu::~Menu() {
    auto it = this->options.begin();
    while (it != this->options.end()) {
        delete(*it);
    }
}

