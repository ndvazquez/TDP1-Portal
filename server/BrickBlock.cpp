//
// Created by cecix on 13/05/19.
//

#include "BrickBlock.h"

BrickBlock::BrickBlock(size_t side, b2Body *body):
    side(side), body(body) {
}

float BrickBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float BrickBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}


size_t BrickBlock::getSide() {
    return this->side;
}