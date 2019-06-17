//
// Created by cecix on 25/05/19.
//

#ifndef PORTAL_CONFIGURATION_H
#define PORTAL_CONFIGURATION_H

struct box2DConfiguration {
    float chellForce;
    float deltaError;
    int energyBallImpulseFactor;
    float chellInitialVelocity;
    float gravityJump;
    float gravity;
    float rockForce;
    float elevationForce;
    float rockFriction;
    float deathTimeEnergyBall;
    float delayEnergyTransmitter;
    float offsetEnergyTransmitter;
    float velocityDownload;
    float velocityRelease;
    float directionFactor;
    float shotFactor;
    float deathPinTool;
};

extern struct box2DConfiguration gameConfiguration;

#endif //PORTAL_CONFIGURATION_H
