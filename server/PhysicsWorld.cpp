//
// Created by cecix on 15/06/19.
//

#include <iostream>
#include "PhysicsWorld.h"
#include "../common/constants.h"

PhysicsWorld::PhysicsWorld(b2World *world, size_t width, size_t height):
    world(world), width(width), height(height) {

    b2BodyDef body;
    body.type = b2_staticBody;
    b2PolygonShape shape;

    b2Body* body_floor = addStaticRectangle(4, width, width/2, -2);
    Floor* floor = new Floor(body_floor);
    this->floor = floor;

    body.position.Set(width/2, height + 2);
    shape.SetAsBox(width/2, 2);
    this->world->CreateBody(&body)->CreateFixture(&shape, 0.0f);

    body.position.Set(-2, height/2);
    shape.SetAsBox(2, height/2);
    this->world->CreateBody(&body)->CreateFixture(&shape, 0.0f);

    body.position.Set(width + 2, height/2);
    shape.SetAsBox(2, height/2);
    this->world->CreateBody(&body)->CreateFixture(&shape, 0.0f);
}

 b2Body* PhysicsWorld::addStaticRectangle(float v_side, float h_side,
                                   float x_pos, float y_pos) {
     if ( x_pos > width || y_pos > height) {
         throw WorldOutOfRangeException();
     }

     b2BodyDef body;
     body.type = b2_staticBody;
     body.position.Set(x_pos, y_pos);

     b2Body* rectangle_body = this->world->CreateBody(&body);

     b2PolygonShape shape;
     shape.SetAsBox(h_side/2, v_side/2);

     b2FixtureDef fixture;
     fixture.shape = &shape;
     rectangle_body->CreateFixture(&fixture);

     return rectangle_body;
 }

 b2Body* PhysicsWorld::addDynamicRectangle(float v_side, float h_side,
                                    float x_pos, float y_pos) {
     if (x_pos > width || y_pos > height) {
         throw WorldOutOfRangeException();
     }

     b2BodyDef body;
     body.type = b2_dynamicBody;
     body.position.Set(x_pos, y_pos);
     body.fixedRotation = true;

     b2Body* rectangle_body = this->world->CreateBody(&body);

     b2PolygonShape shape;
     shape.SetAsBox(h_side/2, v_side/2);

     b2FixtureDef fixture;
     fixture.shape = &shape;
     fixture.density = 1;
     fixture.friction = 0.2;
     rectangle_body->CreateFixture(&fixture);

     return rectangle_body;
 }

b2Body* PhysicsWorld::addTriangle(float side, float x_pos, float y_pos, float angle) {
    if (x_pos > width || y_pos > height) {
        throw WorldOutOfRangeException();
    }

    b2BodyDef body;
    body.type = b2_staticBody;
    body.position.Set(x_pos, y_pos);
    body.fixedRotation = true;

    b2Body* triangle_body = this->world->CreateBody(&body);

    b2Vec2 vertices[3];

    if (angle == 45) {
        vertices[0].Set((-2.0/3) * side, (-1.0/3) * side);
        vertices[1].Set((1.0/3) * side, (2.0/3) * side);
        vertices[2].Set((1.0/3) * side,  (-1.0/3) * side);
    } else if (angle == 135) {
        std::cout << "Seteo bien" << std::endl;
        vertices[0].Set((-1.0/3) * side, (-1.0/3) * side);
        vertices[1].Set((-1.0/3) * side, (2.0/3) * side);
        vertices[2].Set((2.0/3) * side,  (-1.0/3) * side);
    } else if (angle == 225) {
        vertices[0].Set((-1.0/3) * side, (-2.0/3) * side);
        vertices[1].Set((-1.0/3) * side, (1.0/3) * side);
        vertices[2].Set((2.0/3) * side,  (1.0/3) * side);
    } else {
        vertices[0].Set((-2.0/3) * side, (1.0/3) * side);
        vertices[1].Set((1.0/3) * side, (1.0/3) * side);
        vertices[2].Set((1.0/3) * side,  (-2.0/3) * side);
    }

    b2PolygonShape shape;
    shape.Set(vertices, 3);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1;
    fixture.friction = 0.2;
    triangle_body->CreateFixture(&fixture);

    return triangle_body;
}

b2Body* PhysicsWorld::addDynamicRectangleWithWheels(float v_side, float h_side,
         float x_pos, float y_pos) {
    if (x_pos > width || y_pos > height) {
        throw WorldOutOfRangeException();
    }

     b2Body* wheel_body = addDynamicRectangle(v_side - CHELL_WHEEL_RADIUS, h_side, x_pos, y_pos);

     b2CircleShape circleShape;
     circleShape.m_radius = CHELL_WHEEL_RADIUS;
     circleShape.m_p.Set(CHELL_WHEEL_RADIUS, -(v_side - CHELL_WHEEL_RADIUS)/2);

     b2FixtureDef fixture;
     fixture.shape = &circleShape;
     wheel_body->CreateFixture(&fixture);

     b2CircleShape circleShape2;
     circleShape2.m_radius = CHELL_WHEEL_RADIUS;
     circleShape2.m_p.Set(-CHELL_WHEEL_RADIUS, -(v_side - CHELL_WHEEL_RADIUS)/2);

     b2FixtureDef fixture2;
     fixture2.shape = &circleShape2;
     wheel_body->CreateFixture(&fixture2);

     wheel_body->SetFixedRotation(true);
     return wheel_body;
}

 void PhysicsWorld::destroyBody(b2Body* body) {
    world->DestroyBody(body);
}

bool PhysicsWorld::hasObject(b2Body* body) {
    b2Body* body_list = world->GetBodyList();
    while (body_list != nullptr) {
        if (body == body_list) return true;
        body_list = body_list->GetNext();
    }
    return false;
}

void PhysicsWorld::step() {
    float timeStep = 1.0f / 60;
    int velocityIterations = 8;
    int positionIterations = 2;
    world->Step(timeStep, velocityIterations, positionIterations);
}

PhysicsWorld::~PhysicsWorld() {
    b2Body* body = world->GetBodyList();
    while (body != nullptr) {
        b2Body* act = body;
        body = body->GetNext();
        world->DestroyBody(act);
    }
    delete floor;
    delete world;
}
