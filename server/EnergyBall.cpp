//
// Created by cecix on 19/05/19.
//

#include <iostream>
#include "EnergyBall.h"

// No se si agregarlo al escenario

EnergyBall::EnergyBall(b2Body* body):
    dynamic(body) {
    life_steps = 0;
}

void EnergyBall::fly() { //TODO: velocity in the other direction
    if (life_steps <= 1200) {
        dynamic.fly(); //TODO: change this harcoded variable
    } else {
        throw EnergyBallDeadException();
    }
    life_steps++;

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

