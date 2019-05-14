//
// Created by camix on 13/05/19.
//
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "BrickBlock.h"
#define PATH "resources/block/breakblock.png"



BrickBlock::BrickBlock(Window& window) : window(window), sprite(PATH, window) {}

BrickBlock::~BrickBlock() {}

void BrickBlock::draw(int x, int y) {
    this->sprite.draw(this->window, x, y);
}


void BrickBlock::draw(SDL_Rect* rect) {
    this->sprite.draw(this->window, rect);
}