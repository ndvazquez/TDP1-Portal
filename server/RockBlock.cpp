//
// Created by cecix on 13/05/19.
//

#include "RockBlock.h"

RockBlock::RockBlock(size_t side, b2Body *body):
    Item(body),
    side(side), body(body) {
}

float RockBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float RockBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}


size_t RockBlock::getSide() {
    return this->side;
}