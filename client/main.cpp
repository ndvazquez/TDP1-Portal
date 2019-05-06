//
// Created by ndv on 5/5/19.
//
#include "Window.h"
#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void drawStaticChell(){
    std::string title = "Portal";
    std::string spritePath = "client/resources/Chell/EnterHold.png";
    SDL_Rect* destRect = nullptr;
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    Sprite newSprite(spritePath, newWindow);


    int x = (SCREEN_WIDTH - newSprite.getWidth()) / 2;
    int y = (SCREEN_HEIGHT - newSprite.getHeight()) / 2;

    bool quit = false;

    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent( &e ) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }

            newWindow.clear();
            newSprite.draw(newWindow, x, y, destRect);
            newWindow.render();
        }
    }
}

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);

    drawStaticChell();

    IMG_Quit();
    SDL_Quit();
}
