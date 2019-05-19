//
// Created by cecix on 19/05/19.
//

#include "EnergyBallVertical.h"

EnergyBallVertical::EnergyBallVertical(b2Body* body):
        EnergyBall(body) {
    life_steps = 0;
}

void EnergyBallVertical::fly() {
    if (life_steps <= 1200) {
        dynamic.flyVertical(); //TODO: change this harcoded variable
    } else {
        throw EnergyBallDeadException();
    }
    life_steps++;
}