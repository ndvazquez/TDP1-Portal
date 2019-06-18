//
// Created by cecix on 13/05/19.
//

#include <string>
#include <iostream>

#include "RockBlock.h"
#include "EnergyBall.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

RockBlock::RockBlock(b2Body* body):
    Entity(ROCK_BLOCK_NAME, body) {
    body->SetUserData(this); //to handle collisions
}

void RockBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == EB_NAME) {
        static_cast<EnergyBall*>(entity)->die();
    }
    if (type == CHELL_NAME) {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == BLUE_SHOT_NAME) {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        static_cast<OrangeShot*>(entity)->die();
    }
}
