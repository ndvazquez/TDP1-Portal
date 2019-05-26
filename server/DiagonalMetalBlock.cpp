//
// Created by cecix on 13/05/19.
//
#define diagonalMetalBlockType "DiagonalMetalBlock"

#include "DiagonalMetalBlock.h"
#include "EnergyBall.h"
#include "Chell.h"

DiagonalMetalBlock::DiagonalMetalBlock(b2Body* body):
    Entity(diagonalMetalBlockType),
    body(body) {
    body->SetUserData(this); //to handle collisions
}

void DiagonalMetalBlock::handleCollision(Entity* entity) {
    if (entity->getType() == "EnergyBall") {
        static_cast<EnergyBall*>(entity)->changeDirection();
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
}

float DiagonalMetalBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float DiagonalMetalBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}

