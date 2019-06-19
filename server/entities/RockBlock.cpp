//
// Created by cecix on 13/05/19.
//

#include <string>
#include <iostream>

#include "RockBlock.h"
#include "entities/EnergyBall.h"
#include "entities/Chell.h"
#include "entities/BlueShot.h"
#include "OrangeShot.h"

RockBlock::RockBlock(b2Body* body):
    Entity(std::move(std::string(ROCK_BLOCK_NAME)), body) {
    body->SetUserData(this); //to handle collisions
}

void RockBlock::handleCollision(Entity* entity) {
    const std::string& type = entity->getType();
    if (type == EB_NAME) {
        dynamic_cast<EnergyBall*>(entity)->die();
    }
    if (type == CHELL_NAME) {
        dynamic_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
}
