//
// Created by camix on 20/05/19.
//

#include <iostream>
#include "yaml-cpp/yaml.h"
#include "Controller.h"
#include "object/Block.h"
#include "object/Button.h"
#include "object/Rock.h"
#include "object/Chell.h"
#include "object/Gate.h"
#include "object/Cake.h"
#include "object/Acid.h"

#define BLOCK_KEY "Blocks"
#define BUTTON_KEY "Buttons"
#define ROCK_KEY "Rocks"
#define CHELL_KEY "Chells"
#define GATE_KEY "Gate"
#define CAKE_KEY "Cake"
#define ACID_KEY "Acid"



Controller::Controller(Window& window, YAML::Node& texturesInfo, int factor) :
stageView(window, factor, textures, tiles) {
    const YAML::Node& blocks = texturesInfo[BLOCK_KEY];
    const YAML::Node& acid = texturesInfo[ACID_KEY];
    for (YAML::const_iterator it = acid.begin();
         it != acid.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        Acid* newObject = new Acid(path, window, node["frames"].as<int>(), name, w, h);
        textures[name] = newObject;

        for (YAML::const_iterator it = blocks.begin();
             it != blocks.end(); ++it) {
            const YAML::Node &node = *it;
            std::string name = node["name"].as<std::string>();

            newObject->hasToBeOn(name);
        }
    }

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

void Controller::draw(SDL_Rect* camera, int yStart) {
    stageView.draw(camera, yStart);
}

void Controller::addTile(int x, int y, std::string& tileName) {
    Object* obj = textures[tileName];
    if (!obj) {
        throw StageControllerNameException();
    }
    try {
        obj->addTo(x, y, tiles);
    }
    catch(ObjectException) {
        throw StageControllerAddTileException();
    }
}

void Controller::removeTile(int x, int y) {
    std::string& tileName = tiles[std::make_pair(x, y)];
    Object* obj = textures[tileName];
    if (!obj) {
        throw StageControllerNameException();
    }
    try {
        obj->removeFrom(x, y, tiles, textures);
    }
    catch(ObjectException) {
        throw StageControllerRemoveTileException();
    }
}


Controller::~Controller() {
    for (auto & texture : textures) {
        delete texture.second;
    }
}

std::string& Controller::getName(int x, int y) {
    auto point = tiles.find(std::make_pair(x, y));
    if (point == tiles.end()) {
        throw StageControllerEmptyPositionException();
    }
    return point->second;
}

void Controller::nameAnObject(int x, int y) {
    textures[tiles[std::make_pair(x, y)]]->setName();
}
