#include <utility>

//
// Created by cecix on 15/06/19.
//

#include "ItemActivable.h"

ItemActivable::ItemActivable(std::string type, b2Body *body):
    Entity(std::move(type), body) {
    this->state = OFF;
}

void ItemActivable::handleCollision(Entity* entity) {
}

bool ItemActivable::isActive() {
    return this->state == ON;
}

void ItemActivable::activate() {
    this->state = ON;
}

void ItemActivable::desactivate() {
    this->state = OFF;
}

SwitchState ItemActivable::getState() {
    return this->state;
}
