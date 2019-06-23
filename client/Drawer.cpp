//
// Created by cecix on 22/06/19.
//

#include <audio/SoundCodeQueue.h>
#include <audio/AudioSystem.h>
#include <communication-support/UserEventHandler.h>
#include <communication-support/EventSender.h>
#include <communication-support/StageStatusReceiver.h>
#include "Drawer.h"
#include "../common/Window.h"
#include "../common/Sprite.h"
#include "../editor/Editor.h"
#include "views/Camera.h"
#include "../common/UserEventQueue.h"
#include "../common/StageStatusQueue.h"
#include "views/ViewManager.h"
#include <yaml-cpp/node/node.h>

// It's recommended to use multiples of the MTP_FACTOR to get a smooth
// experience.
#define SCREEN_WIDTH 1050
#define SCREEN_HEIGHT 700
#define MTP_FACTOR 70
#define TEXTURE_CONFIG_FILE "config/textures.yaml"

Drawer::Drawer(Protocol &clientProtocol, Socket &clientSocket):
    clientProtocol(clientProtocol), clientSocket(clientSocket) {
}

void Drawer::draw(std::string& idChell) {
    YAML::Node textures = YAML::LoadFile(TEXTURE_CONFIG_FILE);
    SoundCodeQueue soundQueue;
    AudioSystem audioSystem(soundQueue);
    std::string title = "Portal";

    Window newWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // Cool space background.
    std::string bgPath = "resources/Backgrounds/NebulaRed.png";
    Sprite background(bgPath, newWindow);
    std::string metalBlock = "MetalBlock";

    //Here we'll receive the metadata
    std::string jsonMetadata = clientProtocol.receiveMessage();
    nlohmann::json metadata = nlohmann::json::parse(jsonMetadata);

    float stageWidth = metadata["stage"]["width"].get<float>();
    float stageHeight = metadata["stage"]["height"].get<float>();

    int levelWidth = stageWidth * MTP_FACTOR;
    int levelHeight = stageHeight * MTP_FACTOR;

    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, levelWidth, levelHeight);

    UserEventQueue userEventQueue;
    UserEventHandler userEventHandler(camera, userEventQueue,
                                      idChell, levelHeight,
                                      soundQueue);
    StageStatusQueue stageStatusQueue;

    EventSender eventSender(clientSocket, userEventQueue);
    StageStatusReceiver stageStatusReceiver(clientSocket, stageStatusQueue);

    // Here we'll receive two jsons with the data of the map to be played.
    // First one is for static objects without state.
    std::string jsonStaticObjects = clientProtocol.receiveMessage();

    // Second one is for objects with state.
    std::string jsonDynamicObjects = clientProtocol.receiveMessage();

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
        if (!stageStatusQueue.empty()) {
            std::string stageStatusString = stageStatusQueue.pop();
            stageUpdateRequest = nlohmann::json::parse(stageStatusString);
        }
        if (userEventHandler.isDead() || stageStatusReceiver.isDead()
            || eventSender.isDead()) {
            quit = true;
        }
        // Time to draw!
        newWindow.clear();
        SDL_Rect* bgRect = nullptr;
        background.draw(bgRect);
        stageView.draw(cameraRect);
        viewManager.showAndUpdateViews(stageUpdateRequest, camera);
        newWindow.render();
        audioSystem.playSoundEffects();

    }
    UserEvent eventSenderSuicidePill = UserEvent(idChell, USER_QUIT_CODE, 0, 0);
    userEventQueue.push(eventSenderSuicidePill);

    clientSocket.shutdownAndClose();
    userEventHandler.stop();
    userEventHandler.join();
    eventSender.stop();
    eventSender.join();
    stageStatusReceiver.stop();
    stageStatusReceiver.join();
}
