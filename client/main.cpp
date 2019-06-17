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
#include "../common/constants.h"
#include "Camera.h"
#include "AudioSystem.h"
#include "../json/json.hpp"
#include "ViewManager.h"
#include "../common/UserEvent.h"
#include "../common/UserEventQueue.h"
#include "UserEventHandler.h"
#include "../common/Socket.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MTP_FACTOR 100
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

void playGame(std::string& idChell) {
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    float xPosChell = 4;
    float yPosChell = 1;
    //std::string idChell = "Chell1";
    float xPosRock = 8;
    float yPosRock = 1;
    std::string idRock = "Rock1";
    float xPosCake = 2;
    float yPosCake = yPosChell + 12.5;

    float xPosAcid = 12;
    float yPosAcid = 1;
    std::string idAcid = "Acid1";

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
                    "Chell2",
                    {
                            {"type", CHELL_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }

            },
            {
                    "Cake",
                    {
                            {"type", CAKE_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosCake},
                            {"y", yPosCake}
                    }
            },{
                    "BlueShot1",
                    {
                            {"type", BULLET_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },{
                    "OrangeShot1",
                    {
                            {"type", BULLET_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },{
                    "BluePortal1",
                    {
                            {"type", BLUE_PORTAL_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },{
                    "OrangePortal1",
                    {
                            {"type", ORANGE_PORTAL_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },{
                    "BlueShot2",
                    {
                            {"type", BULLET_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },{
                    "OrangeShot2",
                    {
                            {"type", BULLET_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },{
                    "BluePortal2",
                    {
                            {"type", BLUE_PORTAL_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },{
                    "OrangePortal2",
                    {
                            {"type", ORANGE_PORTAL_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell} ,
                            {"y", yPosChell}
                    }
            },{
                    "Rock1",
                    {
                            {"type", ROCK_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosRock},
                            {"y", yPosRock}
                    }
            },{
                    "Acid1",
                    {
                            {"type", ACID_VIEW_CODE},
                            {"state", 0},
                            {"x", xPosAcid},
                            {"y", yPosAcid}
                    }
            },{
                    "EnergyBall1",
                    {
                            {"type", ENERGY_BALL__VIEW_CODE},
                            {"state", 0},
                            {"x", xPosChell},
                            {"y", yPosChell}
                    }
            },

    };
    nlohmann::json stageUpdateRequest;

    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);
    std::string title = "Portal";
    //std::string playerID = "Chell1";
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

    /* stage.addRock(idRock, ROCK_HEIGHT,
                   xPosRock, yPosRock);*/
    /* stage.addRock("Rock2", ROCK_HEIGHT,
                   xPosRock + 2, yPosRock);*/

    float metalBlockPosX = 0;
    float metalBlockPosY = 0;
    float metalSide = METAL_SIDE;
    for (int i = 0; i < 40; i += 2){
        stageView.addTile(metalBlockPosX+i,
                          metalBlockPosY * -1 + stageHeight, metalBlock);
    }
    std::string bb = "RockBlock";
    std::string id_et = "EnergyTransmitter1";
    std::string et = "LounchBlockUp";

    stageView.addTile(8,
                      (2) * -1 + stageHeight, et);

    // Time to add some platforms!
    stageView.addTile(metalBlockPosX + 2,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stageView.addTile(metalBlockPosX + 6,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stageView.addTile(metalBlockPosX + 8,
                      (metalBlockPosY + 6) * -1 + stageHeight, metalBlock);

    stageView.addTile(metalBlockPosX + 8,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);
    stageView.addTile(metalBlockPosX + 12,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stageView.addTile(metalBlockPosX + 14,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);
    stageView.addTile(metalBlockPosX + 16,
                      (metalBlockPosY + 12) * -1 + stageHeight, metalBlock);

    stageView.addTile(metalBlockPosX + 14,
                      (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);
    stageView.addTile(metalBlockPosX + 16,
                      (metalBlockPosY + 4) * -1 + stageHeight, metalBlock);

    stageView.addTile(metalBlockPosX + 20,
                      (metalBlockPosY + 8) * -1 + stageHeight, metalBlock);
    stageView.addTile(metalBlockPosX + 2,
                      (metalBlockPosY + 6) * -1 + stageHeight, metalBlock);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);

    ViewManager viewManager(newWindow, levelHeight,
                            MTP_FACTOR, idChell, objectsData, soundQueue);


    UserEventQueue userEventQueue;
    UserEventHandler userEventHandler(camera, userEventQueue,
                                      idChell, levelHeight,
                                      soundQueue);
    //StageStatusQueue stageStatusQueue;

    std::string host = "localhost";
    std::string service = "8000";

    Socket clientSocket;
    int status = clientSocket.connectToHost(host, service);
    if (status == -1){
        std::cout << "Fallo la conexion" << std::endl;
    } else {
        std::cout << "Estamos conectados!" << std::endl;
    }

    bool quit = false;
    SDL_Event e;
    //audioSystem.playMusic(BG_SONG_GAME);
    const SDL_Rect& cameraRect = camera.getCameraRectangle();
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            userEventHandler.run(e);
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (!userEventQueue.empty()) {
                UserEvent userEvent = userEventQueue.pop();
                std::string userJson = userEvent.toJsonString();
                int request_size = userJson.size();
                clientSocket.sendMessage(&request_size, REQUEST_LEN_SIZE);
                clientSocket.sendMessage(&userJson[0], request_size);
            }
        }
        int stageStatusSize;
        clientSocket.receiveMessage(&stageStatusSize, REQUEST_LEN_SIZE);
        std::string stageStatusString(stageStatusSize, '\0');
        clientSocket.receiveMessage(&stageStatusString[0], stageStatusSize);
        stageUpdateRequest = nlohmann::json::parse(stageStatusString);

        SDL_Delay(1000/60);
        newWindow.clear();
        SDL_Rect* bgRect = nullptr;
        background.draw(bgRect);
        stageView.draw(cameraRect);
        viewManager.showAndUpdateViews(stageUpdateRequest, camera);
        newWindow.render();
        audioSystem.playSoundEffects();
    }
    clientSocket.shutdownAndClose();
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (argc < 2) {
        std::cout << "Falta el id del cliente\n";
    }
    std::string playerID = argv[1];
    playGame(playerID);
}
