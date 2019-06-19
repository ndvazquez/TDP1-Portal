#include <utility>

#include <utility>

//
// Created by cecix on 19/05/19.
//

#include <string>

#include "Entity.h"

Entity::Entity(std::string type, b2Body* body):
    type(std::move(type)), body(body) {
}

const std::string& Entity::getType() {
    return type;
}

float Entity::getHorizontalPosition() {
    return body->GetPosition().x;
}

float Entity::getVerticalPosition() {
    return body->GetPosition().y;
}

float Entity::getHorizontalVelocity() {
    return body->GetLinearVelocity().x;
}

float Entity::getVerticalVelocity() {
    return body->GetLinearVelocity().y;
}

b2Body* Entity::getBody() {
    return body;
}
