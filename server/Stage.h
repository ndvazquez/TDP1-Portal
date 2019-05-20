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
#include "../editor/MouseButtonDown.h"

class Stage {
private:
    size_t width;
    size_t height;
    b2World* world;
    std::unordered_map<Coordinate*, BrickBlock*> brick_blocks;
    std::unordered_map<Coordinate*, MetalBlock*> metal_blocks;
    std::unordered_map<Coordinate*, DiagonalMetalBlock*> diagonal_metal_blocks;

public:
    Stage(size_t width, size_t height);
    ~Stage();
    bool addBrickBlock(size_t side, float x_pos, float y_pos);
    bool addMetalBlock(size_t side, float x_pos, float y_pos);
    bool addDiagonalMetalBlock(size_t side, float x_pos, float y_pos, float angle);
    bool addButton(float x_pos, float y_pos);
    bool addRock(float x_pos, float y_pos);
    bool addEnergyTransmitter(float x_pos, float y_pos);
    bool addEnergyBar(float x_pos, float y_pos);
    BrickBlock* getBrickBlock(Coordinate* coordinate);
    MetalBlock* getMetalBlock(Coordinate* coordinate);
    DiagonalMetalBlock* getDiagonalMetalBlock(Coordinate* coordinate);
};

#endif //PORTAL_STAGE_H
