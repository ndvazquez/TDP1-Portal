//
// Created by cecix on 18/05/19.
//

#include "MoveRight.h"

MoveRight::MoveRight(b2Body* body):
    Dynamic(body) {
}

void MoveRight::move() {
    moveRight();
}

MoveRight::~MoveRight() {
}