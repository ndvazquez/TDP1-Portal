//
// Created by ndv on 5/5/19.
//

#include "Window.h"
#include <SDL.h>
#include <SDL_image.h>

Window::Window(const std::string& title, int width, int height, int flags) {
    if (SDL_CreateWindowAndRenderer(width, height, flags, &this->window, &this->renderer)){
        throw WindowInitException();
    }
    SDL_SetWindowTitle(this->window, title.c_str());
    if (SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF)){
        throw WindowInitException();
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best")){
        throw WindowInitException();
    }
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Window::render(){
    SDL_RenderPresent(this->renderer);
}

void Window::clear(){
    SDL_RenderClear(this->renderer);
}

void Window::draw(SDL_Texture& texture, SDL_Rect& sourceRect,
        SDL_Rect& destRect) {
    SDL_RenderCopy(this->renderer, &texture, &sourceRect, &destRect);
}