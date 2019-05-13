//
// Created by cecix on 13/05/19.
//

#include "DiagonalMetalBlock.h"

DiagonalMetalBlock::DiagonalMetalBlock(size_t side, b2Body *body):
    Item(body),
    side(side), body(body) {
}