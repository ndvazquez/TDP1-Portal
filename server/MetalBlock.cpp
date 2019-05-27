//
// Created by cecix on 13/05/19.
//

#define metalBlockType "MetalBlock"

#include <iostream>
#include "MetalBlock.h"
#include "Chell.h"

MetalBlock::MetalBlock(b2Body* body):
    Entity(metalBlockType),
    body(body) {
    body->SetUserData(this);
}

float MetalBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float MetalBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}

void MetalBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == "Rock") {
    }
}
