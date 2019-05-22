//
// Created by camix on 20/05/19.
//

#include <iostream>
#include "yaml-cpp/yaml.h"
#include "StageController.h"
#include "MouseButtonUp.h"
#include "MouseDoubleCick.h"
#include "Block.h"
#include "Button.h"
#include "Rock.h"
#include "Chell.h"
#include "Gate.h"

#define BLOCK_KEY "Blocks"
#define BUTTON_KEY "Buttons"
#define ROCK_KEY "Rocks"
#define CHELL_KEY "Chells"
#define GATE_KEY "Gate"


#define TEXTURES_KEY "Objects"


StageController::StageController(Window& window, YAML::Node& texturesInfo, int factor) :
stageView(window, factor, textures, tiles) {
    const YAML::Node& blocks = texturesInfo[BLOCK_KEY];
    for (YAML::const_iterator it = blocks.begin();
         it != blocks.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        Block* newObject = new Block(path, window);
        textures[name] = newObject;
    }

    const YAML::Node& buttons = texturesInfo[BUTTON_KEY];
    for (YAML::const_iterator it = buttons.begin();
         it != buttons.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        Button* newObject = new Button(path, window);
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
        Rock* newObject = new Rock(path, window);
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
        Chell* newObject = new Chell(path, window, node["frames"].as<int>());
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
        Gate* newObject = new Gate(path, window);
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
    auto it = tiles.find(std::make_pair(x, y + 1));
    Object* obj = textures[tileName];
    bool canBeAdd;
    if (it == tiles.end()) {
        canBeAdd = obj->canBeOn();
    } else {
        canBeAdd = obj->canBeOn(it->second);
    }

    if (!canBeAdd) {
        throw EditorStageViewAddTileGravityException();
    }
    tiles.insert(std::make_pair(std::make_pair(x, y), tileName));
}

void StageController::removeTile(int x, int y) {
    tiles.erase(std::make_pair(x, y));
}


StageController::~StageController() {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        delete it->second;
    }
}

std::string& StageController::getName(int x, int y) {
    auto point = tiles.find(std::make_pair(x, y));
    if (point == tiles.end()) {
        throw EditorStageViewEmptyPositionException();
    }
    return point->second;
}
