//
// Created by cecix on 19/05/19.
//

#include <string>

#include "EnergyBall.h"

#define energyBallType "EnergyBall"
#define deathNumber 1200;

EnergyBall::EnergyBall(b2Body* body, bool is_vertical):
    Entity(std::string(energyBallType)),
    dynamic(body) {
    this->is_vertical = is_vertical;
    life_steps = 0;
    body->SetUserData(this); //to handle collisions
}

void EnergyBall::fly() {
    if (life_steps >= 1200) throw EnergyBallDeadException();
    if (is_vertical) {
        dynamic.flyVertical();
    } else {
        dynamic.flyHorizontal();
    }
    life_steps++;
}

void EnergyBall::changeDirection() {
    this->is_vertical = ! is_vertical;
}

void EnergyBall::die() {
    life_steps = deathNumber;
}

bool EnergyBall::isDead() {
    return life_steps >= deathNumber;
}

bool EnergyBall::isVertical() {
    return this->is_vertical;
}

void EnergyBall::handleCollision(Entity* entity) {
    if (entity->getType() == "BrickBlock") die();
    else if (entity->getType() == "DiagonalMetalBlock") changeDirection();
}

float EnergyBall::getHorizontalPosition() {
    return this->dynamic.getHorizontalPosition();
}

float EnergyBall::getVerticalPosition() {
    return this->dynamic.getVerticalPosition();
}

float EnergyBall::getHorizontalVelocity() {
    return this->dynamic.getHorizontalVelocity();
}

float EnergyBall::getVerticalVelocity() {
    return this->dynamic.getVerticalVelocity();
}
