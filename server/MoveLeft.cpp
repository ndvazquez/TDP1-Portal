//
// Created by cecix on 18/05/19.
//

#include "MoveLeft.h"

MoveLeft::MoveLeft(b2Body* body):
    Dynamic(body) {
}

void MoveLeft::move(float force) {
    moveLeft(force);
}

MoveLeft::~MoveLeft() {
}
