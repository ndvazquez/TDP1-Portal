//
// Created by cecix on 12/05/19.
//

#ifndef PORTAL_STAGE_H
#define PORTAL_STAGE_H

#include <unordered_map>
#include <cstddef>
#include <string>
#include <chrono>
#include "../json/json.hpp"

#include "Box2D/Box2D.h"
#include "Coordinate.h"
#include "BrickBlock.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"
#include "EnergyTransmitter.h"
#include "Rock.h"
#include "EnergyBar.h"
#include "Button.h"
#include "Acid.h"
#include "Chell.h"
#include "EnergyBall.h"
#include "Floor.h"
#include "BlueShot.h"
#include "OrangeShot.h"
#include "Gate.h"
#include "Cake.h"

class StageOutOfRangeException : public std::exception {
    virtual const char* what() const throw() {
        std::string message = "This object doesn't fit in the stage!\n";
        return message.c_str();
    }
};

class Stage {
private:
    size_t width;
    size_t height;
    b2World* world;
    Floor* floor;
    Cake* cake;
    std::chrono::system_clock::time_point timeStamp;

    std::unordered_map<Coordinate*, BrickBlock*> brick_blocks;
    std::unordered_map<Coordinate*, MetalBlock*> metal_blocks;
    std::unordered_map<Coordinate*, DiagonalMetalBlock*> diagonal_metal_blocks;
    std::unordered_map<Coordinate*, EnergyBar*> energy_bars;

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
    std::unordered_map<std::string, Rock*> rocks;
    std::unordered_map<std::string, Portal*> portals; //Id == shots

public:
    Stage(size_t width, size_t height);
    ~Stage();
    b2Body* addStaticRectangle(float v_side, float h_side,
            float x_pos, float y_pos);
    b2Body* addDynamicRectangle(float v_side, float h_side,
            float x_pos, float y_pos);

    void addCake(float side, float x_pos, float y_pos);
    void addBrickBlock(float side, float x_pos, float y_pos);
    void addMetalBlock(float side, float x_pos, float y_pos);
    void addDiagonalMetalBlock(float side, float x_pos,
            float y_pos);
    void addEnergyBar(float v_side, float h_side, float x_pos, float y_pos);


    void addGate(std::string id, float v_side, float h_side, float x_pos,
            float y_pos, std::unordered_map<std::string, Button*> buttons,
                 std::string logic);
    void addButton(std::string id, float v_side, float h_side,
            float x_pos, float y_pos);
    void addAcid(std::string id, float v_side, float h_side,
            float x_pos, float y_pos);
    void addChell(std::string id, float v_side, float h_side,
            float x_pos, float y_pos);
    void addEnergyBallHorizontal(std::string id, float side,
            float x_pos, float y_pos);
    void addEnergyBallVertical(std::string id, float side,
            float x_pos, float y_pos);
    void addBlueShot(std::string id, float v_side,
            float h_side, Chell* chell, Coordinate* target);
    void addOrangeShot(std::string id, float v_side, float h_side,
            Chell* chell, Coordinate* target);
    void addEnergyTransmitterRight(std::string id, float side,
            float x_pos, float y_pos);
    void addEnergyTransmitterLeft(std::string id, float side,
            float x_pos, float y_pos);
    void addEnergyTransmitterUp(std::string id, float side,
            float x_pos, float y_pos);
    void addEnergyTransmitterDown(std::string id, float side,
            float x_pos, float y_pos);
    void addRock(std::string id, float side,
            float x_pos, float y_pos);
    void addPortal(std::string id, float v_side, float h_side,
            Coordinate* origin, Coordinate* target,
            PortalOrientation orientation);
    void managePortals(Chell* chell, std::string id);
    void step();

    Cake* getCake();
    BrickBlock* getBrickBlock(Coordinate* coordinate);
    MetalBlock* getMetalBlock(Coordinate* coordinate);
    DiagonalMetalBlock* getDiagonalMetalBlock(Coordinate* coordinate);
    EnergyBar* getEnergyBar(Coordinate* coordinate);

    Button* getButton(std::string id);
    Acid* getAcid(std::string id);
    Chell* getChell(std::string id);
    EnergyBall* getEnergyBall(std::string id);
    BlueShot* getBlueShot(std::string id);
    OrangeShot* getOrangeShot(std::string id);
    EnergyTransmitter* getEnergyTransmitter(std::string id);
    Rock* getRock(std::string id);

    nlohmann::json getCurrentState();
};

#endif //PORTAL_STAGE_H
