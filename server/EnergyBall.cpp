//
// Created by cecix on 19/05/19.
//

#include <iostream>
#include "EnergyBall.h"

#define energyBallType "EnergyBall"
#define deathNumber 1200;

EnergyBall::EnergyBall(b2Body* body):
    Entity(std::string(energyBallType)),
    dynamic(body) {
    life_steps = 0;
    body->SetUserData(this); //to handle collisions
}

void EnergyBall::fly() {
}

void EnergyBall::die() {
    life_steps = deathNumber;
}

void EnergyBall::handleCollision(Entity* entity) {
    if (entity->getType() == "BrickBlock") die();
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
