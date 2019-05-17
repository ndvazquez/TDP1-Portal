//
// Created by cecix on 13/05/19.
//

#include "BrickBlock.h"

BrickBlock::BrickBlock(b2Body* body):
    body(body) {
}

float BrickBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float BrickBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}
