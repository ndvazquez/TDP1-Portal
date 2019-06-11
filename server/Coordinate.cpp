//
// Created by cecix on 13/05/19.
//

#include "Coordinate.h"

Coordinate::Coordinate(float x_pos, float y_pos):
        x_pos(x_pos), y_pos(y_pos) {
}

float Coordinate::getX() {
    return x_pos;
}

float Coordinate::getY() {
    return y_pos;
}

bool Coordinate::operator==(const Coordinate& other) {
    return other.y_pos == this->y_pos && other.x_pos == this->x_pos;
}

bool Coordinate::operator!=(const Coordinate& other) {
    return other.y_pos != this->y_pos || other.x_pos != this->x_pos;
}
