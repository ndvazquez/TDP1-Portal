//
// Created by camix on 13/05/19.
//

#include "Menu.h"
#include "BrickBlock.h"
#define START 15
#define HW 90
#define TOTAL_OPTIONS 1
#define BRICKBLOCK_POS 0

struct SDL_Rect* createSDL_Rect(int x, int y, int w, int h) {
    struct SDL_Rect* rect = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    return rect;
}


Menu::Menu() {
    for (int i = 1; i < TOTAL_OPTIONS + 1; i++) {
        struct SDL_Rect* rect = createSDL_Rect(START, i*20, HW, HW);
        this->options.push_back(rect);
    }
}

Menu::~Menu() {
    auto it = this->options.begin();
    while (it != this->options.end()) {
        delete(*it);
    }
}

void Menu::draw(Window& window) {
    BrickBlock bb(window);
    bb.draw(this->options[BRICKBLOCK_POS]);
}
