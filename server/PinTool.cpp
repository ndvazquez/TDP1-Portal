//
// Created by cecix on 17/06/19.
//

#include "PinTool.h"
#include "../common/constants.h"
#include "configuration.h"
#include "BlueShot.h"
#include "OrangeShot.h"

PinTool::PinTool(b2Body *body):
    Entity(PINTOOL_NAME, body) {
    body->SetUserData(this);
    this->timeStamp = std::chrono::system_clock::now();
    this->is_dead = false;
}

void PinTool::handleCollision(Entity *entity) {
    std::string type = entity->getType();
    if (type == BLUE_SHOT_NAME) {
        static_cast<BlueShot*>(entity)->die();
        die();
    }
    if (type == ORANGE_SHOT_NAME) {
        static_cast<OrangeShot*>(entity)->die();
        die();
    }
}

void PinTool::die() {
    this->is_dead = true;
}

bool PinTool::isDead() {
    return is_dead;
}

void PinTool::update() {
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference < gameConfiguration.deathPinTool) return;
    die();
    timeStamp = std::chrono::system_clock::now();
}
