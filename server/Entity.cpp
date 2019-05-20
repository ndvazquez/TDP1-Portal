//
// Created by cecix on 19/05/19.
//

#include "Entity.h"

Entity::Entity(std::string type):
    type(type) {
}

std::string Entity::getType() {
    return type;
}