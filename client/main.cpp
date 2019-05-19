//
// Created by ndv on 5/5/19.
//
#include "../common/Window.h"
#include "../common/Sprite.h"
#include "../common/AnimatedSprite.h"
#include "../common/StageView.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "../common/SDLSession.h"
#include "ChellView.h"
#include <yaml-cpp/yaml.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define LEVEL_WIDTH 1500
#define LEVEL_HEIGHT 1500
#define MATRIX_TO_PIXEL_FACTOR 100
#define REFRESH_STEP 16 // 16ms
#define CHELL_VELOCITY 12
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

void fakeChellSimulation(SDL_Event& e, int& chellVelocityX, int& chellVelocityY){
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch (e.key.keysym.sym){
            case SDLK_d:
                chellVelocityX += CHELL_VELOCITY;
                break;
            case SDLK_a:
                chellVelocityX -= CHELL_VELOCITY;
                break;
            case SDLK_w:
                chellVelocityY -= CHELL_VELOCITY;
                break;
            case SDLK_s:
                chellVelocityY += CHELL_VELOCITY;
                break;
            default:
                break;
        }
    }
    if (e.type == SDL_KEYUP && e.key.repeat == 0){
        switch (e.key.keysym.sym){
            case SDLK_d:
                chellVelocityX -= CHELL_VELOCITY;
                break;
            case SDLK_a:
                chellVelocityX += CHELL_VELOCITY;
                break;
            case SDLK_w:
                chellVelocityY += CHELL_VELOCITY;
                break;
            case SDLK_s:
                chellVelocityY -= CHELL_VELOCITY;
                break;
            default:
                break;
        }
    }
}

void drawStageAndChell(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    StageView stageView(newWindow, textures, MATRIX_TO_PIXEL_FACTOR);

    std::string bgPath = "resources/Backgrounds/Industrial.png";
    Sprite background(bgPath, newWindow);

    // We'll setup a very basic map.
    std::string metalBlock = "MetalBlock";
    std::string rockBlock = "RockBlock";
    for (int i = 0; i < 15; ++i){
        stageView.addTile(i, 0, metalBlock);
        stageView.addTile(i, 14, metalBlock);
    }
    for (int i = 0; i < 15; ++i){
        stageView.addTile(0, i, rockBlock);
        stageView.addTile(14, i, rockBlock);
    }

    int chellInitPosX = 0;
    int chellInitPosY = 0;
    int chellVelocityX = 0;
    int chellVelocityY = 0;

    ChellView chell(newWindow, chellInitPosX, chellInitPosY, textures);
    // This will be our camera, for now it's just a SDL_Rect
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    bool quit = false;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent( &e ) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            chell.handleEvent(e, keys);
            fakeChellSimulation(e, chellVelocityX, chellVelocityY);
        }
        SDL_Delay(REFRESH_STEP);
        //TODO: Here we'll use the position on the world given by the server.
        chell.move(chell.getPosX() + chellVelocityX, chell.getPosY() + chellVelocityY,
                LEVEL_WIDTH, LEVEL_HEIGHT);

        chell.updateCamera(camera, LEVEL_WIDTH, LEVEL_HEIGHT);

        newWindow.clear();
        background.draw(newWindow, nullptr);
        stageView.draw(newWindow, &camera);
        chell.playAnimation(camera);
        newWindow.render();
    }
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO);

    drawStageAndChell();
}
