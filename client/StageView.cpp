//
// Created by ndv on 5/13/19.
//

#include "StageView.h"
#include "../common/Sprite.h"
#include <utility>
#include "yaml-cpp/yaml.h"
#include <map>
#include <string>

StageView::StageView(Window& window, YAML::Node& texturesInfo, int factor) :
        window(window),
        mtpFactor(factor) {
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

void StageView::draw(const SDL_Rect& camera) {
    SDL_Rect destRect = {0 , 0, mtpFactor * BLOCK_SIZE, mtpFactor * BLOCK_SIZE};
    int camPosX = camera.x / mtpFactor;
    int camPosY = camera.y / mtpFactor;
    // We'll draw NxM tiles on the screen, to cover the camera.
    int n = camera.w / mtpFactor + EXTRA_TILES;
    int m = camera.h / mtpFactor + EXTRA_TILES;

    Sprite* sprite = nullptr;
    for (int i = camPosX; i < camPosX + n; ++i){
        for (int j = camPosY; j < camPosY + m; ++j){
            auto tile = tiles.find(std::make_pair(i, j));
            if (tile == tiles.end()){
                continue;
            }
            auto tileCoordinate = tile->first;
            auto tileName = tile->second;
            sprite = textures[tileName];
            destRect.x = tileCoordinate.first  * mtpFactor -
                    camera.x - destRect.w / 2;
            destRect.y = tileCoordinate.second * mtpFactor -
                    camera.y - destRect.h / 2;
            sprite->draw(&destRect);
        }
    }
}

void StageView::addTile(int x, int y, std::string& tileName) {
    if (textures.count(tileName) == 0) {
        throw StageViewAddTileException();
    }
    tiles.insert(std::make_pair(std::make_pair(x, y), tileName));
}
