//
// Created by cecix on 13/05/19.
//

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
    calculateCenterMass();
}

void DiagonalMetalBlock::calculateCenterMass() {
    b2Fixture* fixture = body->GetFixtureList();
    b2PolygonShape* shape = (b2PolygonShape*) fixture->GetShape();
    b2Vec2* vector;
    vector = shape->m_vertices;
    
    for (int i = 0; i < 3; i++) {
        if (i == 2 && angle == 135) {
            x_diagonal_center_mass = getHorizontalPosition() - vector[i].x;
            y_diagonal_center_mass = getVerticalPosition() - vector[i].y;
        } else if (i == 1 && angle == 315) {
            x_diagonal_center_mass = getHorizontalPosition();
            y_diagonal_center_mass = getVerticalPosition() + vector[i].y - 1;
        } else if (i == 1 && angle == 225) {
            x_diagonal_center_mass = getHorizontalPosition() + vector[i].x + 1;
            y_diagonal_center_mass = getVerticalPosition() + vector[i].y - 1;
        } else if (i == 2 && angle == 45) {
            x_diagonal_center_mass = getHorizontalPosition();
            y_diagonal_center_mass = getVerticalPosition() - vector[i].y;
        }
    }
}

float DiagonalMetalBlock::getXCM() {
    return x_diagonal_center_mass;
}

float DiagonalMetalBlock::getYCM() {
    return y_diagonal_center_mass;
}

Direction DiagonalMetalBlock::getDirection(Direction eb_type) {
    if (angle == 45) {
        if (eb_type == RIGHT) return UP;
        if (eb_type == DOWN) return LEFT;
    } else if (angle == 135) {
        if (eb_type == LEFT) return UP;
        if (eb_type == DOWN) return RIGHT;
    } else if (angle == 225) {
        if (eb_type == UP) return RIGHT;
        if (eb_type == LEFT) return DOWN;
    } else if (angle == 315) {
        if (eb_type == UP) return LEFT;
        if (eb_type == RIGHT) return DOWN;
    }
    return eb_type;
}

void DiagonalMetalBlock::handleCollision(Entity* entity) {
    const std::string& type = entity->getType();
    if (type == EB_NAME) {
        Direction eb_type = dynamic_cast<EnergyBall*>(entity)->getDirection();
        Direction direction = getDirection(eb_type);
        dynamic_cast<EnergyBall*>(entity)->applyOrientation(direction);
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
    if (type == CHELL_NAME) {
        dynamic_cast<Chell*>(entity)->onFloor(true);
    }
}
