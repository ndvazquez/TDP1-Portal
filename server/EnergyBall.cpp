//
// Created by cecix on 19/05/19.
//

#define energyBallType "EnergyBall"

#include <string>

#include "EnergyBall.h"
#include "Chell.h"
#include "EnergyBar.h"

EnergyBall::EnergyBall(b2Body* body, bool is_vertical):
    Entity(energyBallType, body),
    dynamic(body) {
    this->is_vertical = is_vertical;
    body->SetUserData(this); //to handle collisions
    this->is_dead = false;
    this->timeStamp = std::chrono::system_clock::now();
}

void EnergyBall::fly() {
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference >= gameConfiguration.deathTimeEnergyBall) {
        die();
        return; //Dies after 10 seconds
    }
    if (is_vertical) {
        dynamic.flyVertical();
    } else {
        dynamic.flyHorizontal();
    }
}

void EnergyBall::changeDirection() {
    this->is_vertical = ! is_vertical;
}

void EnergyBall::die() {
    this->is_dead = true;
}

bool EnergyBall::isDead() {
    return is_dead;
}

bool EnergyBall::isVertical() {
    return this->is_vertical;
}

void EnergyBall::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "EnergyBar") {
        static_cast<EnergyBar*>(entity)->disableBody();
    }
    if (type == "BrickBlock") {
        die();
    }
    if (type == "DiagonalMetalBlock") {
        changeDirection();
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->die();
        die();
    }
}
