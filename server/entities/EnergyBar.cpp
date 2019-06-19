//
// Created by cecix on 17/05/19.
//

#define energyBarType "EnergyBar"

#include "EnergyBar.h"
#include "BlueShot.h"
#include "OrangeShot.h"

EnergyBar::EnergyBar(b2Body *body):
    Entity(ENERGY_BAR_NAME, body) {
    this->body->SetUserData(this);
    this->timeStamp = std::chrono::system_clock::now();
}

void EnergyBar::handleCollision(Entity *entity) {
    const std::string& type = entity->getType();
    if (type == CHELL_NAME || type == EB_NAME) {
        disableBody();
    }
    if (type == ROCK_NAME) {
        dynamic_cast<Rock*>(entity)->die();
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
}

void EnergyBar::disableBody() {
    body->SetActive(false);
}

void EnergyBar::activateBody() {
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference <= 1100) return; //1.1 seconds to traspass
    this->timeStamp = std::chrono::system_clock::now();
    body->SetActive(true);
}
