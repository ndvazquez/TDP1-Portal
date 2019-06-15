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
    std::string type = entity->getType();
    if (type == "Chell" || type == "EnergyBall") {
        disableBody();
    }
    if (type == "Rock") {
        static_cast<Rock*>(entity)->die();
    }
    //Didnt handle special cases of shots because it dies anyway
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
