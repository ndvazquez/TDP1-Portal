//
// Created by cecix on 20/05/19.
//

#include "MoveUp.h"

MoveUp::MoveUp(b2Body* body):
        Dynamic(body) {
}

void MoveUp::move(float force) {
    moveUp(force);
}

MoveUp::~MoveUp() {
}
