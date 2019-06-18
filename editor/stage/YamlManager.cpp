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

YamlManager::YamlManager(std::unordered_map<int, Object *> &textures,
                         std::map<std::pair<int, int>, int> &tiles,
                         LogicGates &logicGates) :
        textures(textures),
        tiles(tiles),
        logicGates(logicGates) {}


void YamlManager::getWidthAndHeightInMeters(int *width, int *height) {
    int maxXMtrixPosition = 0, maxXMtriyPosition = 0;
    for (auto & tile : tiles) {
        const std::pair<int,int>& pixelsPosition = tile.first;
        int id = tile.second;
        if (maxXMtrixPosition < pixelsPosition.first + textures[id]->getWidth()) {
            maxXMtrixPosition = pixelsPosition.first;
        }
        if (maxXMtriyPosition < pixelsPosition.second) {
            maxXMtriyPosition = pixelsPosition.second;
        }
    }
    *width = maxXMtrixPosition;
    *height = maxXMtriyPosition + 1;
}


void YamlManager::write() {
    int width, height;
    YAML::Emitter out;
    getWidthAndHeightInMeters(&width, &height);
    out << YAML::BeginMap;
    out << YAML::Key << "Stage";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "dimentions";

    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "width";
    out << YAML::Value << width;
    out << YAML::Key << "height";
    out << YAML::Value << height;
    out << YAML::Value << YAML::EndMap;

    out << YAML::Value << YAML::EndMap;




    for(auto & texture : textures) {
        int currentID = texture.first;
        if (currentID == GRAVITY_SENTINEL ||
            currentID == WITHOUT_GRAVITY_SENTINEL) continue;
        Object* object = texture.second;
        out << YAML::Key << currentID;

        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << OBJECT_POSITION;

        out << YAML::Key  << YAML::BeginSeq;
        for (auto & tile : tiles) {
            const std::pair<int,int>& position = tile.first;
            int thisID = tile.second;
            if (thisID == currentID) {
                std::pair<float, float> centerOfMass =
                        object->centerOfMass(position);
                matrixToMeter(centerOfMass, height);
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


    std::map<std::pair<float, float>, std::string>& names = logicGates.getNames();
    out << YAML::Key << "Names";
    out << YAML::Key << YAML::BeginSeq;
    for(auto & it : names) {
        std::pair<float, float> centerOfMassPos = it.first;
        matrixToMeter(centerOfMassPos, height);
        std::string& name = it.second;
        out << YAML::Value << YAML::BeginMap;

        out << YAML::Key << "name";
        out << YAML::Value << name;
        out << YAML::Key << "position";

        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "x";
        out << YAML::Value << centerOfMassPos.first;
        out << YAML::Key << "y";
        out << YAML::Value << centerOfMassPos.second;
        out << YAML::Value << YAML::EndMap;


        out << YAML::Value << YAML::EndMap;
    }
    out << YAML::Key << YAML::EndSeq;


    std::map<std::pair<float, float>, std::string>& conditions = logicGates.getConditions();
    out << YAML::Key << "Conditions";
    out << YAML::Key << YAML::BeginSeq;
    for(auto & it : conditions) {
        std::pair<float, float> centerOfMassPos = it.first;
        matrixToMeter(centerOfMassPos, height);
        std::string& name = it.second;
        out << YAML::Value << YAML::BeginMap;

        out << YAML::Key << "name";
        out << YAML::Value << name;
        out << YAML::Key << "position";

        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "x";
        out << YAML::Value << centerOfMassPos.first;
        out << YAML::Key << "y";
        out << YAML::Value << centerOfMassPos.second;
        out << YAML::Value << YAML::EndMap;


        out << YAML::Value << YAML::EndMap;
    }
    out << YAML::Key << YAML::EndSeq;

    out << YAML::EndMap;
    std::ofstream fileOut("file.yaml");
    fileOut << out.c_str();
}

#define IMAGE_PATH "path"
#define OBJECT_ID "id"
#define OBJECT_HEIGHT "h"
#define OBJECT_WIDTH "w"

void YamlManager::read(Window &window, YAML::Node &texturesInfo) {
    const YAML::Node& blocks = texturesInfo[BLOCK_KEY];
    for (YAML::const_iterator it = blocks.begin();
         it != blocks.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        Block* newObject = new Block(path, window, id, w, h);
        textures[id] = newObject;
    }


    const YAML::Node& receptors = texturesInfo[RECPTOR_KEY];
    for (YAML::const_iterator it = receptors.begin();
         it != receptors.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        Receptor* newObject = new Receptor(path, window, id, w, h);
        textures[id] = newObject;

        logicGates.addNamedElement(newObject);
    }


    const YAML::Node& wGSentinels = texturesInfo[KEY_WITHOUT_GRAVITY_SENTINEL];
    for (YAML::const_iterator it = wGSentinels.begin();
         it != wGSentinels.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        WithOutGravitySentinel* newObject =
                new WithOutGravitySentinel(path, window, id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& gSentinels = texturesInfo[KEY_GRAVITY_SENTINEL];
    for (YAML::const_iterator it = gSentinels.begin();
         it != gSentinels.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        GravitySentinel* newObject =
                new GravitySentinel(path, window, id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& buttons = texturesInfo[BUTTON_KEY];
    for (YAML::const_iterator it = buttons.begin();
         it != buttons.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        Button* newObject = new Button(path, window, id, w, h);
        textures[id] = newObject;

        logicGates.addNamedElement(newObject);
    }

    const YAML::Node& rocks = texturesInfo[ROCK_KEY];
    for (YAML::const_iterator it = rocks.begin();
         it != rocks.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();

        Rock* newObject = new Rock(path, window, id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& chells = texturesInfo[CHELL_KEY];
    for (YAML::const_iterator it = chells.begin();
         it != chells.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        Chell* newObject =
                new Chell(path, window, node["frames"].as<int>(), id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& gates = texturesInfo[GATE_KEY];
    for (YAML::const_iterator it = gates.begin();
         it != gates.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        Gate* newObject = new Gate(path, window, id, w, h);
        textures[id] = newObject;

        logicGates.addNamedElement(newObject);
        logicGates.addConditionalElement(newObject);
    }

    const YAML::Node& cakes = texturesInfo[CAKE_KEY];
    for (YAML::const_iterator it = cakes.begin();
         it != cakes.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        Cake* newObject =
                new Cake(path, window, node["frames"].as<int>(), id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& acid = texturesInfo[ACID_KEY];
    for (YAML::const_iterator it = acid.begin();
         it != acid.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        Acid* newObject =
                new Acid(path, window, node["frames"].as<int>(), id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& DiagonalBlocksRU = texturesInfo[DIAGONAL_BLOCK_RU_KEY];
    for (YAML::const_iterator it = DiagonalBlocksRU.begin();
         it != DiagonalBlocksRU.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        DiagonalBlockRightUp* newObject =
                new DiagonalBlockRightUp(path, window, id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& DiagonalBlocksLE = texturesInfo[DIAGONAL_BLOCK_LU_KEY];
    for (YAML::const_iterator it = DiagonalBlocksLE.begin();
         it != DiagonalBlocksLE.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        DiagonalBlockLeftUp* newObject =
                new DiagonalBlockLeftUp(path, window, id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& DiagonalBlocksLD = texturesInfo[DIAGONAL_BLOCK_LD_KEY];
    for (YAML::const_iterator it = DiagonalBlocksLD.begin();
         it != DiagonalBlocksLD.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        DiagonalBlockLeftDown* newObject =
                new DiagonalBlockLeftDown(path, window, id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& DiagonalBlocksRD = texturesInfo[DIAGONAL_BLOCK_RD_KEY];
    for (YAML::const_iterator it = DiagonalBlocksRD.begin();
         it != DiagonalBlocksRD.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        DiagonalBlockRightDown* newObject =
                new DiagonalBlockRightDown(path, window, id, w, h);
        textures[id] = newObject;
    }
}

