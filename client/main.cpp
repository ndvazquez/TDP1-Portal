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
#include <yaml-cpp/yaml.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LEVEL_WIDTH 1500
#define LEVEL_HEIGHT 1500
#define TEST_CAMERA_STEP 100
#define MATRIX_TO_PIXEL_FACTOR 100
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

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

void drawRunningChell(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    int totalFramesIdle = 7;
    int totalFramesRunning = 12;
    std::string title = "Portal";
    std::string spritePathRunning = "resources/Chell/Run.png";
    std::string spritePathIdle = "resources/Chell/RestingIdle.png";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    AnimatedSprite runningChell(spritePathRunning, newWindow, totalFramesRunning);
    AnimatedSprite restingIdleChell(spritePathIdle, newWindow, totalFramesIdle);


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
        restingIdleChell.draw(newWindow, x-200, y);
        restingIdleChell.draw(newWindow, x+250, y);
        restingIdleChell.updateFrameStep();
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

void drawStage(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    StageView stageView(newWindow, textures, MATRIX_TO_PIXEL_FACTOR);

    std::string metalBlock = "MetalBlock";
    std::string rockBlock = "RockBlock";
    // We'll setup a very basic map.
    for (int i = 0; i < 15; ++i){
        stageView.addTile(i, 0, metalBlock);
        stageView.addTile(i, 14, metalBlock);
    }
    for (int i = 0; i < 15; ++i){
        stageView.addTile(0, i, metalBlock);
        stageView.addTile(14, i, metalBlock);
    }

    for (int i = 1; i < 14; ++i){
        for (int j = 1; j < 14; ++j){
            stageView.addTile(i, j, rockBlock);
        }
    }

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    bool quit = false;

    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent( &e ) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_d:
                        camera.x += TEST_CAMERA_STEP;
                        if (camera.x + camera.w > LEVEL_WIDTH){
                            camera.x = LEVEL_WIDTH - camera.w;
                        }
                        break;
                    case SDLK_a:
                        camera.x -= TEST_CAMERA_STEP;
                        if (camera.x < 0){
                            camera.x = 0;
                        }
                        break;
                    case SDLK_w:
                        camera.y -= TEST_CAMERA_STEP;
                        if (camera.y < 0){
                            camera.y = 0;
                        }
                        break;
                    case SDLK_s:
                        camera.y += TEST_CAMERA_STEP;
                        if (camera.y + camera.h > LEVEL_HEIGHT){
                            camera.y = LEVEL_HEIGHT - camera.h;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        newWindow.clear();
        stageView.draw(newWindow, &camera);
        newWindow.render();
    }


}
int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO);
    drawStaticChell();
    SDL_Delay(300);
    drawRunningChell();
    SDL_Delay(300);
    drawEnterChell();
    SDL_Delay(300);
    drawStage();
}
