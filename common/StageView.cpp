//
// Created by ndv on 5/13/19.
//

#include "StageView.h"
#include "Sprite.h"
#include <utility>
#include "yaml-cpp/yaml.h"
#include <map>
#include <iostream>

StageView::StageView(Window& window, YAML::Node& texturesInfo, int factor) :
    matrixToPixelFactor(factor) {
    const YAML::Node& staticObjects = texturesInfo[TEXTURES_STATICOBJETS_KEY];
    for (YAML::const_iterator it = staticObjects.begin();
         it != staticObjects.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        Sprite* newSprite = new Sprite(path, window);
        textures[name] = newSprite;
    }
}

StageView::~StageView() {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        delete it->second;
    }
}

void StageView::draw(Window& window, SDL_Rect* camera, int xStart) {
    SDL_Rect destRect = {0 , 0, matrixToPixelFactor, matrixToPixelFactor};

    int camPosX = camera->x / matrixToPixelFactor;
    int camPosY = camera->y / matrixToPixelFactor;
    // We'll draw NxM tiles on the screen, to cover the camera.
    int n = camera->w / matrixToPixelFactor + EXTRA_TILES;
    int m = camera->h / matrixToPixelFactor + EXTRA_TILES;


    Sprite* sprite = nullptr;
    for (int i = camPosX; i < camPosX + n; ++i){
        for (int j = camPosY; j < camPosY + m; ++j){
            auto point = tiles.find(std::make_pair(i, j));
            if (point == tiles.end()){
                continue;
            }
            sprite = textures[point->second];
            destRect.x = xStart + (point->first.first - camPosX) * matrixToPixelFactor;
            destRect.y = (point->first.second - camPosY) * matrixToPixelFactor;
            sprite->draw(window, &destRect);
        }
    }
}

void StageView::draw(Window& window, SDL_Rect* camera) {
    this->draw(window, camera, 0);
}

void StageView::addTile(int x, int y, std::string& tileName) {
    if (textures.count(tileName) == 0) {
        throw StageViewAddTileException();
    }
    tiles.insert(std::make_pair(std::make_pair(x, y), tileName));
}

void StageView::removeTile(int x, int y) {
    tiles.erase(std::make_pair(x, y));
}

std::string &StageView::getName(int x, int y) {
    auto point = tiles.find(std::make_pair(x, y));
    if (point == tiles.end()) {
        throw StageViewEmptyPositionException();
    }
    return point->second;
}


