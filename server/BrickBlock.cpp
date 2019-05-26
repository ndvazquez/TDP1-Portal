//
// Created by cecix on 13/05/19.
//

#include "BrickBlock.h"
#include "EnergyBall.h"
#include "Chell.h"

#define brickBlockType "BrickBlock"

BrickBlock::BrickBlock(b2Body* body):
    Entity(brickBlockType),
    body(body) {
    body->SetUserData(this); //to handle collisions
}

float BrickBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float BrickBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}

void BrickBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "EnergyBall") {
        static_cast<EnergyBall*>(entity)->die();
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
}
