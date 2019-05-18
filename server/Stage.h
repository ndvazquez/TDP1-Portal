//
// Created by cecix on 12/05/19.
//

#ifndef PORTAL_STAGE_H
#define PORTAL_STAGE_H

#include <unordered_map>
#include <cstddef>
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

class Stage {
private:
    size_t width;
    size_t height;
    b2World* world;
    std::unordered_map<Coordinate*, BrickBlock*> brick_blocks;
    std::unordered_map<Coordinate*, MetalBlock*> metal_blocks;
    std::unordered_map<Coordinate*, DiagonalMetalBlock*> diagonal_metal_blocks;
    std::unordered_map<Coordinate*, EnergyTransmitter*> energy_transmitters;
    std::unordered_map<Coordinate*, Rock*> rocks;
    std::unordered_map<Coordinate*, EnergyBar*> energy_bars;
    std::unordered_map<Coordinate*, Button*> buttons;
    std::unordered_map<Coordinate*, Acid*> acids;

public:
    Stage(size_t width, size_t height);
    ~Stage();
    b2Body* addStaticSquare(size_t side, float x_pos, float y_pos);
    b2Body* addStaticRectangle(size_t v_side, size_t h_side, float x_pos, float y_pos);

    bool addBrickBlock(size_t side, float x_pos, float y_pos);
    bool addMetalBlock(size_t side, float x_pos, float y_pos);
    bool addDiagonalMetalBlock(size_t side, float x_pos, float y_pos, float angle);
    bool addEnergyTransmitter(size_t side, float x_pos, float y_pos);
    bool addRock(size_t side, float x_pos, float y_pos);
    bool addButton(size_t v_side, size_t h_side, float x_pos, float y_pos);
    bool addEnergyBar(size_t v_side, size_t h_side, float x_pos, float y_pos);
    bool addAcid(size_t v_side, size_t h_side, float x_pos, float y_pos);

    //bool addEnergyBall(size_t v_side, size_t h_side, float x_pos, float y_pos);

    BrickBlock* getBrickBlock(Coordinate* coordinate);
    MetalBlock* getMetalBlock(Coordinate* coordinate);
    EnergyTransmitter* getEnergyTransmitter(Coordinate* coordinate);
    DiagonalMetalBlock* getDiagonalMetalBlock(Coordinate* coordinate);
    Rock* getRock(Coordinate* coordinate);
    EnergyBar* getEnergyBar(Coordinate* coordinate);
    Button* getButton(Coordinate* coordinate);
    Acid* getAcid(Coordinate* coordinate);
};

#endif //PORTAL_STAGE_H
