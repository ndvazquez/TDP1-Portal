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
#include "BulletView.h"
#include "RockView.h"
#include <yaml-cpp/yaml.h>
#include <Stage.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define LEVEL_WIDTH 1000
#define LEVEL_HEIGHT 600
#define MTP_FACTOR 100
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
    for (int i = 0; i < 10; ++i){
        stageView.addTile(i, 0, metalBlock);
        stageView.addTile(i, 5, metalBlock);
    }
    for (int i = 0; i < 6; ++i){
        stageView.addTile(0, i, metalBlock);
        stageView.addTile(9, i, metalBlock);
    }
    // Rock background.
//    for (int i = 1; i < 14; ++i){
//        for (int j = 1; j < 14; ++j){
//            stageView.addTile(i, j, rockBlock);
//        }
//    }
    // Box2D Stuff.
    float xPos = 1;
    float yPos = 1;
    float chellHeight = 2;
    float chellWidth = 2;
    // We'll subtract 1 block from the world stage for now because it will make Chell collide
    // with the borders of what's being rendered on screen.
    Stage stage(9, 6); // 1m == 1 block == 100px
    stage.addChell(chellHeight, chellWidth, xPos, yPos);
    float metalBlockPosX = 4;
    float metalBlockPosY = 1;
    stage.addMetalBlock(1, metalBlockPosX, metalBlockPosY);
    stage.addMetalBlock(1, metalBlockPosX + 1, metalBlockPosY);

    // Add a rock next to the metal block.
    stage.addRock(2, metalBlockPosX + 3, metalBlockPosY);

    stageView.addTile(int(metalBlockPosX), int(metalBlockPosY) * -1 + 5, metalBlock);
    stageView.addTile(int(metalBlockPosX) + 1, int(metalBlockPosY) * -1 + 5, metalBlock);
    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(coordinate);
    // Get the rock object.
    Coordinate* coordinateRock = new Coordinate(metalBlockPosX + 3, metalBlockPosY);
    Rock* rock = stage.getRock(coordinateRock);

    //Chell grabs the Rock
    chell->grabRock(rock);

    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR, textures);
    // This will be our camera, for now it's just a SDL_Rect
    SDL_Rect camera = {int(xPos), int(yPos), SCREEN_WIDTH, SCREEN_HEIGHT};
    // RockView.
    RockView rockView(newWindow, metalBlockPosX + 2, metalBlockPosY, MTP_FACTOR, textures);

    bool quit = false;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    SDL_Event e;
    
    while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // This should be done server side, but we'll do the event handling here for now.
            if (e.type  == SDL_KEYDOWN  && e.key.repeat == 0) {
                if (e.key.keysym.sym == SDLK_w) chell->jump(); //jump
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->moveRight();
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) chell->moveLeft();
            // This might become an issue when we actually implement a jump animation.
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->stop();
        }

        stage.step();
        std::cout << chell->getState() << std::endl;
        chellView.setState(chell->getState());
        float newPosX = chell->getHorizontalPosition();
        float newPosY = chell->getVerticalPosition();
        // We move the animated sprite for Chell.
        chellView.move(newPosX, newPosY, LEVEL_HEIGHT);
        // Gotta update the camera now to center it around Chell.
        chellView.updateCamera(camera, LEVEL_WIDTH, LEVEL_HEIGHT);
        // Get current Rock position and move it.
        float newRockPosX = rock->getHorizontalPosition();
        float newRockPosY = rock->getVerticalPosition();

        rockView.move(newRockPosX, newRockPosY, LEVEL_HEIGHT);

        newWindow.clear();
        stageView.draw(&camera);
        rockView.playAnimation();
        chellView.playAnimation(camera);
        newWindow.render();


    }
    delete coordinate;
    delete coordinateRock;
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
    EnergyBallView energyBallView(newWindow, x, y, MTP_FACTOR, textures);

    stage.addEnergyBallHorizontal(2, x, y);
    Coordinate* coordinate = new Coordinate(x, y);
    EnergyBall* energyBall = stage.getEnergyBall(coordinate);

    energyBall->fly();

    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        stage.step();
        float newPosX = energyBall->getHorizontalPosition();
        float newPosY = energyBall->getVerticalPosition();
        energyBallView.move(newPosX, newPosY, SCREEN_HEIGHT);
      
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
    AcidView acidView(newWindow, 0, 50, MTP_FACTOR, textures);

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

void drawBullet(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    BulletView bulletView(newWindow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, textures);
    double bulletAngle = 0;
    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
                switch(e.key.keysym.sym){
                    case SDLK_d:
                        bulletAngle += 30;
                        break;
                    case SDLK_a:
                        bulletAngle -= 30;
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_Delay(16);
        newWindow.clear();
        bulletView.playAnimation(bulletAngle);
        newWindow.render();
    }
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO);

    drawChellWithBox2D();
//    drawEnergyBall();
    //drawAcidPool();
    //drawBullet();
}
