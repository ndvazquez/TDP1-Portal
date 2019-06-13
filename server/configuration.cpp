
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
<<<<<<< HEAD
        .rockForce = 50,
        .elevationForce = 5,
=======
        .rockForce = 250,
        .elevationForce = 3000,
>>>>>>> f289a085db3cf84f6a69b8b5ceac0813a26a9b27
        .rockFriction = 4000,
        .deathTimeEnergyBall = 10000,
        .delayEnergyTransmitter = 3000,
        .offsetEnergyTransmitter = 2,
};
