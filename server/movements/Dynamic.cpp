//
// Created by cecix on 18/05/19.
//

#include <Box2D/Box2D.h>
#include "Dynamic.h"
#include "entities/Entity.h"
#include "stage-support/Coordinate.h"
#include "../../common/constants.h"

Dynamic::Dynamic(b2Body* body):
        body(body) {
}

void Dynamic::move(float force) {
}

bool Dynamic::teleport(Coordinate* coordinate, Direction type, bool keep_impulse) {
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference <= 100) return false; //0.1 seconds to teletransport
    timeStamp = std::chrono::system_clock::now();

    float x = coordinate->getX();
    float y = coordinate->getY();

    body->SetTransform(b2Vec2(x, y), 0);

    if (keep_impulse) return true;

    float gravity_force = -body->GetMass() * gameConfiguration.gravity;
    float net_force = gameConfiguration.elevationForce;

    if (type == UP) {
        float force_to_apply = net_force + gravity_force;
        body->ApplyForce(b2Vec2(0, force_to_apply),
                         body->GetWorldCenter(), true);
    }
    else if (type == DOWN) {
        float force_to_apply = -net_force + gravity_force;
        body->ApplyForce(b2Vec2(0, force_to_apply),
                         body->GetWorldCenter(), true);
    }
    else if (type == RIGHT) {
        body->ApplyForce(b2Vec2(net_force, 0),
                 body->GetWorldCenter(), true);
    }
    else if (type == LEFT) {
        body->ApplyForce(b2Vec2(-net_force, 0),
                         body->GetWorldCenter(), true);
    }
    return true;
}

void Dynamic::moveRight(float force) {
    if (body->GetLinearVelocity().x > 3) force = 0;
    body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);
}

void Dynamic::moveLeft(float force) {
    if (body->GetLinearVelocity().x < -3) force = 0;
    body->ApplyForce(b2Vec2(-force, 0), body->GetWorldCenter(), true);
}

void Dynamic::stop(float force) {
    force = 0;
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

bool Dynamic::handleCollisions() {
    b2ContactEdge* edge = body->GetContactList();
    bool resul = false;
    size_t counter = 0;
    while (edge != NULL) {
        b2Contact* contact = edge->contact;
        if (contact->IsTouching()) {
            void* user_A = contact->GetFixtureA()->GetBody()->GetUserData();
            void* user_B = contact->GetFixtureB()->GetBody()->GetUserData();
            if (user_A != NULL) {
                Entity* entity_A = static_cast<Entity*>(user_A);
                std::string typeA = entity_A->getType();
                if (typeA == "EnergyBall" || typeA == "Button") resul = true;
            }
            if (user_B != NULL) {
                Entity* entity_B = static_cast<Entity*>(user_B);
                std::string typeB = entity_B->getType();
                if (typeB == "EnergyBall" || typeB == "Button") resul = true;
            }
            if (user_A != NULL && user_B != NULL) {
                Entity* entity_A = static_cast<Entity*>(user_A);
                Entity* entity_B = static_cast<Entity*> (user_B);
                entity_A->handleCollision(entity_B);
            }
        }
        edge = edge->next;
        counter++;
    }
    return resul;
}

void Dynamic::flyRect(Direction eb_type) {
    float energy_ball_factor = gameConfiguration.energyBallImpulseFactor;
    float energy_ball_impulse = body->GetMass() * energy_ball_factor;

    if (eb_type == RIGHT) {
        if (body->GetLinearVelocity().x > 0) return;
        body->ApplyLinearImpulse(b2Vec2(energy_ball_impulse, 0),
                                 body->GetWorldCenter(), true);
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0));

    } else if (eb_type == LEFT) {
        if (body->GetLinearVelocity().x < 0) return;
        body->ApplyLinearImpulse(b2Vec2(-energy_ball_impulse, 0),
                                 body->GetWorldCenter(), true);
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0));

    } else if (eb_type == UP) {
        if (body->GetLinearVelocity().y > 0) return;
        body->ApplyLinearImpulse(b2Vec2(0, energy_ball_impulse),
                                 body->GetWorldCenter(), true);
        body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));

    } else if (eb_type == DOWN) {
        if (body->GetLinearVelocity().y < 0) return;
        body->ApplyLinearImpulse(b2Vec2(0, -energy_ball_impulse),
                                 body->GetWorldCenter(), true);
        body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
    }
}

void Dynamic::fly(b2Vec2 velocity) {
    body->SetGravityScale(0);

    float factor = gameConfiguration.directionFactor;
    body->SetLinearVelocity(b2Vec2(velocity.x*factor, velocity.y*factor));
}

void Dynamic::adjustJump() {
    body->SetGravityScale(0.6);
}

bool Dynamic::jump(bool chellFloor) {
    adjustJump();

    float epsilon = pow(10.5, -9);
    bool chell_is_still = body->GetLinearVelocity().y < epsilon
                        && body->GetLinearVelocity().y > -epsilon;

    if (! chell_is_still && ! chellFloor) return false;

    float initialVelocity = gameConfiguration.chellInitialVelocity;
    float impulse = body->GetMass() * initialVelocity;
    body->ApplyLinearImpulse(b2Vec2(0,impulse), body->GetWorldCenter() , true);

    return true;
}

Dynamic::~Dynamic() = default;
