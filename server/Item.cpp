//
// Created by cecix on 13/05/19.
//

#include "Item.h"

Item::Item(b2Body* body):
    body(body) {
}

float Item::getHorizontalPosition() {
    return -500;
}

float Item::getVerticalPosition() {
    return -500;
}

size_t Item::getSide() {
    return 0;
}