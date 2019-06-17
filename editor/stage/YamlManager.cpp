//
// Created by camix on 17/06/19.
//

#include <fstream>
#include "YamlManager.h"
#include "yaml-cpp/yaml.h"

#include "object/Block.h"
#include "object/Button.h"
#include "object/Rock.h"
#include "object/Chell.h"
#include "object/Gate.h"
#include "object/Cake.h"
#include "object/Acid.h"
#include "object/Receptor.h"
#include "object/WithOutGravitySentinel.h"
#include "object/GravitySentinel.h"
#include "object/diagonalBlocks/DiagonalBlockRightUp.h"
#include "object/diagonalBlocks/DiagonalBlockLeftUp.h"
#include "object/diagonalBlocks/DiagonalBlockDown.h"
#include "object/diagonalBlocks/DiagonalBlockLeftDown.h"
#include "object/diagonalBlocks/DiagonalBlockRightDown.h"


#define BLOCK_KEY "Blocks"
#define BUTTON_KEY "Buttons"
#define ROCK_KEY "Rocks"
#define CHELL_KEY "Chells"
#define GATE_KEY "Gate"
#define CAKE_KEY "Cake"
#define ACID_KEY "Acid"
#define DIAGONAL_BLOCK_RU_KEY "DiagonalBlockRU"
#define DIAGONAL_BLOCK_LU_KEY "DiagonalBlockLU"
#define DIAGONAL_BLOCK_LD_KEY "DiagonalBlockLD"
#define DIAGONAL_BLOCK_RD_KEY "DiagonalBlockRD"

#define RECPTOR_KEY "Receptors"


#define KEY_WITHOUT_GRAVITY_SENTINEL "WithoutGravitySentinel"
#define KEY_GRAVITY_SENTINEL "GravitySentinel"

#define OBJECT_POSITION "position"


void matrixToMeter(std::pair<float, float> &pair, int totalMeters) {
    pair.second = totalMeters - pair.second;
}

void YamlManager::write(std::unordered_map<std::string, Object *> &textures,
                        std::map<std::pair<int, int>, std::string> &tiles,
                        int totalMeters) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    for(auto & texture : textures) {
        const std::string& currentName = texture.first;
        if (currentName == GRAVITY_SENTINEL ||
            currentName == WITHOUT_GRAVITY_SENTINEL) continue;
        Object* object = texture.second;
        out << YAML::Key << currentName;

        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << OBJECT_POSITION;

        out << YAML::Key  << YAML::BeginSeq;
        for (auto & tile : tiles) {
            const std::pair<int,int>& position = tile.first;
            const std::string& thisName = tile.second;
            if (thisName == currentName) {
                std::pair<float, float> centerOfMass =
                        object->centerOfMass(position);
                matrixToMeter(centerOfMass, totalMeters);
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
    std::ofstream fileOut("file.yaml");
    fileOut << out.c_str();
}

void YamlManager::read(Window &window,
                       YAML::Node &texturesInfo,
                       std::unordered_map<std::string, Object *> &textures,
                       std::map<std::pair<int, int>, std::string> &tiles,
                       LogicGates &logicGates) {
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
        WithOutGravitySentinel* newObject =
                new WithOutGravitySentinel(path, window, name, w, h);
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
        GravitySentinel* newObject =
                new GravitySentinel(path, window, name, w, h);
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
        Chell* newObject =
                new Chell(path, window, node["frames"].as<int>(), name, w, h);
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
        Cake* newObject =
                new Cake(path, window, node["frames"].as<int>(), name, w, h);
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
        Acid* newObject =
                new Acid(path, window, node["frames"].as<int>(), name, w, h);
        textures[name] = newObject;
    }

    const YAML::Node& DiagonalBlocksRU = texturesInfo[DIAGONAL_BLOCK_RU_KEY];
    for (YAML::const_iterator it = DiagonalBlocksRU.begin();
         it != DiagonalBlocksRU.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        DiagonalBlockRightUp* newObject =
                new DiagonalBlockRightUp(path, window, name, w, h);
        textures[name] = newObject;
    }

    const YAML::Node& DiagonalBlocksLE = texturesInfo[DIAGONAL_BLOCK_LU_KEY];
    for (YAML::const_iterator it = DiagonalBlocksLE.begin();
         it != DiagonalBlocksLE.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        DiagonalBlockLeftUp* newObject =
                new DiagonalBlockLeftUp(path, window, name, w, h);
        textures[name] = newObject;
    }

    const YAML::Node& DiagonalBlocksLD = texturesInfo[DIAGONAL_BLOCK_LD_KEY];
    for (YAML::const_iterator it = DiagonalBlocksLD.begin();
         it != DiagonalBlocksLD.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        DiagonalBlockLeftDown* newObject =
                new DiagonalBlockLeftDown(path, window, name, w, h);
        textures[name] = newObject;
    }

    const YAML::Node& DiagonalBlocksRD = texturesInfo[DIAGONAL_BLOCK_RD_KEY];
    for (YAML::const_iterator it = DiagonalBlocksRD.begin();
         it != DiagonalBlocksRD.end(); ++it) {
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int w = node["w"].as<int>();
        int h = node["h"].as<int>();
        DiagonalBlockRightDown* newObject =
                new DiagonalBlockRightDown(path, window, name, w, h);
        textures[name] = newObject;
    }
}
