//
// Created by cecix on 17/05/19.
//

#define energyBarType "EnergyBar"

#include "EnergyBar.h"
#include "BlueShot.h"
#include "OrangeShot.h"

EnergyBar::EnergyBar(b2Body *body):
    Entity(energyBarType, body) {
    this->body->SetUserData(this);
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
