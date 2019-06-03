//
// Created by cecix on 13/05/19.
//

#define metalBlockType "MetalBlock"

#include <string>
#include "MetalBlock.h"
#include "Chell.h"

MetalBlock::MetalBlock(b2Body* body):
    Entity(metalBlockType, body) {
    body->SetUserData(this);
}

void MetalBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == "Rock") {
        static_cast<Rock*>(entity)->onFloor(true);
    }
}
