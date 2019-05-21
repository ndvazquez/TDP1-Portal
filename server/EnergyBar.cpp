//
// Created by cecix on 17/05/19.
//

#include "EnergyBar.h"

EnergyBar::EnergyBar(b2Body *body):
    body(body) {
}

float EnergyBar::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float EnergyBar::getVerticalPosition() {
    return this->body->GetPosition().y;
}
