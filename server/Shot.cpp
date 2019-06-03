//
// Created by cecix on 2/06/19.
//

#define shotType "Shot"

#include <string>
#include "Shot.h"

Shot::Shot(b2Body* body):
    Entity(shotType, body) {
    body->SetUserData(this);
}

void Shot::handleCollision(Entity* entity) {
    std::string type = entity->getType();
}
