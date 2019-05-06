//
// Created by ndv on 5/5/19.
//

#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"

Sprite::Sprite(const std::string &path, Window& window) {
    SDL_Surface* tempSurface = nullptr;
    tempSurface = IMG_Load(path.c_str());
    if (tempSurface == nullptr){
        throw SpriteInitException();
    }
    this->texture = SDL_CreateTextureFromSurface(window.renderer, tempSurface);
    if (this->texture == nullptr){
        throw SpriteInitException();
    }
    this->imageHeight = tempSurface->h;
    this->imageWidth = tempSurface->w;
    SDL_FreeSurface(tempSurface);
}

Sprite::~Sprite() {
    this->free();
}

void Sprite::draw(Window &destWindow, int x, int y, SDL_Rect *sourceRect) {
    SDL_Rect destRect = {x, y ,this->imageWidth ,this->imageHeight};
    if (sourceRect != nullptr){
        destRect.w = sourceRect->w;
        destRect.h = sourceRect->h;
    }
    destWindow.draw(*this->texture, *sourceRect, destRect);
}

void Sprite::free(){
    SDL_DestroyTexture(this->texture);
}

int Sprite::getWidth() {
    return this->imageWidth;
}

int Sprite::getHeight() {
    return this->imageHeight;
}
