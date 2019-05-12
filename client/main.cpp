//
// Created by ndv on 5/5/19.
//
#include "Window.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "SDLSession.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void drawStaticChell(){
    std::string title = "Portal";
    std::string spritePath = "resources/Chell/EnterHold.png";

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
            newSprite.draw(newWindow, x, y);
            newWindow.render();
        }
    }
}

void drawIdleChell(){
    int totalFrames = 7;
    std::string title = "Portal";
    std::string spritePath = "resources/Chell/RestingIdle.png";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    AnimatedSprite restingIdleChell(spritePath, newWindow, totalFrames);

    int x = (SCREEN_WIDTH - restingIdleChell.getWidth()) / 2;
    int y = (SCREEN_HEIGHT - restingIdleChell.getHeight()) / 2;

    bool quit = false;

    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent( &e ) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        newWindow.clear();
        restingIdleChell.draw(newWindow, x, y);
        restingIdleChell.updateFrameStep();
        newWindow.render();
    }
}

void drawRunningChell(){
    int totalFrames = 12;
    std::string title = "Portal";
    std::string spritePath = "resources/Chell/Run.png";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    AnimatedSprite runningChell(spritePath, newWindow, totalFrames);

    int x = (SCREEN_WIDTH - runningChell.getWidth()) / 2;
    int y = (SCREEN_HEIGHT - runningChell.getHeight()) / 2;

    bool quit = false;

    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent( &e ) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        newWindow.clear();
        runningChell.draw(newWindow, x, y);
        runningChell.updateFrameStep();
        newWindow.render();
    }
}

void drawEnterChell(){
    int totalFrames = 16;
    std::string title = "Portal";
    std::string spritePath = "resources/Chell/Enter.png";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    AnimatedSprite runningChell(spritePath, newWindow, totalFrames);

    int x = (SCREEN_WIDTH - runningChell.getWidth()) / 2;
    int y = (SCREEN_HEIGHT - runningChell.getHeight()) / 2;

    bool quit = false;

    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent( &e ) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        newWindow.clear();
        runningChell.draw(newWindow, x, y);
        runningChell.updateFrameStep();
        newWindow.render();
    }
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO);

    drawStaticChell();
    SDL_Delay(500);
    drawIdleChell();
    SDL_Delay(500);
    drawRunningChell();
    SDL_Delay(500);
    drawEnterChell();
}
