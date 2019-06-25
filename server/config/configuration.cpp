//
// Created by cecix on 21/06/19.
//

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include "configuration.h"

YAML::Node configuration_data = YAML::LoadFile("config/server_config.yaml");
const struct box2DConfiguration gameConfiguration = {
        .chellForce = configuration_data["chellForce"].as<float>(),
        .deltaError = configuration_data["deltaError"].as<float>(),
        .energyBallImpulseFactor = configuration_data["energyBallImpulseFactor"].as<float>(),
        .chellInitialVelocity = configuration_data["chellInitialVelocity"].as<float>(),
        .gravityJump = configuration_data["gravityJump"].as<float>(),
        .gravity = configuration_data["gravity"].as<float>(),
        .rockForce = configuration_data["rockForce"].as<float>(),
        .elevationForce = configuration_data["elevationForce"].as<float>(),
        .rockFriction = configuration_data["rockFriction"].as<float>(),
        .deathTimeEnergyBall = configuration_data["deathTimeEnergyBall"].as<float>(),
        .delayEnergyTransmitter = configuration_data["delayEnergyTransmitter"].as<float>(),
        .offsetEnergyTransmitter = configuration_data["offsetEnergyTransmitter"].as<float>(),
        .velocityDownload = configuration_data["velocityDownload"].as<float>(),
        .velocityRelease = configuration_data["velocityRelease"].as<float>(),
        .shotFactor = configuration_data["shotFactor"].as<float>(),
        .deathPinTool = configuration_data["deathPinTool"].as<float>(),
};
