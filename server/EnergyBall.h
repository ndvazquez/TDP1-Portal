//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENERGYBALL_H
#define PORTAL_ENERGYBALL_H

#include <string>
#include "Dynamic.h"
#include "Entity.h"

class EnergyBallDeadException : public std::exception {
    virtual const char* what() const throw() {
        std::string message = "This object isn't alive anymore!\n";
        return message.c_str();
    }
};


class EnergyBall: public Entity {
protected:
    Dynamic dynamic;
    size_t life_steps;

public:
    explicit EnergyBall(b2Body* body);
    virtual void fly();
    void die();
    bool isDead();
    float getHorizontalPosition();
    float getVerticalPosition();
    float getHorizontalVelocity();
    float getVerticalVelocity();
    virtual void handleCollision(Entity* entity) override;
};


#endif //PORTAL_ENERGYBALL_H
