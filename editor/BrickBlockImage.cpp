//
// Created by camix on 13/05/19.
//
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "BrickBlockImage.h"
#define PATH "resources/blocks/breakblock.png"



BrickBlockImage::BrickBlockImage(Window& window) : window(window), sprite(PATH, window) {}

BrickBlockImage::~BrickBlockImage() = default;

void BrickBlockImage::draw(int x, int y) {
    this->sprite.draw(this->window, x, y);
}


void BrickBlockImage::draw(SDL_Rect* rect) {
    this->sprite.draw(this->window, rect);
}