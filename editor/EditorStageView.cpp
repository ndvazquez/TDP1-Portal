//
// Created by camix on 20/05/19.
//

#include <iostream>
#include "yaml-cpp/yaml.h"
#include "EditorStageView.h"
#include "../common/AnimatedSprite.h"

#define TEXTURES_KEY "Objects"

EditorStageView::EditorStageView(Window& window, YAML::Node& texturesInfo, int factor) :
window(window), factor(factor) {
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

void EditorStageView::draw(Window& window, SDL_Rect* camera, int xStart) {
    SDL_Rect destRect = {0 , 0, factor, factor};

    int camPosX = camera->x / factor;
    int camPosY = camera->y / factor;
    // We'll draw NxM tiles on the screen, to cover the camera.
    int n = camera->w / factor + 1;
    int m = camera->h / factor + 1;


    Sprite* sprite = nullptr;
    for (int i = camPosX; i < camPosX + n; ++i){
        for (int j = camPosY; j < camPosY + m; ++j){
            auto point = tiles.find(std::make_pair(i, j));
            if (point == tiles.end()){
                continue;
            }
            sprite = textures[point->second];
            destRect.x = xStart + (point->first.first - camPosX) * factor;
            destRect.y = (point->first.second - camPosY) * factor;
            sprite->draw(window, &destRect);
        }
    }
}

void EditorStageView::addTile(int x, int y, std::string& tileName) {
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

void EditorStageView::removeTile(int x, int y) {
    tiles.erase(std::make_pair(x, y));
}


EditorStageView::~EditorStageView() {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        delete it->second;
    }
}

std::string& EditorStageView::getName(int x, int y) {
    auto point = tiles.find(std::make_pair(x, y));
    if (point == tiles.end()) {
        throw EditorStageViewEmptyPositionException();
    }
    return point->second;
}
