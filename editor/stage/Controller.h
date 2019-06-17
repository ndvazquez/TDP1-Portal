//
// Created by camix on 20/05/19.
//

#ifndef PORTAL_CONTROLLER_H
#define PORTAL_CONTROLLER_H



#include <unordered_map>
#include <map>
#include <yaml-cpp/node/node.h>

#include "LogicGates.h"
#include "../../common/Window.h"
#include "../../common/Sprite.h"
#include "View.h"
#include "object/Object.h"
#include "YamlManager.h"


class Controller {
private:
    std::unordered_map<std::string, Object*> textures;
    std::map<std::pair<int, int>, std::string> tiles;
    //std::map<std::string, bool> gravity;
    int factor;
    View stageView;
    LogicGates logicGates;


public:
    Controller(Window& window, YAML::Node& texturesInfo, int factor);
    ~Controller();

    void draw(SDL_Rect *camera, int xStart);

    void addTile(int x, int y, std::string &tileName);

    void removeTile(int x, int y);

    std::string &getName(int x, int y);

    void nameAnObject(int x, int y, std::string& enteredName);

    void addCondition(int x, int y);

    void writeYaml(int i);
};


#define ADD_TILE "Couldn't add the tile. That's not a valid place\n"
#define NAME_EXC "Couldn't add the tile. That's not a valid element!\n"
#define POSITION_EXC "Couldn't get tile's name. That's position is empty!\n"
#define REMOVE_TILE  "Couldn't remove the tile\n"
#define INVALID_CONDITION_EXC "Invalid condition\n"


class StageControllerException : public std::exception {};

class StageControllerNameException : public StageControllerException {
public:
    const char* what() const noexcept override {
        return NAME_EXC;
    }
};

class StageControllerAddTileException : public StageControllerException {
public:
    const char* what() const noexcept override {
        return ADD_TILE;
    }
};

class StageControllerRemoveTileException : public StageControllerException {
public:
    const char* what() const noexcept override {
        return REMOVE_TILE;
    }
};

class StageControllerEmptyPositionException : public StageControllerException {
public:
    const char* what() const noexcept override {
        return POSITION_EXC;
    }
};

#endif //PORTAL_CONTROLLER_H
