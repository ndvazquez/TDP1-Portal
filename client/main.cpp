///
// Created by ndv on 5/5/19.
//
#include "../common/Window.h"
#include "../common/Sprite.h"
#include "StageView.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "../common/SDLSession.h"
#include <yaml-cpp/yaml.h>
#include <Stage.h>
#include <StageManager.h>
#include "../common/constants.h"
#include "Camera.h"
#include "AudioSystem.h"
#include "../json/json.hpp"
#include "ViewManager.h"
#include "../common/UserEvent.h"
#include "../common/UserEventQueue.h"
#include "UserEventHandler.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define MTP_FACTOR 100
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

void playGame() {
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    float xPosChell = 4;
    float yPosChell = 1;
    std::string idChell = "Chell1";
    float xPosRock = 8;
    float yPosRock = 1;
    std::string idRock = "Rock1";
    float xPosCake = 2;
    float yPosCake = yPosChell + 12.5;

    nlohmann::json objectsData = {
            {
                    "Chell1",
                    {
                            {"type", CHELL_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }

            },{
                    "Cake",
                    {
                            {"type", CAKE_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosCake} ,
                            {"y", yPosCake}
                    }
            },{
                    "Rock1",
                    {
                            {"type", ROCK_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosRock} ,
                            {"y", yPosRock}
                    }
            },{
                    "Rock2",
                    {
                            {"type", ROCK_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosRock + 2},
                            {"y", yPosRock}
                    }
            },

    };
    nlohmann::json stageUpdateRequest;

    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);
    std::string title = "Portal";
    std::string playerID = "Chell1";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // Cool space background.
    std::string bgPath = "resources/Backgrounds/NebulaRed.png";
    Sprite background(bgPath, newWindow);
    std::string metalBlock = "MetalBlock";
    int stageWidth = 40;
    int stageHeight = 20;
    int levelWidth = stageWidth * MTP_FACTOR;
    int levelHeight = stageHeight * MTP_FACTOR;

    StageView stageView(newWindow, textures, MTP_FACTOR);
    Stage stage(stageWidth, stageHeight);
    stage.addChell(idChell, CHELL_HEIGHT, CHELL_WIDTH,
            xPosChell, yPosChell);
    stage.addCake(1, xPosCake, yPosCake);
    stage.addRock(idRock, ROCK_HEIGHT,
            xPosRock, yPosRock);
    stage.addRock("Rock2", ROCK_HEIGHT,
            xPosRock + 2, yPosRock);

    float metalBlockPosX = 0;
    float metalBlockPosY = 0;
    float metalSide = 2;
    for (int i = 0; i < 40; i += 2){
        stage.addMetalBlock(metalSide, metalBlockPosX+i, metalBlockPosY);
        stageView.addTile(metalBlockPosX+i,
                          metalBlockPosY * -1 + stageHeight, metalBlock);
    }
    // Time to add some platforms!
<<<<<<< HEAD
    stage.addMetalBlock(metalSide, metalBlockPosX + 2, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 2,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 6, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 6,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 8, metalBlockPosY + 6);
    stageView.addTile(metalBlockPosX + 8,
                      (metalBlockPosY + 6) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 8, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 8,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 12, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 12,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 14, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 14,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 16, metalBlockPosY + 12);
    stageView.addTile(metalBlockPosX + 16,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 14, metalBlockPosY + 4);
    stageView.addTile(metalBlockPosX + 14,
                      (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 16, metalBlockPosY + 4);
    stageView.addTile(metalBlockPosX + 16,
                      (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);

    stage.addMetalBlock(metalSide, metalBlockPosX + 20, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 20,
                      (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);
    stage.addMetalBlock(metalSide, metalBlockPosX + 2, metalBlockPosY + 6);
    stageView.addTile(metalBlockPosX + 2,
                      (metalBlockPosY + 6) * -1 + stageHeight, metalBlock);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);

    ViewManager viewManager(newWindow, levelHeight,
            MTP_FACTOR, playerID, objectsData, soundQueue);
=======
    stage.addMetalBlock(metalSide, metalBlockPosX + 8, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 8,
                      (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);


    stage.addMetalBlock(metalSide, metalBlockPosX + 2, metalBlockPosY + 8);
    stageView.addTile(metalBlockPosX + 2,
                      (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);

    // Box2D Chell and stuff.
    std::string chell_id = "Chell1";
    std::string button_id = "Button1";
    float xPos = 4;
    float yPos = 1;
    float chellHeight = CHELL_HEIGHT;
    float chellWidth = CHELL_WIDTH;
    stage.addChell(chell_id, chellHeight, chellWidth, xPos, yPos);
    stage.addButton(button_id, 1, 1, metalBlockPosX + 2, metalBlockPosY + 2);
    Button* button = stage.getButton(button_id);

    std::unordered_map<std::string, Button*> buttons;
    buttons.insert({button_id, button});

    stage.addGate(chell_id, 3, 1, metalBlockPosX + 5, 2, buttons, "Button1");
    Gate* gate = stage.getGate(chell_id);

    float xCake = 2;
    float yCake = yPos + 12.5;
    stage.addCake(1, xCake, yCake);
    Cake* cake = stage.getCake();

    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(chell_id);
    //Rock
    std::string rock_id = "Rock1";
    size_t rockSide = 1;
    stage.addRock(rock_id, rockSide, metalBlockPosX + 12, metalBlockPosY+2);

    Rock* rock = stage.getRock(rock_id);

    /*
    //Shot in Chell
    std::string blue_shot_id = "BlueShot1";
    std::string orange_shot_id = "OrangeShot1";
    float shotWidth = 1;
    float shotHeight = 1;
    //Setting one block to shoot
    Coordinate* target_blue = new Coordinate(metalBlockPosX + 8,
                                             metalBlockPosY + 8);
    stage.addBlueShot(blue_shot_id, shotHeight, shotWidth,
                      chell, target_blue); //Arbitrary width and height in Shot
    BlueShot* blueShot = stage.getBlueShot(blue_shot_id);

    Coordinate* target_orange = new Coordinate(metalBlockPosX + 2,
                                               metalBlockPosY + 8);
    stage.addOrangeShot(orange_shot_id, shotHeight,
                        shotWidth, chell, target_orange);
    OrangeShot* orangeShot = stage.getOrangeShot(orange_shot_id);*/

    // SoundCodeQueue and AudioSystem init.
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);

    /*View* blueShotView = viewFactory.createView(BULLET_VIEW_CODE,
                                                newWindow, soundQueue);
    View* orangeShotView = viewFactory.createView(BULLET_VIEW_CODE,
                                                  newWindow, soundQueue);*/
    View* rockView = viewFactory.createView(ROCK_VIEW_CODE,
                                            newWindow, soundQueue);
    View* cakeView = viewFactory.createView(CAKE_VIEW_CODE,
                                            newWindow, soundQueue);

    // ChellView and camera.
    View* chellView = viewFactory.createView(CHELL_VIEW_CODE,
                                             newWindow, soundQueue);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);

    //audioSystem.playMusic(BG_SONG_GAME);
    bool quit = false;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // This should be done server side,
            // but we'll do the event handling here for now.
            if (e.type  == SDL_KEYDOWN  && e.key.repeat == 0) {
                if (e.key.keysym.sym == SDLK_w) chell->jump(); //jump}
                if (e.key.keysym.sym == SDLK_m) audioSystem.stopMusic();
                if (e.key.keysym.sym == SDLK_n) {
                    audioSystem.playMusic(BG_SONG_GAME);
                }
                if (e.key.keysym.sym == SDLK_f) chell->downloadRock();
                if (e.key.keysym.sym == SDLK_g) chell->grabRock(rock);
                if (e.key.keysym.sym == SDLK_t) chell->releaseRock();
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
                chell->moveRight();
            }
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
                chell->moveLeft();
            }

            // This might become an issue
            // when we actually implement a jump animation.
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
                chell->stop();
            }
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
        camera.centerCameraOnPlayer(chellCenterPositionX,
                                    chellCenterPositionY);
        const SDL_Rect& cameraRect = camera.getCameraRectangle();


        /*
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
        }*/

        // Get current Rock position and move it.
        float newRockPosX = rock->getHorizontalPosition();
        float newRockPosY = rock->getVerticalPosition();
        rockView->move(newRockPosX, newRockPosY, levelHeight);

        // Get cake position and "move it".
        float cakePosX = cake->getHorizontalPosition();
        float cakePosY = cake->getVerticalPosition();
        cakeView->move(cakePosX, cakePosY, levelHeight);

        SDL_Rect cakeRect = {cakeView->getViewPositionX() - cameraRect.x,
                             cakeView->getViewPositionY() - cameraRect.y,
                             MTP_FACTOR,
                             MTP_FACTOR};

        SDL_Rect rockRect = {rockView->getViewPositionX() - cameraRect.x,
                             rockView->getViewPositionY() - cameraRect.y,
                             int(rockSide * MTP_FACTOR),
                             int(rockSide * MTP_FACTOR)};

        SDL_Rect outlineRect = {chellView->getViewPositionX() - cameraRect.x,
                                chellView->getViewPositionY() - cameraRect.y,
                                int(chellWidth * MTP_FACTOR),
                                int(chellHeight * MTP_FACTOR)};
        SDL_Rect* bgRect = NULL;
        newWindow.clear();
        background.draw(bgRect);
        stageView.draw(cameraRect);
        cakeView->playAnimation(cameraRect);
        chellView->playAnimation(cameraRect);
        //if (!blueShot->isDead()) blueShotView->playAnimation(cameraRect);
        //if (!orangeShot->isDead()) orangeShotView->playAnimation(cameraRect);
        if (!rock->isDead()) rockView->playAnimation(cameraRect);
        //Debug rectangle to see Chell's collision box.
        newWindow.drawRectangle(outlineRect);
        newWindow.drawRectangle(rockRect);
        newWindow.drawRectangle(cakeRect);
        newWindow.render();
        audioSystem.playSoundEffects();

        GateState gateState = gate->getState();
        if (gateState == OPEN) std::cout << "La puerta esta abierta" << std::endl;
        else std::cout << "La puerta esta cerrada" << std::endl;

        ButtonState buttonState = button->getState();
        if (buttonState == ON) std::cout << "El boton esta activado" << std::endl;
        else std::cout << "El boton esta cerrado" << std::endl;

    }
    delete coordinate;
   // delete target_blue;
    //delete target_orange;
    delete chellView;
    //delete blueShotView;
    //delete orangeShotView;
}

void drawChellAndRock(){
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    std::string title = "Portal";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Box2D Stuff.
    std::string chell_id = "Chell1";
    float xPos = 1;
    float yPos = 1;
    float chellHeight = 2;
    float chellWidth = 1;
    int stageWidth = 10;
    int stageHeight = 6;
    int levelWidth = stageWidth * MTP_FACTOR;
    int levelHeight = stageHeight * MTP_FACTOR;
    Stage stage(stageWidth, stageHeight); // 1m == 1 block == 100px
    stage.addChell(chell_id, chellHeight, chellWidth, xPos, yPos);
    float metalBlockPosX = 4;
    float metalBlockPosY = 1;

    // Add a rock next to the metal block.
    std::string rock_id = "Rock1";
    size_t rockSide = 1;
    stage.addRock(rock_id, rockSide, metalBlockPosX + 3, metalBlockPosY+5);

    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(chell_id);
    // Get the rock object.
    Coordinate* coordinateRock = new Coordinate(metalBlockPosX + 3,
                                                metalBlockPosY + 5);
    Rock* rock = stage.getRock(rock_id);

    // SoundCodeQueue and AudioSystem init.
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);

    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos,
                        MTP_FACTOR, soundQueue, textures);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);
    // RockView.
    RockView rockView(newWindow, metalBlockPosX + 2,
                      metalBlockPosY, MTP_FACTOR, textures);

    audioSystem.playMusic(BG_SONG_GAME);
    bool quit = false;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // This should be done server side,
            // but we'll do the event handling here for now.
            if (e.type  == SDL_KEYDOWN  && e.key.repeat == 0) {
                if (e.key.keysym.sym == SDLK_w) chell->jump(); //jump
                if (e.key.keysym.sym == SDLK_f) chell->downloadRock();
                if (e.key.keysym.sym == SDLK_g) chell->grabRock(rock);
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
                chell->moveRight();
            }
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
                chell->moveLeft();
            }
            // This might become an issue when
            // we actually implement a jump animation.
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
                chell->stop();
            }
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
        camera.centerCameraOnPlayer(chellCenterPositionX,
                                    chellCenterPositionY);
        const SDL_Rect& cameraRect = camera.getCameraRectangle();

        // Get current Rock position and move it.
        float newRockPosX = rock->getHorizontalPosition();
        float newRockPosY = rock->getVerticalPosition();

        rockView.move(newRockPosX, newRockPosY, levelHeight);

        SDL_Rect rockRect = {rockView.getViewPositionX(),
                             rockView.getViewPositionY(),
                             int(rockSide * MTP_FACTOR),
                             int(rockSide * MTP_FACTOR)};
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
    std::string chell_id = "Chell1";
    float xPos = 1;
    float yPos = 1;
    float chellHeight = 2;
    float chellWidth = 1;
    stage.addChell(chell_id, chellHeight, chellWidth, xPos, yPos);
    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(chell_id);
    // Stage EnergyBall
    std::string eb_id = "EnergyBall1";
    int xBall = 8;
    int yBall = 1;
    EnergyBallView energyBallView(newWindow, xBall, yBall,
                                  MTP_FACTOR, textures);
    float energyBallSide = 1;
    stage.addEnergyBallHorizontal(eb_id, energyBallSide, xBall, yBall);
    Coordinate* coordinateEB = new Coordinate(xBall, yBall);
    EnergyBall* energyBall = stage.getEnergyBall(eb_id);

    // SoundCodeQueue and AudioSystem init.
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);
    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos, MTP_FACTOR,
                        soundQueue, textures);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT,
                  levelWidth, levelHeight);

    audioSystem.playMusic(BG_SONG_GAME);
    bool quit = false;
    SDL_Event e;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // This should be done server side,
            // but we'll do the event handling here for now.
            if (e.type  == SDL_KEYDOWN  && e.key.repeat == 0) {
                if (e.key.keysym.sym == SDLK_w) chell->jump(); //jump
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
                chell->moveRight();
            }
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
                chell->moveLeft();
            }
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
                chell->stop();
            }
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
        camera.centerCameraOnPlayer(chellCenterPositionX,
                                    chellCenterPositionY);
        const SDL_Rect& cameraRect = camera.getCameraRectangle();

        SDL_Rect ebRect = {energyBallView.getViewPositionX(),
                           energyBallView.getViewPositionY(),
                           int(energyBallSide * MTP_FACTOR),
                           int(energyBallSide * MTP_FACTOR)};
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
    std::string chell_id = "Chell1";
    float xPos = 1;
    float yPos = 2;
    float chellHeight = 2;
    float chellWidth = 1;

    stage.addChell(chell_id, chellHeight, chellWidth, xPos, yPos);
    Coordinate* coordinate = new Coordinate(xPos, yPos);
    Chell* chell = stage.getChell(chell_id);
    // Stage AcidPool
    std::string acid_id = "Acid1";
    float acidPosX = 5;
    float acidPosY = 0.5;
    float acidHeight = 0.5;
    float acidWidth = 3;
    int acidViewPosX = (acidPosX - acidWidth / 2) * MTP_FACTOR;
    int acidViewPosY = (acidPosY + acidHeight / 2) * MTP_FACTOR * -1 +
                       levelHeight;
    stage.addAcid(acid_id, acidHeight, acidWidth, acidPosX, acidPosY);
    // Acid View.
    AcidView acidView(newWindow, acidViewPosX, acidViewPosY,
                      MTP_FACTOR, textures);

    // SoundCodeQueue and AudioSystem init.
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);

    // ChellView and camera.
    ChellView chellView(newWindow, xPos, yPos,
                        MTP_FACTOR, soundQueue, textures);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT,
                  levelWidth, levelHeight);

    audioSystem.playMusic(BG_SONG_GAME);
    bool quit = false;
    SDL_Event e;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // This should be done server side,
            // but we'll do the event handling here for now.
            if (e.type  == SDL_KEYDOWN  && e.key.repeat == 0) {
                if (e.key.keysym.sym == SDLK_w) chell->jump(); //jump
            }
            if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
                chell->moveRight();
            }
            if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
                chell->moveLeft();
            }
            if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
                chell->stop();
            }
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
        camera.centerCameraOnPlayer(chellCenterPositionX,
                                    chellCenterPositionY);
        const SDL_Rect& cameraRect = camera.getCameraRectangle();

        newWindow.clear();
        SDL_Rect acidRect = {acidViewPosX - cameraRect.x,
                             acidViewPosY - cameraRect.y,
                             int(acidWidth * MTP_FACTOR),
                             int(acidHeight * MTP_FACTOR)};
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


    float xPosChell = 4;
    float yPosChell = 1;
    std::string idChell = "Chell1";
    float xPosRock = 8;
    float yPosRock = 1;
    std::string idRock = "Rock1";

    nlohmann::json mapData = {
            {
                    "Chell1",
                    {
                            {"type", CHELL_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },
    };
    // This is what an update JSON looks like,
    // sent from the server to the clients.
    nlohmann::json stageUpdateRequest;
    /*= {
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
    };*/




    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);
    std::string title = "Portal";
    std::string playerID = "Chell1";
    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    int stageWidth = 60;
    int stageHeight = 6;
    int levelWidth = stageWidth * MTP_FACTOR;
    int levelHeight = stageHeight * MTP_FACTOR;

    Stage stage(stageWidth, stageHeight);
    stage.addChell(idChell, 2, 1, xPosChell, yPosChell);
    Chell* chell = stage.getChell(idChell);

    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);
    ViewManager viewManager(newWindow, levelHeight,
                            MTP_FACTOR, playerID, mapData, soundQueue);
>>>>>>> f289a085db3cf84f6a69b8b5ceac0813a26a9b27


    UserEventQueue userEventQueue;
    UserEventHandler userEventHandler(camera, userEventQueue,
            idChell, levelHeight);
    // We share the same queue for now, but once we start to use sockets,
    // we'll use different queues;
    StageManager stageManager(stage, userEventQueue);
    bool quit = false;
    SDL_Event e;
    audioSystem.playMusic(BG_SONG_GAME);
    const SDL_Rect& cameraRect = camera.getCameraRectangle();
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            userEventHandler.run(e);
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
        stageManager.run();
        stageUpdateRequest = stage.getCurrentState();
        newWindow.clear();
        SDL_Rect* bgRect = nullptr;
        background.draw(bgRect);
        stageView.draw(cameraRect);
        viewManager.showAndUpdateViews(stageUpdateRequest, camera);
        newWindow.render();
        audioSystem.playSoundEffects();
    }
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
<<<<<<< HEAD
    playGame();
}
=======
    drawChell();
    //drawChellAndRock();
    //drawChellAndEnergyBall();
    //drawChellAndAcidPool();
    //jsonTest();
}
>>>>>>> f289a085db3cf84f6a69b8b5ceac0813a26a9b27
