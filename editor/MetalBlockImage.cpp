//
// Created by camix on 13/05/19.
//

#include "MetalBlockImage.h"
#define PATH "resources/blocks/switchblock.png"

MetalBlockImage::MetalBlockImage(Window &window) : window(window), sprite(PATH, window){
}

MetalBlockImage::~MetalBlockImage() = default;

void MetalBlockImage::draw(int x, int y) {
    this->sprite.draw(this->window, x, y);
}

void MetalBlockImage::draw(SDL_Rect *rect) {
    this->sprite.draw(this->window, rect);
}
