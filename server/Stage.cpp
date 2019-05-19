//
// Created by cecix on 12/05/19.
//

# define DEGTORAD 0.0174532925199432957f

#include "Stage.h"
#include "BrickBlock.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"
#include "EnergyBar.h"
#include "Button.h"
#include "Acid.h"
#include "EnergyBall.h"

Stage::Stage(size_t width, size_t height):
        width(width), height(height) {
    b2Vec2 gravity(0.0f, -1.0f);
    this->world = new b2World(gravity);

    // Setting initial configuration
    b2BodyDef body;
    body.type = b2_staticBody;
    b2PolygonShape shape;

    // Setting floor
    body.position.Set(width/2, -2); //avoid creating objets in the origin
    shape.SetAsBox(width/2, 2);
    this->world->CreateBody(&body)->CreateFixture(&shape, 0.0f);

    // Setting ceiling
    body.position.Set(width/2, height + 2);
    shape.SetAsBox(width/2, 2);
    this->world->CreateBody(&body)->CreateFixture(&shape, 0.0f);

    // Setting left wall
    body.position.Set(-2, height/2);
    shape.SetAsBox(2, height/2);
    this->world->CreateBody(&body)->CreateFixture(&shape, 0.0f);

    // Setting right wall
    body.position.Set(width + 2, height/2);
    shape.SetAsBox(2, height/2);
    this->world->CreateBody(&body)->CreateFixture(&shape, 0.0f);
}

b2Body* Stage::addStaticRectangle(size_t v_side, size_t h_side,
                                  float x_pos, float y_pos) {
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

b2Body* Stage::addDynamicRectangle(size_t v_side, size_t h_side,
                                   float x_pos, float y_pos) {
    b2BodyDef body;
    body.type = b2_dynamicBody;
    body.position.Set(x_pos, y_pos);

    b2Body* rectangle_body = this->world->CreateBody(&body);

    b2PolygonShape shape;
    shape.SetAsBox(h_side/2, v_side/2);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1;
    fixture.friction = 0.6;
    rectangle_body->CreateFixture(&fixture);

    return rectangle_body;
}

void Stage::addBrickBlock(size_t side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* block_body = addStaticRectangle(side, side, x_pos, y_pos);

    BrickBlock* block = new BrickBlock(block_body);
    brick_blocks.insert({coordinates, block});
}

void Stage::addMetalBlock(size_t side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* block_body = addStaticRectangle(side, side, x_pos, y_pos);

    MetalBlock* block = new MetalBlock(block_body);
    metal_blocks.insert({coordinates, block});
}

void Stage::addDiagonalMetalBlock(size_t side, float x_pos,
                                  float y_pos, float angle) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2BodyDef body;
    body.type = b2_staticBody;
    body.position.Set(x_pos, y_pos);

    b2Body* block_body = this->world->CreateBody(&body);

    b2Vec2 vertices[3]; // TODO: other variants as well
    vertices[0].Set(x_pos,  y_pos);
    vertices[1].Set(x_pos, y_pos + side);
    vertices[2].Set(x_pos + side, y_pos);

    b2PolygonShape shape;
    shape.Set(vertices, 3);

    b2FixtureDef fixture;

    fixture.shape = &shape;
    block_body->CreateFixture(&fixture);

    //block_body->SetTransform(block_body->GetPosition(), angle * DEGTORAD);

    DiagonalMetalBlock* block = new DiagonalMetalBlock(block_body);

    diagonal_metal_blocks.insert(std::make_pair(coordinates, block));
}

void Stage::addEnergyTransmitter(size_t side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* transmitter_body = addStaticRectangle(side, side, x_pos, y_pos);

    EnergyTransmitter* energy = new EnergyTransmitter(transmitter_body);
    energy_transmitters.insert({coordinates, energy});
}

void Stage::addRock(size_t side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* rock_body = addDynamicRectangle(side, side, x_pos, y_pos);

    Rock* rock = new Rock(rock_body);
    rocks.insert({coordinates, rock});
}

void Stage::addEnergyBar(size_t v_side, size_t h_side,
                         float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* energy_bar_body = addStaticRectangle(v_side, h_side, x_pos, y_pos);

    EnergyBar* energy_bar = new EnergyBar(energy_bar_body);
    energy_bars.insert({coordinates, energy_bar});
}

void Stage::addButton(size_t v_side, size_t h_side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* button_body = addStaticRectangle(v_side, h_side, x_pos, y_pos);

    Button* button = new Button(button_body);
    buttons.insert({coordinates, button});
}

void Stage::addAcid(size_t v_side, size_t h_side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* acid_body = addStaticRectangle(v_side, h_side, x_pos, y_pos);

    Acid* button = new Acid(acid_body);
    acids.insert({coordinates, button});
}

void Stage::addChell(size_t v_side, size_t h_side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* chell_body = addDynamicRectangle(v_side, h_side, x_pos, y_pos);

    Chell* chell = new Chell(chell_body);
    chells.insert({coordinates, chell});
}

void Stage::addEnergyBall(size_t side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* energy_ball_body = addDynamicRectangle(side, side, x_pos, y_pos);

    EnergyBall* energy_ball = new EnergyBall(energy_ball_body);
    energy_balls.insert({coordinates, energy_ball});
}

void Stage::step() {
    for (auto i = chells.begin(); i != chells.end(); i++) {
        i->second->update();
    }
    float timeStep = 1.0f / 60.0f;
    int velocityIterations = 8;
    int positionIterations = 2;
    world->Step(timeStep, velocityIterations, positionIterations);
}


BrickBlock* Stage::getBrickBlock(Coordinate* coordinate) {
    for (auto i = brick_blocks.begin() ; i != brick_blocks.end() ; i++) {
        if (*i->first == *coordinate) return i->second;
    }
    return nullptr;
}

MetalBlock* Stage::getMetalBlock(Coordinate* coordinate) {
    for (auto i = metal_blocks.begin() ; i != metal_blocks.end() ; i++) {
        if (*i->first == *coordinate) return i->second;
    }
    return nullptr;
}

DiagonalMetalBlock* Stage::getDiagonalMetalBlock(Coordinate* coordinate) {
    for (auto i = diagonal_metal_blocks.begin() ;
         i != diagonal_metal_blocks.end() ; i++) {
        if (*i->first == *coordinate) return i->second;
    }
    return nullptr;
}

EnergyTransmitter* Stage::getEnergyTransmitter(Coordinate *coordinate) {
    for (auto i = energy_transmitters.begin() ;
         i != energy_transmitters.end() ; i++) {
        if (*i->first == *coordinate) return i->second;
    }
    return nullptr;
}

Rock* Stage::getRock(Coordinate *coordinate) {
    for (auto item = rocks.begin() ; item != rocks.end() ; item++) {
        if (*item->first == *coordinate) return item->second;
    }
    return nullptr;
}

EnergyBar* Stage::getEnergyBar(Coordinate *coordinate) {
    for (auto item = energy_bars.begin() ; item != energy_bars.end() ; item++) {
        if (*item->first == *coordinate) return item->second;
    }
    return nullptr;
}

Button* Stage::getButton(Coordinate *coordinate) {
    for (auto item = buttons.begin() ; item != buttons.end() ; item++) {
        if (*item->first == *coordinate) return item->second;
    }
    return nullptr;
}

Acid* Stage::getAcid(Coordinate *coordinate) {
    for (auto item = acids.begin() ; item != acids.end() ; item++) {
        if (*item->first == *coordinate) return item->second;
    }
    return nullptr;
}

Chell* Stage::getChell(Coordinate* coordinate) {
    for (auto item = chells.begin() ; item != chells.end() ; item++) {
        if (*item->first == *coordinate) return item->second;
    }
    return nullptr;
}

EnergyBall* Stage::getEnergyBall(Coordinate* coordinate) {
    for (auto i = energy_balls.begin(); i != energy_balls.end(); i++) {
        if (*i->first == *coordinate) return i->second;
    }
    return nullptr;
}

Stage::~Stage() {
    b2Body* body = world->GetBodyList();
    while (body != nullptr) {
        b2Body* act = body;
        body = body->GetNext();
        world->DestroyBody(act);
    }

    for (auto i = brick_blocks.begin() ; i != brick_blocks.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    for (auto i = metal_blocks.begin() ; i != metal_blocks.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    for (auto i = diagonal_metal_blocks.begin() ;
         i != diagonal_metal_blocks.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    for (auto i = energy_transmitters.begin() ;
         i != energy_transmitters.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    for (auto i = rocks.begin() ; i != rocks.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    for (auto i = energy_bars.begin() ; i != energy_bars.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    for (auto i = buttons.begin() ; i != buttons.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    for (auto i = acids.begin() ; i != acids.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    for (auto i = chells.begin() ; i != chells.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    //just in case an energy balls isn't deleted before the end of the game
    for (auto i = energy_balls.begin() ; i != energy_balls.end() ; i++) {
        delete i->first;
        delete i->second;
    }

    delete world;
}
