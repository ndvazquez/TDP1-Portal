//
// Created by cecix on 19/05/19.
//

#include <string>
#include <iostream>
#include "EnergyBall.h"
#include "Chell.h"
#include "EnergyBar.h"
#include "BlueShot.h"
#include "OrangeShot.h"
#include "EnergyReceptorRight.h"
#include "EnergyReceptorLeft.h"
#include "EnergyReceptorUp.h"
#include "EnergyReceptorDown.h"
#include "DiagonalMetalBlock.h"

EnergyBall::EnergyBall(b2Body* body, Direction eb_type):
    Entity(EB_NAME, body),
    dynamic(body) {
    this->eb_type = eb_type;
    body->SetUserData(this); //to handle collisions
    this->is_dead = false;
    this->timeStamp = std::chrono::system_clock::now();
    body->SetGravityScale(0);
}

void EnergyBall::fly() {
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference >= gameConfiguration.deathTimeEnergyBall) {
        die();
        return; //Dies after 10 seconds
    }
    dynamic.flyRect(eb_type);
}

void EnergyBall::applyOrientation(Direction direction) {
    this->eb_type = direction;
}

void EnergyBall::changeDirection(b2Vec2 velocity) {
    this->dynamic.fly(velocity);
}

void EnergyBall::die() {
    this->is_dead = true;
}

bool EnergyBall::isDead() {
    return is_dead;
}

void EnergyBall::handleCollision(Entity* entity) {
    const std::string& type = entity->getType();
    if (type == ENERGY_BAR_NAME) {
        dynamic_cast<EnergyBar*>(entity)->disableBody();
    }
    if (type == ROCK_BLOCK_NAME) {
        die();
    }

    if (type == METAL_BLOCK_NAME) {
        invertDirection();
    }

    if (type == DIAGONAL_METAL_BLOCK_NAME) {
        b2Vec2 velocity = dynamic_cast<DiagonalMetalBlock*>(entity)->calculateVelocity();
        changeDirection(velocity);
    }
    if (type == CHELL_NAME) {
        dynamic_cast<Chell*>(entity)->die();
        die();
    }
    if (type == PORTAL_NAME) {
        Portal* portal = dynamic_cast<Portal*>(entity);
        Coordinate* target = portal->getTarget();
        if (target != nullptr) {
            Direction portal_type = portal->getPortalType();
            applyOrientation(portal_type);
            teleport(target, portal->getPortalType());
        }
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
    if (type == ER_RIGHT_NAME) {
        EnergyReceptorRight* er = dynamic_cast<EnergyReceptorRight*>(entity);
        float x_er = er->getHorizontalPosition();
        float x_eb =getHorizontalPosition();
        if (x_eb > x_er) {
            er->activate();
            die();
        }
    }
    if (type == ER_LEFT_NAME) {
        EnergyReceptorLeft* er = dynamic_cast<EnergyReceptorLeft*>(entity);
        float x_er = er->getHorizontalPosition();
        float x_eb = getHorizontalPosition();
        if (x_eb < x_er) {
            er->activate();
            die();
        }
    }
    if (type == ER_UP_NAME) {
        EnergyReceptorUp* er = dynamic_cast<EnergyReceptorUp*>(entity);
        float y_er = er->getVerticalPosition();
        float y_eb = getVerticalPosition();
        if (y_eb > y_er) {
            er->activate();
            die();
        }
    }
    if (type == ER_DOWN_NAME) {
        EnergyReceptorDown* er = dynamic_cast<EnergyReceptorDown*>(entity);
        float y_er = er->getVerticalPosition();
        float y_eb = getVerticalPosition();
        if (y_eb < y_er) {
            er->activate();
            die();
        }
    }
    if (type == ROCK_NAME) {
        dynamic_cast<Rock*>(entity)->die();
        die();
    }
}

void EnergyBall::invertDirection() {
    if (eb_type == RIGHT) {
        eb_type = LEFT;
    } else if (eb_type == LEFT) {
        eb_type = RIGHT;
    } else if (eb_type == UP) {
        eb_type = DOWN;
    } else if (eb_type == DOWN) {
        eb_type = UP;
    }
}

void EnergyBall::teleport(Coordinate* target, Direction type) {
    this->dynamic.teleport(target, type, true);
}

void EnergyBall::update() {
    this->dynamic.handleCollisions();
}
