//
// Created by cecix on 13/05/19.
//

#include <iostream>
#include "Box2D/Box2D.h"
#include "DiagonalMetalBlock.h"
#include "EnergyBall.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

DiagonalMetalBlock::DiagonalMetalBlock(b2Body* body, float angle):
    Entity(DIAGONAL_METAL_BLOCK_NAME, body) {
    body->SetUserData(this); //to handle collisions
    this->angle = angle;
}

void DiagonalMetalBlock::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "EnergyBall") {
        b2Vec2 velocity = calculateVelocity();
        static_cast<EnergyBall*>(entity)->changeDirection(velocity);
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
}

b2Vec2 DiagonalMetalBlock::calculateVelocity() {
    b2Fixture* fixture = body->GetFixtureList();
    b2PolygonShape* shape = (b2PolygonShape*) fixture->GetShape();
    b2Vec2* vector;
    vector = shape->m_vertices;

    float x_rect = 0;
    float y_rect = 0;

    for (int i = 0; i < 3; i++) {
        if (i == 2 && angle == 135) {
            x_rect = -vector[i].x;
            y_rect = -vector[i].y;
        }
        if (i == 0 && angle == 45) {
            x_rect = -vector[i].x;
            y_rect = -vector[i].y;
        }
        if (i == 1 && (angle == 225 || angle == 315)) {
            x_rect = -vector[i].x;
            y_rect = -vector[i].y;
        }
    }

    b2Vec2 velocity(x_rect, y_rect);
    velocity.Normalize();
    return velocity;
}
