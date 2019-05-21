//
// Created by camix on 20/05/19.
//

#include <iostream>
#include "yaml-cpp/yaml.h"
#include "StageController.h"
#include "../common/AnimatedSprite.h"

#define TEXTURES_KEY "Objects"

StageController::StageController(Window& window, YAML::Node& texturesInfo, int factor) :
stageView(window, factor, textures, tiles) {
    const YAML::Node& objects = texturesInfo[TEXTURES_KEY];
    for (YAML::const_iterator it = objects.begin();
         it != objects.end(); ++it) {
        const YAML::Node& node = *it;

        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();

        Sprite* newSprite;
        if (node["animated"].as<int>()) {
            newSprite = new AnimatedSprite(path, window, node["frames"].as<int>());
        } else {
            newSprite = new Sprite(path, window);
        }

        textures[name] = newSprite;
        bool hasGravity = (bool) node["gravity"].as<int>();
        gravity[name] = hasGravity;
    }
}

void StageController::draw(SDL_Rect* camera, int xStart) {
    stageView.draw(camera, xStart);
}

void StageController::addTile(int x, int y, std::string& tileName) {
    std::cerr << std::endl;
    std::cerr << tileName << std::endl;
    if (gravity[tileName]) {
        auto it = tiles.find(std::make_pair(x, y + 1));
        if (it == tiles.end()) {
            throw EditorStageViewAddTileGravityException();
        }
    }
    if (textures.count(tileName) == 0) {
        throw EditorStageViewAddTileNameException();
    }
    tiles.insert(std::make_pair(std::make_pair(x, y), tileName));
}

void StageController::removeTile(int x, int y) {
    tiles.erase(std::make_pair(x, y));
}


StageController::~StageController() {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        delete it->second;
    }
}

std::string& StageController::getName(int x, int y) {
    auto point = tiles.find(std::make_pair(x, y));
    if (point == tiles.end()) {
        throw EditorStageViewEmptyPositionException();
    }
    return point->second;
}
