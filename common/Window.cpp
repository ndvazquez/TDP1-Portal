//
// Created by ndv on 5/5/19.
//

#include "Window.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

Window::Window(const std::string& title, int width, int height, int flags) :
    windowWidth(width), windowHeight(height){
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
    //std::cerr << "Estoy destruyendo LA WINDOWWWW" << std::endl;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Window::render(){
    //std::cerr << "ANDTESS  SDL_RenderPresent failed: " << SDL_GetError() << std::endl;

    SDL_RenderPresent(this->renderer);
    //std::cerr << "DESPUEEES SDL_RenderPresent failed: " << SDL_GetError() << std::endl;
}

void Window::clear() {
    //std::cerr << "Adentro de clear" << std::endl;
    //std::cerr << "SDL_RenderClear failed: " << SDL_GetError() << std::endl;
    if (SDL_RenderClear(this->renderer) < 0) {
        std::cerr << "SDL_RenderClear failed: " << SDL_GetError() << std::endl;
    }
    //std::cerr << "SDL_RenderClear failed: " << SDL_GetError() << std::endl;
}

void Window::draw(SDL_Texture& texture, SDL_Rect& sourceRect,
        SDL_Rect& destRect) {
    if (SDL_RenderCopy(this->renderer, &texture, &sourceRect, &destRect) < 0) {
        std::cerr << "SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
    }
}

int Window::getWindowWidth() {
    return windowWidth;
}

int Window::getWindowHeight() {
    return windowHeight;
}
