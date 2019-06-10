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
#include "PortalView.h"
#include "Camera.h"
#include "AudioSystem.h"
#include "ViewFactory.h"
#include "../json/json.hpp"
#include "ViewManager.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define MTP_FACTOR 100
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

void drawChell(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    ViewFactory viewFactory(MTP_FACTOR);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // Cool space background.
    std::string bgPath = "resources/Backgrounds/NebulaRed.png";
    Sprite background(bgPath, newWindow);
    std::string metalBlock = "MetalBlock";
    // We'll setup a very basic map, 10x6 blocks.
    int stageWidth = 40;
    int stageHeight = 20;
    int levelWidth = stageWidth * MTP_FACTOR;
    int levelHeight = stageHeight * MTP_FACTOR;
    Stage stage(stageWidth, stageHeight); // 1m == 1 block == 100px
    StageView stageView(newWindow, textures, MTP_FACTOR);
    float metalBlockPosX = 0;
    float metalBlockPosY = 0;
    float metalSide = 2;
    for (int i = 0; i < 40; i += 2){
        stage.addMetalBlock(metalSide, metalBlockPosX+i, metalBlockPosY);
        stageView.addTile(metalBlockPosX+i, metalBlockPosY * -1 + stageHeight, metalBlock);
    }
    // Time to add some platforms!
    stage.addMetalBlock(metalSide, metalBlockPosX + 2, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 2, (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 6, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 6, (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 8, metalBlockPosY + 4);
    stageView.addTile(metalBlockPosX + 8, (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 10, metalBlockPosY + 4);
    stageView.addTile(metalBlockPosX + 10, (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 8, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 8, (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 12, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 12, (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 14, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 14, (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 16, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 16, (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 14, metalBlockPosY + 4);
    stageView.addTile(metalBlockPosX + 14, (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 16, metalBlockPosY + 4);
    stageView.addTile(metalBlockPosX + 16, (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 20, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 20, (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 2, metalBlockPosY + 6);
    stageView.addTile(metalBlockPosX + 2, (metalBlockPosY + 6) * -1 + stageHeight, metalBlock);

    // Box2D Chell and stuff.
    float xPos = 4;
    float yPos = 1;
    float chellHeight = CHELL_HEIGHT;
    float chellWidth = CHELL_WIDTH;
    stage.addChell(chellHeight, chellWidth, xPos, yPos);

    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(coordinate);
    //Rock
    size_t rockSide = 1;
    stage.addRock(rockSide, metalBlockPosX + 12, metalBlockPosY+2);

    Coordinate* coordinateRock = new Coordinate(metalBlockPosX + 12, metalBlockPosY + 2);
    Rock* rock = stage.getRock(coordinateRock);

    //Shot in Chell
    float shotWidth = 1;
    float shotHeight = 1;

    Coordinate* target_blue = new Coordinate(metalBlockPosX + 8, metalBlockPosY + 4); //Setting one block to shoot
    stage.addBlueShot(shotHeight, shotWidth, chell, target_blue); //Arbitrary width and height in Shot
    float x_origin_blue = xPos + chellWidth*2 + shotWidth/2;
    float y_origin_blue = yPos + 1;
    BlueShot* blueShot = stage.getBlueShot(new Coordinate(x_origin_blue, y_origin_blue));

    Coordinate* target_orange = new Coordinate(metalBlockPosX + 2, metalBlockPosY + 6);
    stage.addOrangeShot(shotHeight, shotWidth, chell, target_orange);
    float x_origin_orange = xPos - chellWidth*2 - shotWidth/2;
    float y_origin_orange = yPos + 1;
    OrangeShot* orangeShot = stage.getOrangeShot(new Coordinate(x_origin_orange, y_origin_orange));

    // SoundCodeQueue and AudioSystem init.
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);

    View* blueShotView = viewFactory.createView(BULLET_VIEW_CODE, newWindow, soundQueue);
    View* orangeShotView = viewFactory.createView(BULLET_VIEW_CODE, newWindow, soundQueue);
    View* rockView = viewFactory.createView(ROCK_VIEW_CODE, newWindow, soundQueue);

    // ChellView and camera.
    //ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR, soundQueue, textures);
    View* chellView = viewFactory.createView(CHELL_VIEW_CODE, newWindow, soundQueue);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);

    audioSystem.playMusic(BG_SONG_GAME);
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
                if (e.key.keysym.sym == SDLK_w) chell->jump(); //jump}
                if (e.key.keysym.sym == SDLK_m) audioSystem.stopMusic();
                if (e.key.keysym.sym == SDLK_n) audioSystem.playMusic(BG_SONG_GAME);
                if (e.key.keysym.sym == SDLK_f) chell->downloadRock();
                if (e.key.keysym.sym == SDLK_g) chell->grabRock(rock);
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->moveRight();
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) chell->moveLeft();

            // This might become an issue when we actually implement a jump animation.
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) chell->stop();
        }

        stage.step();

        chellView->setState(chell->getState());
        float newPosX = chell->getHorizontalPosition();
        float newPosY = chell->getVerticalPosition();
        // We move the animated sprite for Chell.
        chellView->move(newPosX, newPosY, levelHeight);
        // Gotta update the camera now to center it around Chell.
        int chellCenterPositionX = chellView->getCenterPosX();
        int chellCenterPositionY = chellView->getCenterPosY();
        camera.centerCameraOnPlayer(chellCenterPositionX, chellCenterPositionY);
        const SDL_Rect& cameraRect = camera.getCameraRectangle();

        //Shot position
        if (! blueShot->isDead()) {
            float blueShotX = blueShot->getHorizontalPosition();
            float blueShotY = blueShot->getVerticalPosition();
            blueShotView->move(blueShotX, blueShotY, levelHeight);
        }


        if (! orangeShot->isDead()) {
            float orangeShotX = orangeShot->getHorizontalPosition();
            float orangeShotY = orangeShot->getVerticalPosition();
            orangeShotView->move(orangeShotX, orangeShotY, levelHeight);
        }

        // Get current Rock position and move it.
        float newRockPosX = rock->getHorizontalPosition();
        float newRockPosY = rock->getVerticalPosition();

        rockView->move(newRockPosX, newRockPosY, levelHeight);

        SDL_Rect rockRect = {rockView->getViewPositionX() - cameraRect.x, rockView->getViewPositionY() - cameraRect.y,
                             int(rockSide * MTP_FACTOR), int(rockSide * MTP_FACTOR)};

        SDL_Rect outlineRect = {chellView->getViewPositionX() - cameraRect.x,
                                chellView->getViewPositionY() - cameraRect.y,
                                int(chellWidth * MTP_FACTOR),
                                int(chellHeight * MTP_FACTOR)};
        SDL_Rect* bgRect = NULL;
        newWindow.clear();
        background.draw(bgRect);
        stageView.draw(cameraRect);
        rockView->playAnimation(cameraRect);
        chellView->playAnimation(cameraRect);
        if (!blueShot->isDead()) blueShotView->playAnimation(cameraRect);
        if (!orangeShot->isDead()) orangeShotView->playAnimation(cameraRect);
        //Debug rectangle to see Chell's collision box.
        newWindow.drawRectangle(outlineRect);
        newWindow.drawRectangle(rockRect);
        newWindow.render();
        audioSystem.playSoundEffects();
    }
    delete coordinate;
    delete target_blue;
    delete target_orange;
    delete chellView;
    delete blueShotView;
    delete orangeShotView;
}

void drawChellAndRock(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Box2D Stuff.
    float xPos = 1;
    float yPos = 1;
    float chellHeight = 2;
    float chellWidth = 1;
    int stageWidth = 10;
    int stageHeight = 6;
    int levelWidth = stageWidth * MTP_FACTOR;
    int levelHeight = stageHeight * MTP_FACTOR;
    Stage stage(stageWidth, stageHeight); // 1m == 1 block == 100px
    stage.addChell(chellHeight, chellWidth, xPos, yPos);
    float metalBlockPosX = 4;
    float metalBlockPosY = 1;

    // Add a rock next to the metal block.
    size_t rockSide = 1;
    stage.addRock(rockSide, metalBlockPosX + 3, metalBlockPosY+5);


    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(coordinate);
    // Get the rock object.
    Coordinate* coordinateRock = new Coordinate(metalBlockPosX + 3, metalBlockPosY + 5);
    Rock* rock = stage.getRock(coordinateRock);

    // SoundCodeQueue and AudioSystem init.
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);

    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR, soundQueue, textures);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);
    // RockView.
    RockView rockView(newWindow, metalBlockPosX + 2, metalBlockPosY, MTP_FACTOR, textures);

    audioSystem.playMusic(BG_SONG_GAME);
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
                if (e.key.keysym.sym == SDLK_f) chell->downloadRock();
                if (e.key.keysym.sym == SDLK_g) chell->grabRock(rock);
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
        chellView.move(newPosX, newPosY, levelHeight);
        // Gotta update the camera now to center it around Chell.
        int chellCenterPositionX = chellView.getCenterPosX();
        int chellCenterPositionY = chellView.getCenterPosY();
        camera.centerCameraOnPlayer(chellCenterPositionX, chellCenterPositionY);
        const SDL_Rect& cameraRect = camera.getCameraRectangle();

        // Get current Rock position and move it.
        float newRockPosX = rock->getHorizontalPosition();
        float newRockPosY = rock->getVerticalPosition();

        rockView.move(newRockPosX, newRockPosY, levelHeight);

        SDL_Rect rockRect = {rockView.getViewPositionX(), rockView.getViewPositionY(),
                             int(rockSide * MTP_FACTOR), int(rockSide * MTP_FACTOR)};
        SDL_Rect outlineRect = {chellView.getViewPositionX() - cameraRect.x,
                                chellView.getViewPositionY() - cameraRect.y,
                                int(chellWidth * MTP_FACTOR),
                                int(chellHeight * MTP_FACTOR)};
        newWindow.clear();
        newWindow.drawRectangle(rockRect);
        newWindow.drawRectangle(outlineRect);
        rockView.playAnimation(cameraRect);
        chellView.playAnimation(cameraRect);
        newWindow.render();
        audioSystem.playSoundEffects();
    }
    delete coordinate;
    delete coordinateRock;
}

void drawChellAndEnergyBall(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Box2D Stuff.
    int stageWidth = 10;
    int stageHeight = 6;
    int levelWidth = stageWidth * MTP_FACTOR;
    int levelHeight = stageHeight * MTP_FACTOR;
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
    float energyBallSide = 1;
    stage.addEnergyBallHorizontal(energyBallSide, xBall, yBall);
    Coordinate* coordinateEB = new Coordinate(xBall, yBall);
    EnergyBall* energyBall = stage.getEnergyBall(coordinateEB);

    // SoundCodeQueue and AudioSystem init.
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);
    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR, soundQueue, textures);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);

    audioSystem.playMusic(BG_SONG_GAME);
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
        energyBallView.move(newEBPosX, newEBPosY, levelHeight);
        // Update Chell position.
        chellView.setState(chell->getState());
        float newChellPosX = chell->getHorizontalPosition();
        float newChellPosY = chell->getVerticalPosition();
        // We move the animated sprite for Chell.
        chellView.move(newChellPosX, newChellPosY, levelHeight);
        // Gotta update the camera now to center it around Chell.
        int chellCenterPositionX = chellView.getCenterPosX();
        int chellCenterPositionY = chellView.getCenterPosY();
        camera.centerCameraOnPlayer(chellCenterPositionX, chellCenterPositionY);
        const SDL_Rect& cameraRect = camera.getCameraRectangle();

        SDL_Rect ebRect = {energyBallView.getViewPositionX(), energyBallView.getViewPositionY(),
                           int(energyBallSide * MTP_FACTOR), int(energyBallSide * MTP_FACTOR)};
        SDL_Rect outlineRect = {chellView.getViewPositionX() - cameraRect.x,
                                chellView.getViewPositionY() - cameraRect.y,
                                int(chellWidth * MTP_FACTOR),
                                int(chellHeight * MTP_FACTOR)};
        // Time to render!
        newWindow.clear();
        newWindow.drawRectangle(outlineRect);
        newWindow.drawRectangle(ebRect);
        if (!energyBall->isDead()) energyBallView.playAnimation(cameraRect);
        chellView.playAnimation(cameraRect);
        newWindow.render();
        audioSystem.playSoundEffects();
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
    int levelWidth = stageWidth * MTP_FACTOR;
    int levelHeight = stageHeight * MTP_FACTOR;
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
    int acidViewPosY = (acidPosY + acidHeight / 2) * MTP_FACTOR * -1 + levelHeight;
    stage.addAcid(acidHeight, acidWidth, acidPosX, acidPosY);
    // Acid View.
    AcidView acidView(newWindow, acidViewPosX, acidViewPosY, MTP_FACTOR, textures);

    // SoundCodeQueue and AudioSystem init.
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);

    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR, soundQueue, textures);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);

    audioSystem.playMusic(BG_SONG_GAME);
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
        chellView.move(newPosX, newPosY, levelHeight);
        // Gotta update the camera now to center it around Chell.
        int chellCenterPositionX = chellView.getCenterPosX();
        int chellCenterPositionY = chellView.getCenterPosY();
        camera.centerCameraOnPlayer(chellCenterPositionX, chellCenterPositionY);
        const SDL_Rect& cameraRect = camera.getCameraRectangle();

        newWindow.clear();
        SDL_Rect acidRect = {acidViewPosX - cameraRect.x, acidViewPosY - cameraRect.y,
                             int(acidWidth * MTP_FACTOR), int(acidHeight * MTP_FACTOR)};
        SDL_Rect outlineRect = {chellView.getViewPositionX() - cameraRect.x,
                                chellView.getViewPositionY() - cameraRect.y,
                                int(chellWidth * MTP_FACTOR),
                                int(chellHeight * MTP_FACTOR)};
        newWindow.drawRectangle(outlineRect);
        newWindow.drawRectangle(acidRect);
        acidView.playAnimation(cameraRect);
        chellView.playAnimation(cameraRect);
        newWindow.render();
        audioSystem.playSoundEffects();
    }
    delete coordinate;
}

void jsonTest() {
    // Initial json sent by the server with information about the entities.
    // We'll need an additional one to populate StageView too.
    nlohmann::json mapData = {
            {
                "Chell1",
                {
                    {"type", CHELL_VIEW_CODE}, {"state", 0}, {"x", 4} ,{"y", 1}
                }
            },
            {
                "Rock1",
                {
                    {"type", ROCK_VIEW_CODE}, {"x", 8}, {"y", 1}
                }
            }
    };
    // This is what an update JSON looks like, sent from the server to the clients.
    nlohmann::json stageUpdateRequest = {
            {
                    "Chell1",
                    {
                        {"state", 0}, {"x", 4} ,{"y", 1}
                    }
            },
            {
                    "Rock1",
                    {
                            {"state", 0}, {"x", 8}, {"y", 1}
                    }
            }
    };

    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);
    std::string title = "Portal";
    std::string playerID = "Chell1";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    int levelWidth = 1000;
    int levelHeight = 1000;
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);
    ViewManager viewManager(newWindow, levelHeight, MTP_FACTOR, playerID, mapData, soundQueue);


    bool quit = false;
    SDL_Event e;
    
    audioSystem.playMusic(BG_SONG_GAME);
    while(!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        newWindow.clear();
        viewManager.showAndUpdateViews(stageUpdateRequest, camera);
        newWindow.render();
    }
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
//    drawChell();
//    drawChellAndRock();
//    drawChellAndEnergyBall();
//    drawChellAndAcidPool();
    jsonTest();
}
