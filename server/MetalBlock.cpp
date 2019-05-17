//
// Created by cecix on 13/05/19.
//

#include "MetalBlock.h"

MetalBlock::MetalBlock(b2Body* body):
    body(body) {
}

float MetalBlock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float MetalBlock::getVerticalPosition() {
    return this->body->GetPosition().y;
}
