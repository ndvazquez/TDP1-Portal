//
// Created by cecix on 13/05/19.
//
#define diagonalMetalBlockType "DiagonalMetalBlock"

#include <iostream>
#include "DiagonalMetalBlock.h"
#include "EnergyBall.h"

DiagonalMetalBlock::DiagonalMetalBlock(b2Body* body):
    Entity(diagonalMetalBlockType),
    body(body) {
    body->SetUserData(this); //to handle collisions
}

void DiagonalMetalBlock::handleCollision(Entity* entity) {
    std::cout << "Entro al handlecollison de diagonalmetalblock" << std::endl;
    if (entity->getType() == "EnergyBall") {
        static_cast<EnergyBall*>(entity)->changeDirection();
    }
}

float DiagonalMetalBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float DiagonalMetalBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}

