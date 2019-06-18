//
// Created by camix on 20/05/19.
//

#include <iostream>
#include <fstream>
#include "Controller.h"
#include "YamlManager.h"



Controller::Controller(Window &window, std::string &texturesPath, int factor) :
                    stageView(window, factor, textures, tiles),
                    factor(factor),
                    yaml(textures, tiles, logicGates) {
    yaml.getObjects(window, texturesPath);
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

void Controller::nameAnObject(int x, int y, std::string& enteredName) {
    std::pair<int, int> pair = std::make_pair(x, y);
    Object* obj = textures[tiles[pair]];
    logicGates.setName(obj, pair, enteredName);
}

void Controller::addCondition(int x, int y) {
    std::pair<int, int> pair = std::make_pair(x, y);

    std::cerr << "Ingrese una condición lógica." << std::endl;

    std::string enteredCondition;
    std::getline(std::cin, enteredCondition);

    std::cerr << "La condición ingresada es: " << enteredCondition << std::endl;

    Object* obj = textures[tiles[pair]];

    logicGates.addCondition(obj, pair, enteredCondition);
}


void Controller::writeYaml(int lenPixelsInY) {
    yaml.writeStage();
}

