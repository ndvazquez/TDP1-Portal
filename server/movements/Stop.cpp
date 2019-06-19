//
// Created by cecix on 18/05/19.
//

#include "Stop.h"

Stop::Stop(b2Body* body):
    Dynamic(body) {
}

void Stop::move(float force) {
    stop(force);
}

Stop::~Stop() = default;
