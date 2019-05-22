//
// Created by camix on 20/05/19.
//

#ifndef PORTAL_STAGECONTROLLER_H
#define PORTAL_STAGECONTROLLER_H


#include <yaml-cpp/node/node.h>
#include <unordered_map>
#include <map>
#include "../common/Window.h"
#include "../common/Sprite.h"
#include "StageView.h"
#include "Object.h"

#define GRAVITY_EXC "Couldn't add the tile, that's not a valid place for an object with physics laws!\n"
#define NAME_EXC "Couldn't add the tile, that's not a valid element!\n"
#define POSITION_EXC "Couldn't get tile's name, that's position is empty!\n"

class EditorStageException : public std::exception {};

class EditorStageViewAddTileNameException : public EditorStageException {
    virtual const char* what() const throw () {
        std::string message = NAME_EXC;
        return message.c_str();
    }
};
class EditorStageViewAddTileGravityException : public EditorStageException {
    virtual const char* what() const throw () {
        std::string message = GRAVITY_EXC;
        return message.c_str();
    }
};

class EditorStageViewEmptyPositionException : public EditorStageException {
    virtual const char* what() const throw () {
        std::string message = POSITION_EXC;
        return message.c_str();
    }
};

class StageController {
private:
    std::unordered_map<std::string, Object*> textures;
    std::map<std::pair<int, int>, std::string> tiles;
    //std::map<std::string, bool> gravity;
    StageView stageView;



public:
    StageController(Window& window, YAML::Node& texturesInfo, int factor);
    ~StageController();

    void draw(SDL_Rect *camera, int xStart);

    void addTile(int x, int y, std::string &tileName);

    void removeTile(int x, int y);

    std::string &getName(int x, int y);
};


#endif //PORTAL_STAGECONTROLLER_H
