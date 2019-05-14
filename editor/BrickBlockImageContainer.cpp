//
// Created by camix on 13/05/19.
//

#include "BrickBlockContainer.h"


BrickBlockContainer::BrickBlockContainer() {}
BrickBlockContainer::~BrickBlockContainer() {}

void BrickBlockContainer::insert(SDL_Rect* rect) {
    this->BrickBlocks.push_back(rect);
}

void BrickBlockContainer::draw(Window& window) {
    BrickBlockImage brickBlock(window);
    std::vector<SDL_Rect*>::iterator it = BrickBlocks.begin();
    for (; it != BrickBlocks.end(); it++) {
        brickBlock.draw(*it);
    }

}


