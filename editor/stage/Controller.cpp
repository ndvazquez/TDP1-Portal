//
// Created by camix on 20/05/19.
//

#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"
#include "Controller.h"

#include "object/Block.h"
#include "object/Button.h"
#include "object/Rock.h"
#include "object/Chell.h"
#include "object/Gate.h"
#include "object/Cake.h"
#include "object/Acid.h"
#include "object/DiagonalBlockUp.h"
#include "object/Receptor.h"
#include "object/WithOutGravitySentinel.h"
#include "object/GravitySentinel.h"

#define BLOCK_KEY "Blocks"
#define BUTTON_KEY "Buttons"
#define ROCK_KEY "Rocks"
#define CHELL_KEY "Chells"
#define GATE_KEY "Gate"
#define CAKE_KEY "Cake"
#define ACID_KEY "Acid"
#define DIAGONAL_BLOCK_KEY "DiagonalBlock"
#define RECPTOR_KEY "Receptors"


#define KEY_WITHOUT_GRAVITY_SENTINEL "WithoutGravitySentinel"
#define KEY_GRAVITY_SENTINEL "GravitySentinel"

Controller::Controller(Window& window, YAML::Node& texturesInfo, int factor) :
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


    const YAML::Node& receptors = texturesInfo[RECPTOR_KEY];
    for (YAML::const_iterator it = receptors.begin();
         it != receptors.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        Receptor* newObject = new Receptor(path, window, name, w, h);
        textures[name] = newObject;

        logicGates.addElement(newObject);
    }


    const YAML::Node& wGSentinels = texturesInfo[KEY_WITHOUT_GRAVITY_SENTINEL];
    for (YAML::const_iterator it = wGSentinels.begin();
         it != wGSentinels.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        WithOutGravitySentinel* newObject = new WithOutGravitySentinel(path, window, name, w, h);
        textures[name] = newObject;
    }

    const YAML::Node& gSentinels = texturesInfo[KEY_GRAVITY_SENTINEL];
    for (YAML::const_iterator it = gSentinels.begin();
         it != gSentinels.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        GravitySentinel* newObject = new GravitySentinel(path, window, name, w, h);
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

        logicGates.addElement(newObject);
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

        logicGates.addElement(newObject);
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
    }

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
    }

    const YAML::Node& DiagonalBlocks = texturesInfo[DIAGONAL_BLOCK_KEY];
    for (YAML::const_iterator it = DiagonalBlocks.begin();
         it != DiagonalBlocks.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        DiagonalBlockUp* newObject = new DiagonalBlockUp(path, window, name, w, h);
        textures[name] = newObject;
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
        obj->addTo(x, y, tiles, textures);
    }
    catch(ObjectException& e) {
        std::cerr << e.what();
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

std::string& Controller::getName(int x, int y) {
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

#define OBJECT_POSITION "position"

void Controller::writeYaml() {
    YAML::Emitter out;
    out << YAML::BeginMap;
    for(auto textures_it = textures.begin(); textures_it != textures.end(); textures_it++) {
        const std::string& currentName = textures_it->first;
        Object* object = textures_it->second;
        out << YAML::Key << currentName;
        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << OBJECT_POSITION;
        out << YAML::Key  << YAML::BeginSeq;
        for (auto tiles_it = tiles.begin(); tiles_it != tiles.end(); tiles_it++) {
            const std::pair<int,int>& position = tiles_it->first;
            const std::string& thisName = tiles_it->second;
            if (thisName == currentName) {
                std::pair<float, float> centerOfMass = object->centerOfMass(position);
                matrixToMeter(centerOfMass);

                out << YAML::Value << YAML::BeginMap;
                out << YAML::Key << "x";
                out << YAML::Value << centerOfMass.first;
                out << YAML::Key << "y";
                out << YAML::Value << centerOfMass.second;
                out << YAML::Value << YAML::EndMap;

            }
        }
        out << YAML::Key  << YAML::EndSeq;
        out << YAML::Value << YAML::EndMap;
    }
    out << YAML::EndMap;
    std::ofstream fout("file.yaml");
    fout << out.c_str();
}

void Controller::matrixToMeter(std::pair<float, float> &pair) {
    pair.second = stageView.getWindowHeight() - pair.second;
}
