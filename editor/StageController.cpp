//
// Created by camix on 20/05/19.
//

#include <iostream>
#include "yaml-cpp/yaml.h"
#include "StageController.h"
#include "Block.h"
#include "Button.h"
#include "Rock.h"
#include "Chell.h"
#include "Gate.h"
#include "Cake.h"

#define BLOCK_KEY "Blocks"
#define BUTTON_KEY "Buttons"
#define ROCK_KEY "Rocks"
#define CHELL_KEY "Chells"
#define GATE_KEY "Gate"
#define CAKE_KEY "Cake"


StageController::StageController(Window& window, YAML::Node& texturesInfo, int factor) :
stageView(window, factor, textures, tiles) {

    const YAML::Node& blocks = texturesInfo[BLOCK_KEY];
    for (YAML::const_iterator it = blocks.begin();
         it != blocks.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        Block* newObject = new Block(path, window, name, w, h);
        textures[name] = newObject;
    }

    const YAML::Node& buttons = texturesInfo[BUTTON_KEY];
    for (YAML::const_iterator it = buttons.begin();
         it != buttons.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        Button* newObject = new Button(path, window, name, w, h);
        textures[name] = newObject;

        for (YAML::const_iterator it = blocks.begin();
             it != blocks.end(); ++it) {
            const YAML::Node &node = *it;
            std::string name = node["name"].as<std::string>();

            newObject->hasToBeOn(name);
        }
    }

    const YAML::Node& rocks = texturesInfo[ROCK_KEY];
    for (YAML::const_iterator it = rocks.begin();
         it != rocks.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();

        Rock* newObject = new Rock(path, window, name, w, h);
        textures[name] = newObject;

        for (YAML::const_iterator it = blocks.begin();
             it != blocks.end(); ++it) {
            const YAML::Node &node = *it;
            std::string name = node["name"].as<std::string>();

            newObject->hasToBeOn(name);
        }
    }

    const YAML::Node& chells = texturesInfo[CHELL_KEY];
    for (YAML::const_iterator it = chells.begin();
         it != chells.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        Chell* newObject = new Chell(path, window, node["frames"].as<int>(), name, w, h);
        textures[name] = newObject;

        for (YAML::const_iterator it = blocks.begin();
             it != blocks.end(); ++it) {
            const YAML::Node &node = *it;
            std::string name = node["name"].as<std::string>();

            newObject->hasToBeOn(name);
        }
    }

    const YAML::Node& gates = texturesInfo[GATE_KEY];
    for (YAML::const_iterator it = gates.begin();
         it != gates.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        Gate* newObject = new Gate(path, window, name, w, h);
        textures[name] = newObject;

        for (YAML::const_iterator it = blocks.begin();
             it != blocks.end(); ++it) {
            const YAML::Node &node = *it;
            std::string name = node["name"].as<std::string>();

            newObject->hasToBeOn(name);
        }
    }

    const YAML::Node& cakes = texturesInfo[CAKE_KEY];
    for (YAML::const_iterator it = cakes.begin();
         it != cakes.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        Cake* newObject = new Cake(path, window, node["frames"].as<int>(), name, w, h);
        textures[name] = newObject;

        for (YAML::const_iterator it = blocks.begin();
             it != blocks.end(); ++it) {
            const YAML::Node &node = *it;
            std::string name = node["name"].as<std::string>();

            newObject->hasToBeOn(name);
        }
    }
}

void StageController::draw(SDL_Rect* camera, int xStart) {
    stageView.draw(camera, xStart);
}

void StageController::addTile(int x, int y, std::string& tileName) {
    Object* obj = textures[tileName];
    if (!obj) {
        throw StageControllerNameException();
    }
    try {
        obj->addTo(x, y, tiles);
    }
    catch(StageObjectException) {
        throw StageControllerAddTileException();
    }
}

void StageController::removeTile(int x, int y) {
    std::string& tileName = tiles[std::make_pair(x, y)];
    Object* obj = textures[tileName];
    if (!obj) {
        throw StageControllerNameException();
    }
    try {
        obj->removeFrom(x, y, tiles, textures);
    }
    catch(StageObjectException) {
        throw StageControllerRemoveTileException();
    }
}


StageController::~StageController() {
    for (auto & texture : textures) {
        delete texture.second;
    }
}

std::string& StageController::getName(int x, int y) {
    auto point = tiles.find(std::make_pair(x, y));
    if (point == tiles.end()) {
        throw StageControllerEmptyPositionException();
    }
    return point->second;
}

void StageController::nameAnObject(int x, int y) {
    textures[tiles[std::make_pair(x, y)]]->setName();
}
