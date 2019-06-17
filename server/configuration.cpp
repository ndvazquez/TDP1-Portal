
//
// Created by cecix on 25/05/19.
//

#include "configuration.h"


struct box2DConfiguration gameConfiguration = {
        .chellForce = 500,
        .deltaError = 0.01,
        .energyBallImpulseFactor = 7,
        .chellInitialVelocity = 5.5,
        .gravityJump = -6,
        .gravity = -10,
        .rockForce = 250,
        .elevationForce = 300,
        .rockFriction = 4000,
        .deathTimeEnergyBall = 10000,
        .delayEnergyTransmitter = 3000,
        .offsetEnergyTransmitter = 2,
        .velocityDownload = 5,
        .velocityRelease = 2,
        .directionFactor = 10,
        .shotFactor = 6,
        .deathPinTool = 3000,
};
