//
// Created by camix on 13/05/19.
//

#include "BrickBlockImageContainer.h"


BrickBlockImageContainer::BrickBlockImageContainer() = default;
BrickBlockImageContainer::~BrickBlockImageContainer() = default;

void BrickBlockImageContainer::insert(SDL_Rect* rect) {
    this->BrickBlocks.push_back(rect);
}

void BrickBlockImageContainer::draw(Window& window) {
    BrickBlockImage brickBlock(window);
    std::vector<SDL_Rect*>::iterator it = BrickBlocks.begin();
    for (; it != BrickBlocks.end(); it++) {
        brickBlock.draw(*it);
    }

}


