//
// Created by ndv on 6/9/19.
//

#include "ViewManager.h"
#include "ViewFactory.h"
#include "../json/json.hpp"
#include <iostream>

ViewManager::ViewManager(Window& window,
        int levelHeight,
        int factor,
        std::string& playerID,
        nlohmann::json& objectsData,
        SoundCodeQueue& soundCodeQueue)
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
        views.insert({viewName, newView});
    }
}

ViewManager::~ViewManager() {
    for (auto it = views.begin(); it != views.end(); ++it){
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
        view->playAnimation(cameraRect);
    }
}
