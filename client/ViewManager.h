//
// Created by ndv on 6/9/19.
//

#ifndef PORTAL_VIEWMANAGER_H
#define PORTAL_VIEWMANAGER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "../json/json.hpp"
#include "View.h"
#include "SoundCodeQueue.h"
#include "Camera.h"

class ViewManager {
    Window& gameWindow;
    int levelHeight;
    int mtpFactor;
    std::string playerID;
    std::unordered_map<std::string, View*> views;
public:
    ViewManager(Window& window,
            int levelHeight,
            int factor,
            std::string& playerID,
            nlohmann::json& objectsData,
            SoundCodeQueue& soundCodeQueue);
    ~ViewManager();
    void showAndUpdateViews(nlohmann::json& objectsData, Camera& camera);
};


#endif //PORTAL_VIEWMANAGER_H
