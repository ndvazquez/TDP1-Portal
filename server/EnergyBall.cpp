//
// Created by cecix on 19/05/19.
//

#include "EnergyBall.h"

// No se si agregarlo al escenario

EnergyBall::EnergyBall(b2Body* body):
    dynamic(body) {
}

void EnergyBall::fly(float velocity) { //TODO: velocity in the other direction
    dynamic.fly(velocity);
}