//
// Created by cecix on 1/06/19.
//

#include "BluePortal.h"

BluePortal::BluePortal(b2Body* body):
    Portal(body) {
}

b2Body* BluePortal::getBody() {
    return body;
}