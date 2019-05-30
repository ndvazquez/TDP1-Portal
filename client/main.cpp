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
#include "ButtonView.h"
#include <yaml-cpp/yaml.h>
#include <Stage.h>
#include "../common/constants.h"
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define LEVEL_WIDTH 2000
#define LEVEL_HEIGHT 1400
#define MTP_FACTOR 100
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

void drawChell(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // Cool space background.
    std::string bgPath = "resources/Backgrounds/NebulaRed.png";
    Sprite background(bgPath, newWindow);
    std::string metalBlock = "MetalBlock";
    // We'll setup a very basic map, 10x6 blocks.
    int stageWidth = 20;
    int stageHeight = 14;
    Stage stage(stageWidth, stageHeight); // 1m == 1 block == 100px
    StageView stageView(newWindow, textures, MTP_FACTOR);
    float metalBlockPosX = 0;
    float metalBlockPosY = 0;
    float metalSide = 1;
    for (int i = 0; i < 20; ++i){
        stage.addMetalBlock(metalSide, metalBlockPosX+i, metalBlockPosY);
        stageView.addTile(metalBlockPosX+i, metalBlockPosY * -1 + stageHeight, metalBlock);
    }
    // Time to add some platforms!
    stage.addMetalBlock(metalSide, metalBlockPosX + 1, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 1, (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 4, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 4, (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 4, metalBlockPosY + 2);
    stageView.addTile(metalBlockPosX + 4, (metalBlockPosY + 2) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 5, metalBlockPosY + 2);
    stageView.addTile(metalBlockPosX + 5, (metalBlockPosY + 2) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 6, metalBlockPosY + 2);
    stageView.addTile(metalBlockPosX + 6, (metalBlockPosY + 2) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 6, metalBlockPosY + 3);
    stageView.addTile(metalBlockPosX + 6, (metalBlockPosY + 3) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 7, metalBlockPosY + 3);
    stageView.addTile(metalBlockPosX + 7, (metalBlockPosY + 3) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 7, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 7, (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 8, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 8, (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 11, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 11, (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 12, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 12, (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 12, metalBlockPosY + 3);
    stageView.addTile(metalBlockPosX + 12, (metalBlockPosY + 3) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 12, metalBlockPosY + 4);
    stageView.addTile(metalBlockPosX + 12, (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 15, metalBlockPosY + 5);
    stageView.addTile(metalBlockPosX + 15, (metalBlockPosY + 5) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 15, metalBlockPosY + 6);
    stageView.addTile(metalBlockPosX + 15, (metalBlockPosY + 6) * -1 + stageHeight, metalBlock);

    // Box2D Chell and stuff.
    float xPos = 1;
    float yPos = 4;
    float chellHeight = CHELL_HEIGHT;
    float chellWidth = CHELL_WIDTH;
    stage.addChell(chellHeight, chellWidth, xPos, yPos);

    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(coordinate);


    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR, textures);
    // This will be our camera, for now it's just a SDL_Rect
    SDL_Rect camera = {int(xPos), int(yPos), SCREEN_WIDTH, SCREEN_HEIGHT};

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
                if (e.key.keysym.sym == SDLK_s) chell->downloadRock();
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->moveRight();
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) chell->moveLeft();
            // This might become an issue when we actually implement a jump animation.
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->stop();
        }

        stage.step();

        chellView.setState(chell->getState());
        float newPosX = chell->getHorizontalPosition();
        float newPosY = chell->getVerticalPosition();

        // We move the animated sprite for Chell.
        chellView.move(newPosX, newPosY, LEVEL_HEIGHT);
        // Gotta update the camera now to center it around Chell.
        chellView.updateCamera(camera, LEVEL_WIDTH, LEVEL_HEIGHT);
        SDL_Rect outlineRect = {chellView.getViewPositionX() - camera.x,
                                chellView.getViewPositionY() - camera.y,
                                int(chellWidth * MTP_FACTOR),
                                int(chellHeight * MTP_FACTOR)};
        newWindow.clear();
        SDL_Rect* bgRect = NULL;
        background.draw(bgRect);
        stageView.draw(camera);
        chellView.playAnimation(camera);
        //Debug rectangle to see Chell's collision box.
        //newWindow.drawRectangle(outlineRect);
        newWindow.render();
    }
    delete coordinate;
}

void drawChellAndRock(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    StageView stageView(newWindow, textures, MTP_FACTOR);
    // We'll setup a very basic map, 10x6 blocks.
    std::string metalBlock = "MetalBlock";

    for (int i = 0; i < 10; ++i){
        stageView.addTile(i, 0, metalBlock);
        stageView.addTile(i, 5, metalBlock);
    }
    for (int i = 0; i < 6; ++i){
        stageView.addTile(0, i, metalBlock);
        stageView.addTile(9, i, metalBlock);
    }

    // Box2D Stuff.
    float xPos = 1;
    float yPos = 1;
    float chellHeight = 2;
    float chellWidth = 1;
    Stage stage(10, 6); // 1m == 1 block == 100px
    stage.addChell(chellHeight, chellWidth, xPos, yPos);
    float metalBlockPosX = 4;
    float metalBlockPosY = 1;
    float metalSide = 1;
    stage.addMetalBlock(metalSide, metalBlockPosX, metalBlockPosY);
    stage.addMetalBlock(metalSide, metalBlockPosX + 1, metalBlockPosY);

    // Add a rock next to the metal block.
    size_t rockSide = 2;
    stage.addRock(rockSide, metalBlockPosX + 3, metalBlockPosY);

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
                if (e.key.keysym.sym == SDLK_s) chell->downloadRock();
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->moveRight();
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) chell->moveLeft();
            // This might become an issue when we actually implement a jump animation.
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->stop();
        }

        stage.step();
        bool chellInGround = chell->inGround();

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
        stageView.draw(camera);
        rockView.playAnimation();
        chellView.playAnimation(camera);
        newWindow.render();
    }
    delete coordinate;
    delete coordinateRock;
}

void drawChellAndEnergyBall(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    StageView stageView(newWindow, textures, MTP_FACTOR);
    // We'll setup a very basic map, 10x6 blocks.
    std::string metalBlock = "MetalBlock";
    for (int i = 0; i < 10; ++i){
        stageView.addTile(i, 0, metalBlock);
        stageView.addTile(i, 5, metalBlock);
    }
    for (int i = 0; i < 6; ++i){
        stageView.addTile(0, i, metalBlock);
        stageView.addTile(9, i, metalBlock);
    }

    // Box2D Stuff.

    int stageWidth = 10;
    int stageHeight = 6;
    Stage stage(stageWidth, stageHeight);
    // Stage Chell
    float xPos = 1;
    float yPos = 1;
    float chellHeight = 2;
    float chellWidth = 1;
    stage.addChell(chellHeight, chellWidth, xPos, yPos);
    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(coordinate);
    // Stage EnergyBall
    int xBall = 8;
    int yBall = 1;
    EnergyBallView energyBallView(newWindow, xBall, yBall, MTP_FACTOR, textures);
    stage.addEnergyBallHorizontal(2, xBall, yBall);
    Coordinate* coordinateEB = new Coordinate(xBall, yBall);
    EnergyBall* energyBall = stage.getEnergyBall(coordinateEB);

    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR, textures);
    // This will be our camera, for now it's just a SDL_Rect
    SDL_Rect camera = {int(xPos), int(yPos), SCREEN_WIDTH, SCREEN_HEIGHT};

    bool quit = false;
    SDL_Event e;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

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
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->stop();
        }
        stage.step();
        // Update EnergyBall position.
        float newEBPosX = energyBall->getHorizontalPosition();
        float newEBPosY = energyBall->getVerticalPosition();
        energyBallView.move(newEBPosX, newEBPosY, LEVEL_HEIGHT);
        // Update Chell position.
        chellView.setState(chell->getState());
        float newChellPosX = chell->getHorizontalPosition();
        float newChellPosY = chell->getVerticalPosition();
        // We move the animated sprite for Chell.
        chellView.move(newChellPosX, newChellPosY, LEVEL_HEIGHT);
        // Gotta update the camera now to center it around Chell.
        chellView.updateCamera(camera, LEVEL_WIDTH, LEVEL_HEIGHT);
        // Time to render!
        newWindow.clear();
        stageView.draw(camera);
        if (!energyBall->isDead()) energyBallView.playAnimation();
        if (!chell->isDead()) chellView.playAnimation(camera);
        newWindow.render();
    }
    delete coordinateEB;
    delete coordinate;
}

void drawChellAndAcidPool(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    std::string metalBlockPath = "resources/blocks/metal-block.png";

    StageView stageView(newWindow, textures, MTP_FACTOR);
    // We'll setup a very basic map, 10x6 blocks.
    std::string metalBlock = "MetalBlock";
    // Box2D Stuff.
    int stageWidth = 20;
    int stageHeight = 6;
    Stage stage(stageWidth, stageHeight);
    // Stage Chell
    float xPos = 1;
    float yPos = 5;
    float chellHeight = 2;
    float chellWidth = 1;

    stage.addChell(chellHeight, chellWidth, xPos, yPos);
    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(coordinate);
    // Stage AcidPool
    float acidPosX = 5;
    float acidPosY = 0.5;
    float acidHeight = 0.5;
    float acidWidth = 3;
    int acidViewPosX = (acidPosX - acidWidth / 2 ) * MTP_FACTOR;
    int acidViewPosY = (acidPosY + acidHeight / 2) * MTP_FACTOR * -1 + LEVEL_HEIGHT;
    stage.addAcid(acidHeight, acidWidth, acidPosX, acidPosY);
    // Acid View.
    AcidView acidView(newWindow, acidViewPosX, acidViewPosY, MTP_FACTOR, textures);

    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR, textures);
    // This will be our camera, for now it's just a SDL_Rect
    SDL_Rect camera = {int(xPos), int(yPos), SCREEN_WIDTH, SCREEN_HEIGHT};

    bool quit = false;
    SDL_Event e;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

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
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->stop();
        }
        stage.step();

        // Update Chell position.
        chellView.setState(chell->getState());
        float newPosX = chell->getHorizontalPosition();
        float newPosY = chell->getVerticalPosition();
        // We move the animated sprite for Chell.
        chellView.move(newPosX, newPosY, LEVEL_HEIGHT);
        // Gotta update the camera now to center it around Chell.
        chellView.updateCamera(camera, LEVEL_WIDTH, LEVEL_HEIGHT);

        newWindow.clear();
        SDL_Rect acidRect = {acidViewPosX, acidViewPosY, int(acidWidth * MTP_FACTOR), int(acidHeight * MTP_FACTOR)};
        SDL_Rect outlineRect = {chellView.getViewPositionX() - camera.x,
                                chellView.getViewPositionY() - camera.y,
                                int(chellWidth * MTP_FACTOR),
                                int(chellHeight * MTP_FACTOR)};
        newWindow.drawRectangle(outlineRect);
        newWindow.drawRectangle(acidRect);
        acidView.playAnimation();
        if (!chell->isDead()) chellView.playAnimation(camera);
        newWindow.render();
    }
    delete coordinate;
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO);
    drawChell();
//    drawChellAndRock();
//    drawChellAndEnergyBall();
//    drawChellAndAcidPool();
}
