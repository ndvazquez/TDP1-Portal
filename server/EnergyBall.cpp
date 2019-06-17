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

EnergyBall::EnergyBall(b2Body* body, bool is_vertical):
    Entity(EB_NAME, body),
    dynamic(body) {
    this->is_vertical = is_vertical;
    body->SetUserData(this); //to handle collisions
    this->is_dead = false;
    this->timeStamp = std::chrono::system_clock::now();
}

void EnergyBall::fly() {
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference >= gameConfiguration.deathTimeEnergyBall) {
        die();
        return; //Dies after 10 seconds
    }
    if (is_vertical) {
        dynamic.flyVertical();
    } else {
        dynamic.flyHorizontal();
    }
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
    std::string type = entity->getType();
    if (type == ENERGY_BAR_NAME) {
        static_cast<EnergyBar*>(entity)->disableBody();
    }
    if (type == BRICK_BLOCK_NAME) {
        die();
    }
    if (type == DIAGONAL_METAL_BLOCK_NAME) {
        b2Vec2 velocity = static_cast<DiagonalMetalBlock*>(entity)->calculateVelocity();
        changeDirection(velocity);
    }
    if (type == CHELL_NAME) {
        static_cast<Chell*>(entity)->die();
        die();
    }
    if (type == PORTAL_NAME) {
        Portal* portal = static_cast<Portal*>(entity);
        Coordinate* target = portal->getTarget();
        if (target != nullptr) {
            teleport(target, portal->getPortalType());
        }
    }
    if (type == BLUE_SHOT_NAME) {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        static_cast<OrangeShot*>(entity)->die();
    }
    if (type == ER_RIGHT_NAME) {
        EnergyReceptorRight* er = static_cast<EnergyReceptorRight*>(entity);
        float x_er = er->getHorizontalPosition();
        float x_eb =getHorizontalPosition();
        if (x_eb > x_er) {
            er->activate();
            die();
        }
    }
    if (type == ER_LEFT_NAME) {
        EnergyReceptorLeft* er = static_cast<EnergyReceptorLeft*>(entity);
        float x_er = er->getHorizontalPosition();
        float x_eb = getHorizontalPosition();
        if (x_eb < x_er) {
            er->activate();
            die();
        }
    }
    if (type == ER_UP_NAME) {
        EnergyReceptorUp* er = static_cast<EnergyReceptorUp*>(entity);
        float y_er = er->getVerticalPosition();
        float y_eb = getVerticalPosition();
        if (y_eb > y_er) {
            er->activate();
            die();
        }
    }
    if (type == ER_DOWN_NAME) {
        EnergyReceptorDown* er = static_cast<EnergyReceptorDown*>(entity);
        float y_er = er->getVerticalPosition();
        float y_eb = getVerticalPosition();
        if (y_eb < y_er) {
            er->activate();
            die();
        }
    }
}

void EnergyBall::teleport(Coordinate* target, PortalType type) {
    this->dynamic.teleport(target, type);
}

void EnergyBall::update() {
    this->dynamic.handleCollisions();
}
