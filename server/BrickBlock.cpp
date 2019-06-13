//
// Created by cecix on 13/05/19.
//

#include <string>
#include <iostream>

#include "BrickBlock.h"
#include "EnergyBall.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

#define brickBlockType "BrickBlock"

BrickBlock::BrickBlock(b2Body* body):
    Entity(brickBlockType, body) {
    body->SetUserData(this); //to handle collisions
}

void BrickBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "EnergyBall") {
        static_cast<EnergyBall*>(entity)->die();
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
}
