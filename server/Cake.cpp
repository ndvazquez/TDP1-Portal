//
// Created by cecix on 10/06/19.
//

#include <string>
#include "Cake.h"
#include "Chell.h"

#define cakeType "Cake"

Cake::Cake(b2Body* body):
        Entity(cakeType, body) {
    body->SetUserData(this);
}

void Cake::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        static_cast<Chell*>(entity)->win();
    }
}
