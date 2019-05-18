//
// Created by camix on 13/05/19.
//

#include "Stage.h"
#include <iostream>
#define TEXTURE_CONFIG_FILE "config/textures.yaml"
#define Y 0
#define H this->window.getWindowHeight()
#define TOTAL_X this->window.getWindowWidth()
#define X (TOTAL_X)/this->xPortion
#define W (TOTAL_X) - (X)


void setSDL_Rect(struct SDL_Rect* rect, int x, int y, int w, int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

Stage::Stage(Window& window, std::string& current, int xPortion):
    window(window), stageView(window, TEXTURE_CONFIG_FILE, 100) , current(current), xPortion(xPortion) {
    this->me = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    this->setSize();
}

void Stage::setSize() {
    setSDL_Rect(this->me, X, Y, W, H);
}

Stage::~Stage() {
    delete (this->me);
}


void Stage::insert(uint32_t x, uint32_t y) {
    if (current.empty()) {
        //throw()
    }
    stageView.addTile(x,y, this->current);
}

void Stage::draw() {
    SDL_Rect matrixRect = {0 , 0, W, H};
    Sprite bgSprite("resources/editor-stage-bg.png", window);
    bgSprite.draw(window, this->me);
    stageView.draw(window, &matrixRect , X);
}
