//
// Created by cecix on 19/05/19.
//

#define energyBallType "EnergyBall"

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

EnergyBall::EnergyBall(b2Body* body, bool is_vertical):
    Entity(energyBallType, body),
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

void EnergyBall::changeDirection() {
    this->is_vertical = ! is_vertical;
}

void EnergyBall::die() {
    this->is_dead = true;
}

bool EnergyBall::isDead() {
    return is_dead;
}

bool EnergyBall::isVertical() {
    return this->is_vertical;
}

void EnergyBall::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "EnergyBar") {
        static_cast<EnergyBar*>(entity)->disableBody();
    }
    if (type == "BrickBlock") {
        die();
    }
    if (type == "DiagonalMetalBlock") {
        changeDirection();
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->die();
        die();
    }
    if (type == "Portal") {
        Portal* portal = static_cast<Portal*>(entity);
        Coordinate* target = portal->getTarget();
        if (target != nullptr) {
            teleport(target, portal->getPortalType());
        }
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
    if (type == "EnergyReceptorRight") {
        EnergyReceptorRight* er = static_cast<EnergyReceptorRight*>(entity);
        float x_er = er->getHorizontalPosition();
        float x_eb =getHorizontalPosition();
        if (x_eb > x_er) {
            er->activate();
            die();
        }
    }
    if (type == "EnergyReceptorLeft") {
        EnergyReceptorLeft* er = static_cast<EnergyReceptorLeft*>(entity);
        float x_er = er->getHorizontalPosition();
        float x_eb = getHorizontalPosition();
        if (x_eb < x_er) {
            er->activate();
            die();
        }
    }
    if (type == "EnergyReceptorUp") {
        EnergyReceptorUp* er = static_cast<EnergyReceptorUp*>(entity);
        float y_er = er->getVerticalPosition();
        float y_eb = getVerticalPosition();
        if (y_eb > y_er) {
            er->activate();
            die();
        }
    }
    if (type == "EnergyReceptorDown") {
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
