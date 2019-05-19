//
// Created by cecix on 19/05/19.
//

#include "EnergyBallHorizontal.h"


EnergyBallHorizontal::EnergyBallHorizontal(b2Body* body):
    EnergyBall(body) {
    life_steps = 0;
}

void EnergyBallHorizontal::fly() {
    if (life_steps <= 1200) {
        dynamic.flyHorizontal(); //TODO: change this harcoded variable
    } else {
        throw EnergyBallDeadException();
    }
    life_steps++;
}