//
// Created by ndv on 5/5/19.
//
#include "../common/Window.h"
#include "../common/Sprite.h"
#include "../common/AnimatedSprite.h"
#include "StageView.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "../common/SDLSession.h"
#include "ChellView.h"
#include "EnergyBallView.h"
#include "AcidView.h"
#include <yaml-cpp/yaml.h>
#include <Stage.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define LEVEL_WIDTH 1500
#define LEVEL_HEIGHT 1500
#define MTP_FACTOR 100
#define CHELL_HEIGHT 200
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

void drawChellWithBox2D(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    std::string bgPath = "resources/Backgrounds/Industrial.png";

    StageView stageView(newWindow, textures, MTP_FACTOR);
    // We'll setup a very basic map, 15x15 blocks.
    std::string metalBlock = "MetalBlock";
    std::string rockBlock = "RockBlock";
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
    // Box2D Stuff.
    float xPos = 1;
    float yPos = 1;
    float chellHeight = 2;
    float chellWidth = 2;
    // We'll subtract 1 block from the world stage for now because it will make Chell collide
    // with the borders of what's being rendered on screen.
    Stage stage(14, 14); // 1m == 1 block == 100px
    stage.addChell(chellHeight, chellWidth, xPos, yPos);
    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(coordinate);

    int chellInitPosX = xPos * MTP_FACTOR;
    // Inverted y axis.
    int chellInitPosY = yPos * MTP_FACTOR * -1 + LEVEL_HEIGHT - CHELL_HEIGHT;

    ChellView chellView(newWindow, chellInitPosX, chellInitPosY, textures);
    // This will be our camera, for now it's just a SDL_Rect
    SDL_Rect camera = {chellInitPosX, chellInitPosY, SCREEN_WIDTH, SCREEN_HEIGHT};

    bool quit = false;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    SDL_Event e;

    float max = 0;

    while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            chellView.handleEvent(e, keys);
            // This should be done server side, but we'll do the event handling here for now.
            if (e.type  == SDL_KEYDOWN  && e.key.repeat == 0) {
                if (e.key.keysym.sym == SDLK_w) chell->jump(yPos);
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->moveRight();
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) chell->moveLeft();
            // This might become an issue when we actually implement a jump animation.
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->stop();

        }
        SDL_Delay(16); // Sleep for 16ms, the real step.
        stage.step();
        bool chellInGround = chell->inGround(yPos);

        if(chell->getVerticalPosition() > max) max = chell->getVerticalPosition();

        chellView.changeJumpingStatus(!chellInGround);
        int newPosX = chell->getHorizontalPosition() * MTP_FACTOR;
        int newPosY = chell->getVerticalPosition() * MTP_FACTOR * -1 + LEVEL_HEIGHT - CHELL_HEIGHT;
        // We move the animated sprite for Chell.
        chellView.move(newPosX, newPosY);
        // Gotta update the camera now to center it around Chell.
        chellView.updateCamera(camera, LEVEL_WIDTH, LEVEL_HEIGHT);
        newWindow.clear();
        stageView.draw(&camera);
        chellView.playAnimation(camera);
        newWindow.render();
    }
    delete coordinate;

    std::cout << max << std::endl;
}

void drawEnergyBall(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    int stageWidth = 9;
    int stageHeight = 6;
    Stage stage(stageWidth, stageHeight);
    int x = 2;
    int y = 2;
    EnergyBallView energyBallView(newWindow, x, y, textures);

    stage.addEnergyBallHorizontal(2, x, y);
    Coordinate* coordinate = new Coordinate(x, y);
    EnergyBall* energyBall = stage.getEnergyBall(coordinate);

    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Delay(16);
        stage.step();
        int newPosX = energyBall->getHorizontalPosition() * MTP_FACTOR;
        int newPosY = energyBall->getVerticalPosition()  * MTP_FACTOR * -1 + SCREEN_HEIGHT;
        std::cout << "EB X: " << newPosX << std::endl;
        energyBallView.move(newPosX, newPosY);
        newWindow.clear();
        energyBallView.playAnimation();
        newWindow.render();
    }
}

void drawAcidPool(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    std::string metalBlockPath = "resources/blocks/metal-block.png";

    Sprite metalBlock(metalBlockPath, newWindow);
    SDL_Rect metalBlockResize = {0, 100, 100, 100};
    AcidView acidView(newWindow, 0, 50, textures);

    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Delay(16);
        newWindow.clear();
        metalBlock.draw(&metalBlockResize);
        metalBlockResize.x += 100;
        metalBlock.draw(&metalBlockResize);
        metalBlockResize.x += 100;
        metalBlock.draw(&metalBlockResize);
        metalBlockResize.x -= 200;
        acidView.playAnimation();
        newWindow.render();
    }
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO);

    drawChellWithBox2D();
    drawEnergyBall();
    drawAcidPool();
}
