//
// Created by camix on 13/05/19.
//

#include "Menu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

//#define START 15
//#define HW 90
#define TOTAL_OPTIONS 3
#define BRICK_BLOCK_POS 0
#define BRICK_BLOCK_PATH "resources/blocks/breakblock.png"
#define METAL_BLOCK_POS 1
#define METAL_BLOCK_PATH "resources/blocks/switchblock.png"
#define ROCK1_POS 2
#define ROCK1_PATH "resources/rocks/1.png"
#define ROCK2_POS 3
#define ROCK2_PATH "resources/rocks/2.png"
#define ROCK3_POS 4
#define ROCK3_PATH "resources/rocks/3.png"
#define BUTTON_POS 5
#define BUTTON_PATH "resources/button/off.png"
#define GATE_POS 6
#define GATE_PATH "resources/gate.png"


struct SDL_Rect* createSDL_Rect(int x, int y, int w, int h) {
    struct SDL_Rect* rect = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    return rect;
}


Menu::Menu(uint8_t& current, uint32_t xEnd, uint32_t yEnd) :
    current(current), xEnd(xend), yEnd(yend) {
    // Set de rectangles
    int y = 40;
    for (int i = 0; i < TOTAL_OPTIONS; i++) {
        struct SDL_Rect* rect = createSDL_Rect(START, y + i*90, HW, HW);
        this->options.push_back(rect);
    }

    // Set de images in order.
    path = {BRICK_BLOCK_PATH, METAL_BLOCK_PATH,\
        ROCK1_PATH, ROCK2_PATH, ROCK3_PATH, BUTTON_PATH, GATE_PATH};
    // Set the sprites in the same order.
    for (int i = 0; i < TOTAL_OPTIONS; i++) {
        Sprite sprite(path[i], this->window);
        this->images.push_back(sprite);
    }
}

Menu::~Menu() {
    auto it = this->options.begin();
    while (it != this->options.end()) {
        delete(*it);
    }
}

void Menu::draw(Window& window) {
    for (int i = 0; i < TOTAL_OPTIONS; i++) {
        this->images[i].draw(this->window, this->options[i]);
    }
}
