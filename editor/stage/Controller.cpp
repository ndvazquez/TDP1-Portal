//
// Created by camix on 20/05/19.
//

#include <iostream>
#include <fstream>
#include "Controller.h"
#include "YamlManager.h"
#include "../../common/InputText.h"


#define AFTER_INVALID_FILE "THAT'S NOT EVEN A VALID FILE. YOU ARE MOVING AWAY FROM THE CAKE"

Controller::Controller(Window &window,
                       std::string texturesPath,
                       int factor,
                       std::string &stageYamlPath) :
                    stageView(window, factor, textures, tiles),
                    factor(factor),

                    yaml(textures, tiles, logicGates),
                    texturesPath(texturesPath) {

    try {
        yaml.getObjects(window, texturesPath);
        yaml.readStage(stageYamlPath);
    }
    catch(InvalidFile& e) {
        return;
    }
    catch (TextException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

void Controller::draw(SDL_Rect* camera, int yStart) {
    stageView.draw(camera, yStart);
}

void Controller::addTile(int x, int y, int id) {
    Object* obj = textures[id];
    if (!obj) {
        throw StageControllerNameException();
    }
    try {
        obj->addTo(x, y, tiles, textures);
    }
    catch(ObjectException& e) {
        std::cerr << e.what();
        throw StageControllerAddTileException();
    }
}

void Controller::removeTile(int x, int y) {
    int tileName = tiles[std::make_pair(x, y)];
    Object* obj = textures[tileName];
    if (!obj) {
        throw StageControllerNameException();
    }
    try {
        obj->removeFrom(x, y, tiles, textures);
    }
    catch(ObjectException& e) {
        std::cerr << e.what();
        throw StageControllerRemoveTileException();
    }
}


Controller::~Controller() {
    for (auto & texture : textures) {
        delete texture.second;
    }
}

void Controller::drawCurrent(int id, int x, int y) {
    if(!id) return;
    std::pair<int, int> pair = std::make_pair(x, y);
    SDL_Rect rect = {x*factor, y*factor, factor, factor};
    Object* obj = textures[id];
    if (!obj) return;
    obj->draw(&rect);
}

int Controller::getName(int x, int y) {
    auto point = tiles.find(std::make_pair(x, y));
    if (point == tiles.end()) {
        throw StageControllerEmptyPositionException();
    }
    return point->second;
}

void Controller::nameAnObject(int x,
                                int y,
                                Window &window,
                                SDL_Rect rect,
                                SDL_Rect* camera,
                                int yStart) {
    std::pair<int, int> pair = std::make_pair(x, y);
    Object* obj = textures[tiles[pair]];
    logicGates.setName(obj, pair, window, &rect,camera, yStart, stageView);
}

void Controller::addCondition(int x,
                              int y,
                              Window &window,
                              SDL_Rect rect,
                              SDL_Rect* camera,
                              int yStart) {
    std::pair<int, int> pair = std::make_pair(x, y);

    Object* obj = textures[tiles[pair]];

    logicGates.addCondition(obj, pair, window, &rect,camera, yStart, stageView);
}


void Controller::writeYaml(std::string &yamlPath) {
    try {
        yaml.writeStage(yamlPath);
    }
    catch(InvalidFile& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}
