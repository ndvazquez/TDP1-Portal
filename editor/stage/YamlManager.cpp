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
#include "object/VerticalEnergyBar.h"
#include "object/HorizontalEnergyBar.h"


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
#define V_ENERGY_BAR_KEY "VerticalEnergyBar"
#define H_ENERGY_BAR_KEY "HorizontalEnergyBar"

#define KEY_WITHOUT_GRAVITY_SENTINEL "WithoutGravitySentinel"
#define KEY_GRAVITY_SENTINEL "GravitySentinel"


#define DIRECTORY "levels/"
#define EXTENSION ".yaml"

void matrixPosToMeters(std::pair<float, float> &pair, int totalMeters) {
    pair.second = totalMeters - pair.second;
}


void YamlManager::MetersToMatrixPos(std::pair<float, float> &pair, int width) {
    pair.second = width - pair.second;
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


void YamlManager::writeStage(std::string& stagePath) {
    try {
        int width, height;
        YAML::Emitter out;
        getWidthAndHeightInMeters(&width, &height);
        out << YAML::BeginMap;
        out << YAML::Key << STAGE_ATTRIBUTES;
        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << STAGE_SIZE;

        out << YAML::Value << YAML::BeginMap;
        out << YAML::Key << HORIZONTAL_SIZE;
        out << YAML::Value << width;
        out << YAML::Key << VERTICAL_SIZE;
        out << YAML::Value << height;
        out << YAML::Value << YAML::EndMap;

        out << YAML::Value << YAML::EndMap;


        for (auto &texture : textures) {
            int currentID = texture.first;
            Object *object = texture.second;
            //if (currentID == GRAVITY_SENTINEL ||
            //    currentID == WITHOUT_GRAVITY_SENTINEL)
            //    continue;
            out << YAML::Key << currentID;

            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << OBJECT_POSITION;

            out << YAML::Key << YAML::BeginSeq;
            for (auto &tile : tiles) {
                const std::pair<int, int> &position = tile.first;
                int thisID = tile.second;
                if (thisID == currentID) {
                    std::pair<float, float> centerOfMass =
                            object->matrixPosToCenterOfMass(position);
                    matrixPosToMeters(centerOfMass, height);
                    out << YAML::Value << YAML::BeginMap;
                    out << YAML::Key << HORIZONTAL_POSITION;
                    out << YAML::Value << centerOfMass.first;
                    out << YAML::Key << VERTICAL_POSITION;
                    out << YAML::Value << centerOfMass.second;
                    out << YAML::Value << YAML::EndMap;
                }
            }
            out << YAML::Key << YAML::EndSeq;
            out << YAML::Value << YAML::EndMap;
        }


        std::map<std::pair<float, float>, std::string> &names = logicGates.getNames();
        out << YAML::Key << STAGE_OBJECT_NAMES;
        out << YAML::Key << YAML::BeginSeq;
        for (auto &it : names) {
            std::pair<float, float> centerOfMassPos = it.first;
            matrixPosToMeters(centerOfMassPos, height);
            std::string &name = it.second;
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << OBJECT_NAME;
            out << YAML::Value << name;
            out << YAML::Key << OBJECT_POSITION;

            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << HORIZONTAL_POSITION;
            out << YAML::Value << centerOfMassPos.first;
            out << YAML::Key << VERTICAL_POSITION;
            out << YAML::Value << centerOfMassPos.second;
            out << YAML::Value << YAML::EndMap;


            out << YAML::Value << YAML::EndMap;
        }
        out << YAML::Key << YAML::EndSeq;


        std::map<std::pair<float, float>, std::string> &conditions = logicGates.getConditions();
        out << YAML::Key << LOGICAL_GATES;
        out << YAML::Key << YAML::BeginSeq;
        for (auto &it : conditions) {
            std::pair<float, float> centerOfMassPos = it.first;
            matrixPosToMeters(centerOfMassPos, height);
            std::string &name = it.second;
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << STAGE_OBJECT_CONDITIONS;
            out << YAML::Value << name;
            out << YAML::Key << OBJECT_POSITION;

            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << HORIZONTAL_POSITION;
            out << YAML::Value << centerOfMassPos.first;
            out << YAML::Key << VERTICAL_POSITION;
            out << YAML::Value << centerOfMassPos.second;
            out << YAML::Value << YAML::EndMap;


            out << YAML::Value << YAML::EndMap;
        }
        out << YAML::Key << YAML::EndSeq;

        out << YAML::EndMap;
        std::ofstream fileOut(DIRECTORY +  stagePath + EXTENSION);
        fileOut << out.c_str();
    }
    catch(YAML::BadFile &e) {
        throw InvalidFile();
    }
}


void YamlManager::readStage(std::string& stagePath) {
    try {
        std::map<std::pair<int, int>, Object *> centerOfMassPosition;
        YAML::Node texturesInfo = YAML::LoadFile(DIRECTORY + stagePath + EXTENSION);
        const YAML::Node &node = texturesInfo[STAGE_ATTRIBUTES][STAGE_SIZE];
        int width = (int) node[VERTICAL_SIZE].as<float>();
        int i= 0;
        for (auto &texture : textures) {
            int currentID = texture.first;
            Object *object = texture.second;
            //if (currentID > 100) {return;}
            const YAML::Node &objects = texturesInfo[currentID][OBJECT_POSITION];
            for (YAML::const_iterator it = objects.begin();
                 it != objects.end(); ++it) {
                const YAML::Node &node = *it;
                float x = node[HORIZONTAL_POSITION].as<float>();
                float y = node[VERTICAL_POSITION].as<float>();
                std::pair<float, float> centerOfMass = std::make_pair(x, y);
                centerOfMassPosition[centerOfMass] = object;
                MetersToMatrixPos(centerOfMass, width);
                std::pair<int, int> matrixPos =
                        object->centerOfMassToMatrixPos(centerOfMass);
                tiles[matrixPos] = currentID;
            }
        }

        const YAML::Node &names = texturesInfo[STAGE_OBJECT_NAMES];
        Object *currentObject;
        std::pair<int, int> matrixPos;
        std::string name;
        for (YAML::const_iterator itNames = names.begin();
             itNames != names.end(); ++itNames) {
            const YAML::Node &node = *itNames;

            name = node[OBJECT_NAME].as<std::string>();
            float x = node[OBJECT_POSITION][HORIZONTAL_POSITION].as<float>();
            float y = node[OBJECT_POSITION][VERTICAL_POSITION].as<float>();

            std::pair<float, float> centerOfMass = std::make_pair(x, y);
            currentObject = centerOfMassPosition[centerOfMass];
            MetersToMatrixPos(centerOfMass, width);
            matrixPos = currentObject->centerOfMassToMatrixPos(centerOfMass);
            logicGates.setName(currentObject, matrixPos, name);
        }

        const YAML::Node &conditions = texturesInfo[LOGICAL_GATES];
        std::string condition;
        for (YAML::const_iterator itNames = conditions.begin();
             itNames != conditions.end(); ++itNames) {
            const YAML::Node &node = *itNames;

            condition = node[STAGE_OBJECT_CONDITIONS].as<std::string>();
            float x = node[OBJECT_POSITION][HORIZONTAL_POSITION].as<float>();
            float y = node[OBJECT_POSITION][VERTICAL_POSITION].as<float>();

            std::pair<float, float> centerOfMass = std::make_pair(x, y);
            currentObject = centerOfMassPosition[centerOfMass];
            MetersToMatrixPos(centerOfMass, width);
            matrixPos = currentObject->centerOfMassToMatrixPos(centerOfMass);
            logicGates.addCondition(currentObject, matrixPos, condition);
        }
    }
    catch(YAML::BadFile &e) {
        throw InvalidFile();
    }
}


void YamlManager::getObjects(Window &window, std::string& texturesPath) {
    YAML::Node texturesInfo = YAML::LoadFile(texturesPath);
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

    const YAML::Node& vEnergyBar = texturesInfo[V_ENERGY_BAR_KEY];
    for (YAML::const_iterator it = vEnergyBar.begin();
         it != vEnergyBar.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        VerticalEnergyBar* newObject =
                new VerticalEnergyBar(path, window, id, w, h);
        textures[id] = newObject;
    }

    const YAML::Node& hEnergyBar = texturesInfo[H_ENERGY_BAR_KEY];
    for (YAML::const_iterator it = hEnergyBar.begin();
         it != hEnergyBar.end(); ++it) {
        const YAML::Node& node = *it;
        int id = node[OBJECT_ID].as<int>();
        std::string path = node[IMAGE_PATH].as<std::string>();
        int w = node[OBJECT_WIDTH].as<int>();
        int h = node[OBJECT_HEIGHT].as<int>();
        HorizontalEnergyBar* newObject =
                new HorizontalEnergyBar(path, window, id, w, h);
        textures[id] = newObject;
    }
}

