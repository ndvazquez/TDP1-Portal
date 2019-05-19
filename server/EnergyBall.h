//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENERGYBALL_H
#define PORTAL_ENERGYBALL_H

#include "Dynamic.h"


class EnergyBallDeadException : public std::exception {
    virtual const char* what() const throw() {
        std::string message = "This object isn't alive anymore!\n";
        return message.c_str();
    }
};


class EnergyBall {
private:
    Dynamic dynamic;
    size_t life_steps;

public:
    EnergyBall(b2Body* body);
    void fly();
    float getHorizontalPosition();
    float getVerticalPosition();
    float getHorizontalVelocity();
    float getVerticalVelocity();
};


#endif //PORTAL_ENERGYBALL_H
