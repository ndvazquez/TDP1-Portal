//
// Created by ndv on 6/9/19.
//

#include "ViewManager.h"
#include "ViewFactory.h"
#include "../../json/json.hpp"
#include <iostream>
#include <string>

ViewManager::ViewManager(Window& window,
        int levelHeight,
        int factor,
        std::string& playerID,
        nlohmann::json& objectsData,
        SoundCodeQueue& soundCodeQueue,
        nlohmann::json& metadata)
        : gameWindow(window),
        levelHeight(levelHeight),
        mtpFactor(factor),
        playerID(playerID) {
    ViewFactory viewFactory(mtpFactor);
    for (const auto& item : objectsData.items()){
        nlohmann::json& data = item.value();
        int viewTypeCode = data["type"].get<int>();
        View* newView = viewFactory.createView(viewTypeCode,
                gameWindow,
                soundCodeQueue);
        float xPos = data["x"].get<float>();
        float yPos = data["y"].get<float>();
        newView->move(xPos, yPos, levelHeight);
        const std::string& viewName = item.key();
        if (viewName.find(PLAYER_ID_PREFIX) != std::string::npos) {
            std::string playerName = metadata["playerNames"][viewName].get<std::string>();
            OutputText* playerNameText = new OutputText(gameWindow, playerName.c_str());
            playerNames.insert({viewName, playerNameText});
        }
        views.insert({viewName, newView});

    }
}

ViewManager::~ViewManager() {
    for (auto it = views.begin(); it != views.end(); ++it){
        delete it->second;
    }
    for (auto it = playerNames.begin(); it != playerNames.end(); ++it){
        delete it->second;
    }
}

void ViewManager::showAndUpdateViews(nlohmann::json &objectsData,
        Camera& camera) {
    const SDL_Rect& cameraRect = camera.getCameraRectangle();
    for (const auto& item : objectsData.items()) {
        const std::string& objectID = item.key();
        auto it = views.find(objectID);
        if (it == views.end()){
            continue;
        }
        View* view = it->second;
        float newPosX = item.value()["x"].get<float>();
        float newPosY = item.value()["y"].get<float>();
        view->move(newPosX, newPosY, levelHeight);
        int newState = item.value()["state"].get<int>();
        view->setState(newState);
        if (objectID == playerID){
            int playerPosX = view->getCenterPosX();
            int playerPosY = view->getCenterPosY();
            camera.centerCameraOnPlayer(playerPosX, playerPosY);
        }
        if (objectID.find(PLAYER_ID_PREFIX) != std::string::npos) {
            auto playerName = playerNames.find(objectID);
            int playerPosX = view->getViewPositionX();
            int playerPosY = view->getViewPositionY();
            SDL_Rect textRect = {playerPosX,
                                 playerPosY,
                                 2 * mtpFactor,
                                 mtpFactor};
            if (SDL_HasIntersection(&textRect, &cameraRect)) {
                textRect.x = playerPosX - cameraRect.x;
                textRect.y = playerPosY - mtpFactor / 2 - cameraRect.y;
                playerName->second->draw(&textRect);
            }
        }

        view->playAnimation(cameraRect);

    }
}
