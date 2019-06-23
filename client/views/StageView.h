//
// Created by ndv on 5/13/19.
//

#ifndef PORTAL_STAGEVIEW_H
#define PORTAL_STAGEVIEW_H
#include <unordered_map>
#include <exception>
#include <map>
#include <yaml-cpp/yaml.h>
#include "../../common/Window.h"
#include "../../common/Sprite.h"
#include <utility>
#include <string>
#include "../../json/json.hpp"

#define TEXTURES_STATICOBJETS_KEY "StaticObjects"
#define EXTRA_TILES 2
#define BLOCK_SIZE 2

class StageViewAddTileException : public std::exception{
    virtual const char* what() const throw() {
        std::string message = "Couldn't add the tile, "
                              "that's not a valid element!\n";
        return message.c_str();
    }
};

class StageView {
    Window& window;
    int mtpFactor;
    std::unordered_map<std::string, Sprite*> textures;
    std::map<std::pair<int, int>, std::string> tiles;

public:
    StageView(Window& window, YAML::Node& texturesInfo,
            int factor, nlohmann::json& objectsData, int stageHeight);
    ~StageView();
    void addTile(int x, int y, const std::string& tileName);
    void draw(const SDL_Rect& camera);
};


#endif //PORTAL_STAGEVIEW_H
