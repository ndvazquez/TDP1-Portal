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
#include "EventSender.h"
#include "../common/StageStatusQueue.h"
#include "StageStatusReceiver.h"

// It's recommended to use multiples of the MTP_FACTOR to get a smooth
// experience.
#define SCREEN_WIDTH 1050
#define SCREEN_HEIGHT 700
#define MTP_FACTOR 70
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

void playGame(std::string& idChell) {
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);

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

    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);

    UserEventQueue userEventQueue;
    UserEventHandler userEventHandler(camera, userEventQueue,
                                      idChell, levelHeight,
                                      soundQueue);
    StageStatusQueue stageStatusQueue;

    std::string host = "localhost";
    std::string service = "8000";

    Socket clientSocket;
    int status = clientSocket.connectToHost(host, service);
    if (status == -1){
        std::cout << "Fallo la conexion" << std::endl;
    } else {
        std::cout << "Estamos conectados!" << std::endl;
    }

    EventSender eventSender(clientSocket, userEventQueue);
    StageStatusReceiver stageStatusReceiver(clientSocket, stageStatusQueue);

    // Here we'll receive two jsons with the data of the map to be played.
    // First one is for static objects without state.
    int jsonSOsize;
    clientSocket.receiveMessage(&jsonSOsize, REQUEST_LEN_SIZE);
    std::string jsonStaticObjects(jsonSOsize, '\0');
    clientSocket.receiveMessage(&jsonStaticObjects[0], jsonSOsize);
    // Second one is for objects with state.
    int jsonDOsize;
    clientSocket.receiveMessage(&jsonDOsize, REQUEST_LEN_SIZE);
    std::string jsonDynamicObjects(jsonDOsize, '\0');
    clientSocket.receiveMessage(&jsonDynamicObjects[0], jsonDOsize);
    //
    nlohmann::json staticObjects = nlohmann::json::parse(jsonStaticObjects);
    nlohmann::json dynamicObjects = nlohmann::json::parse(jsonDynamicObjects);

    StageView stageView(newWindow, textures, MTP_FACTOR, staticObjects, stageHeight);
    ViewManager viewManager(newWindow, levelHeight,
                            MTP_FACTOR, idChell, dynamicObjects, soundQueue);
    audioSystem.playMusic(BG_SONG_GAME);
    userEventHandler.start();
    eventSender.start();
    stageStatusReceiver.start();
    
    nlohmann::json stageUpdateRequest = "{}"_json;
    const SDL_Rect& cameraRect = camera.getCameraRectangle();
    bool quit = false;
    while (!quit) {
        // This isn't optimal but it'll do for now.
        if (!stageStatusQueue.empty()) {
            std::string stageStatusString = stageStatusQueue.pop();
            stageUpdateRequest = nlohmann::json::parse(stageStatusString);
        }

        // Time to draw!
        newWindow.clear();
        SDL_Rect* bgRect = nullptr;
        background.draw(bgRect);
        stageView.draw(cameraRect);
        viewManager.showAndUpdateViews(stageUpdateRequest, camera);
        newWindow.render();
        audioSystem.playSoundEffects();
        if (userEventHandler.isDead()) quit = true;
    }
    
    clientSocket.shutdownAndClose();
    userEventHandler.stop();
    userEventHandler.join();
    eventSender.stop();
    eventSender.join();
    stageStatusReceiver.stop();
    stageStatusReceiver.join();
    
    
}

int main(int argc, char* argv[]){
    SDLSession sdlSession(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (argc < 2) {
        std::cout << "Falta el id del cliente\n";
    }
    std::string playerID = argv[1];
    playGame(playerID);
}
