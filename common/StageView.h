//
// Created by ndv on 5/13/19.
//

#ifndef PORTAL_STAGEVIEW_H
#define PORTAL_STAGEVIEW_H
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include "Window.h"
#include "Sprite.h"

#define TEXTURES_KEY "StaticObjects"

class StageView {
    std::unordered_map<std::string, Sprite*> textures;
public:
    StageView(Window& window, YAML::Node& texturesInfo);
    ~StageView();
    void draw(Window& window);
};


#endif //PORTAL_STAGEVIEW_H
