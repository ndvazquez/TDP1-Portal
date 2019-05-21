//
// Created by cecix on 20/05/19.
//

#include "MoveDown.h"

MoveDown::MoveDown(b2Body* body):
        Dynamic(body) {
}

void MoveDown::move(float force) {
    moveDown(force);
}

MoveDown::~MoveDown() {
}
