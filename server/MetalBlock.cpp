//
// Created by cecix on 13/05/19.
//

#include "MetalBlock.h"

MetalBlock::MetalBlock(size_t side, b2Body* body):
    side(side), body(body) {
}

float MetalBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float MetalBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}

size_t MetalBlock::getSide() {
    return this->side;
}