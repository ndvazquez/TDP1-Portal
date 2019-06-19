//
// Created by cecix on 12/05/19.
//

#ifndef PORTAL_STAGE_H
#define PORTAL_STAGE_H

#include <unordered_map>
#include <cstddef>
#include <string>
#include <chrono>
#include "../../json/json.hpp"

#include "Coordinate.h"
#include "entities/RockBlock.h"
#include "entities/MetalBlock.h"
#include "entities/DiagonalMetalBlock.h"
#include "entities/EnergyTransmitter.h"
#include "entities/Rock.h"
#include "entities/EnergyBar.h"
#include "entities/Button.h"
#include "entities/Acid.h"
#include "entities/Chell.h"
#include "entities/EnergyBall.h"
#include "entities/Floor.h"
#include "entities/BlueShot.h"
#include "entities/OrangeShot.h"
#include "entities/Gate.h"
#include "entities/Cake.h"
#include "PhysicsWorld.h"
#include "entities/EnergyReceptor.h"
#include "entities/ItemActivable.h"

class StageBadIdentifierException : public std::exception {
    virtual const char* what() const throw() {
        std::string message = "This object doesn't belong in the stage!\n";
        return message.c_str();
    }
};

class Stage {
private:
    PhysicsWorld* world;
    Cake* cake;
    bool end_of_game;

    std::unordered_map<Coordinate*, RockBlock*> brick_blocks;
    std::unordered_map<Coordinate*, MetalBlock*> metal_blocks;
    std::unordered_map<Coordinate*, DiagonalMetalBlock*> diagonal_metal_blocks;

    std::unordered_map<std::string, EnergyBar*> energy_bars;
    std::unordered_map<std::string, Gate*> gates;
    std::unordered_map<std::string, Button*> buttons;
    std::unordered_map<std::string, Acid*> acids;
    std::unordered_map<std::string, Chell*> chells;
    std::unordered_map<std::string, EnergyBall*> energy_balls;
    std::unordered_map<std::string, BlueShot*> blue_shots;
    std::unordered_map<std::string, OrangeShot*> orange_shots;
    std::unordered_map<std::string, EnergyTransmitter*>
    energy_transmitters_horizontals;
    std::unordered_map<std::string, EnergyTransmitter*>
    energy_transmitters_verticals;
    std::unordered_map<std::string, EnergyReceptor*>
    energy_receptors;
    std::unordered_map<std::string, Rock*> rocks;
    std::unordered_map<std::string, Portal*> portals; //Id == shots

public:
    Stage(size_t width, size_t height);
    ~Stage();

    void addBlock(std::string identifier, float side, float x_pos, float y_pos);
    void addDiagonalBlock(float side, float x_pos, float y_pos, float angle);
    void addEnergyBall(std::string identifier, std::string id,
            float side, float x_pos, float y_pos);
    void addEnergyItem(std::string identifier, std::string id, float side,
                              float x_pos, float y_pos);
    void addShot(std::string identifier, std::string id, float v_side,
    float h_side, Chell* chell, Coordinate* target);
    void addElement(std::string identifier, std::string id, float v_side,
            float h_side, float x_pos, float y_pos);
    void addRock(std::string id, float side,
                 float x_pos, float y_pos);
    void addGate(std::string id, float v_side, float h_side, float x_pos,
            float y_pos, std::unordered_map<std::string, ItemActivable*> items,
                 std::string logic);
    void addChell(std::string id, float v_side, float h_side,
            float x_pos, float y_pos);

    Rock* getClosestRock(float x_pos, float y_pos);
    void managePortals(Chell* chell, std::string id);
    void step();

    Cake* getCake();
    RockBlock* getBrickBlock(Coordinate* coordinate);
    MetalBlock* getMetalBlock(Coordinate* coordinate);
    DiagonalMetalBlock* getDiagonalMetalBlock(Coordinate* coordinate);

    EnergyBar* getEnergyBar(std::string id);
    Button* getButton(std::string id);
    Acid* getAcid(std::string id);
    Chell* getChell(std::string id);
    EnergyBall* getEnergyBall(std::string id);
    BlueShot* getBlueShot(std::string id);
    OrangeShot* getOrangeShot(std::string id);
    EnergyTransmitter* getEnergyTransmitter(std::string id);
    Rock* getRock(std::string id);
    Gate* getGate(std::string id);
    EnergyReceptor* getEnergyReceptor(std::string id);
    nlohmann::json getCurrentState();
};

#endif //PORTAL_STAGE_H