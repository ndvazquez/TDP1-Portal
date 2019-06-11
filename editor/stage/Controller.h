//
// Created by camix on 20/05/19.
//

#ifndef PORTAL_CONTROLLER_H
#define PORTAL_CONTROLLER_H


#include <yaml-cpp/node/node.h>
#include <unordered_map>
#include <map>
#include "../../common/Window.h"
#include "../../common/Sprite.h"
#include "View.h"
#include "object/Object.h"

#define ADD_TILE "Couldn't add the tile. That's not a valid place\n"
#define NAME_EXC "Couldn't add the tile. That's not a valid element!\n"
#define POSITION_EXC "Couldn't get tile's name. That's position is empty!\n"

class StageControllerException : public std::exception {};

class StageControllerNameException : public StageControllerException {
    virtual const char* what() const throw () {
        std::string message = NAME_EXC;
        return message.c_str();
    }
};

class StageControllerAddTileException : public StageControllerException {
    virtual const char* what() const throw () {
        std::string message = ADD_TILE;
        return message.c_str();
    }
};

class StageControllerRemoveTileException : public StageControllerException {
    virtual const char* what() const throw () {
        std::string message = ADD_TILE;
        return message.c_str();
    }
};

class StageControllerEmptyPositionException : public StageControllerException {
    virtual const char* what() const throw () {
        std::string message = POSITION_EXC;
        return message.c_str();
    }
};

class Controller {
private:
    std::unordered_map<std::string, Object*> textures;
    std::map<std::pair<int, int>, std::string> tiles;
    //std::map<std::string, bool> gravity;
    View stageView;



public:
    Controller(Window& window, YAML::Node& texturesInfo, int factor);
    ~Controller();

    void draw(SDL_Rect *camera, int xStart);

    void addTile(int x, int y, std::string &tileName);

    void removeTile(int x, int y);

    std::string &getName(int x, int y);

    void nameAnObject(int x, int y, std::string& enteredName);
};


#endif //PORTAL_CONTROLLER_H
