
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
    playGame();
}
