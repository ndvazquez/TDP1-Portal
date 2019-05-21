//
// Created by cecix on 12/05/19.
//

//Preguntar hasta que punto las cosas son representables en BOX2D

# define DEGTORAD 0.0174532925199432957f

#include "Stage.h"
#include "BrickBlock.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"


Stage::Stage(size_t width, size_t height):
    width(width), height(height) {

    b2Vec2 gravity(0.0f, -10.0f);
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

bool Stage::addBrickBlock(size_t side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        return false;
    } //excepciones o booleano?

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2BodyDef body;
    body.type = b2_staticBody;
    body.position.Set(x_pos, y_pos);

    b2Body* block_body = this->world->CreateBody(&body);

    b2PolygonShape shape;
    shape.SetAsBox(side/2, side/2);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    block_body->CreateFixture(&fixture);

    BrickBlock* block = new BrickBlock(side, block_body);
    brick_blocks.insert({coordinates, block});

    return true; // despues si no entra devolver false. Como hago para saber si hay otro objeto ahi?
}

bool Stage::addMetalBlock(size_t side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        return false;
    } //excepciones o booleano?

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2BodyDef body;
    body.type = b2_staticBody;
    body.position.Set(x_pos, y_pos);

    b2Body* block_body = this->world->CreateBody(&body);

    b2PolygonShape shape;
    shape.SetAsBox(side/2, side/2);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    block_body->CreateFixture(&fixture);

    MetalBlock* block = new MetalBlock(side, block_body);
    metal_blocks.insert({coordinates, block});

    return true; // despues si no entra devolver false. Como hago para saber si hay otro objeto ahi?
}

bool Stage::addDiagonalMetalBlock(size_t side, float x_pos, float y_pos, float angle) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        return false;
    } //excepciones o booleano?

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2BodyDef body;
    body.type = b2_staticBody;
    body.position.Set(x_pos, y_pos);

    b2Body* block_body = this->world->CreateBody(&body);

    b2Vec2 vertices[3]; // setting vertices of the  triangule. TODO: other variants as well
    vertices[0].Set(x_pos,  y_pos);
    vertices[1].Set(x_pos, y_pos + side);
    vertices[2].Set(x_pos + side, y_pos);

    b2PolygonShape shape;
    shape.Set(vertices, 3);

    b2FixtureDef fixture;

    fixture.shape = &shape;
    block_body->CreateFixture(&fixture);

    //block_body->SetTransform(block_body->GetPosition(), angle * DEGTORAD);

    DiagonalMetalBlock* block = new DiagonalMetalBlock(side, block_body);

    diagonal_metal_blocks.insert(std::make_pair(coordinates, block));

    return true; // despues si no entra devolver false. Como hago para saber si hay otro objeto ahi?
}

bool Stage::addButton(float x_position, float y_position) {
    return true;
}

bool Stage::addRock(float x_position, float y_position) {
    return true;
}

bool Stage::addEnergyTransmitter(float x_position, float y_position) {
    return true;
}

bool Stage::addEnergyBar(float x_position, float y_position) {
    return true;
}

BrickBlock* Stage::getBrickBlock(Coordinate* coordinate) {
    for (auto item = brick_blocks.begin() ; item != brick_blocks.end() ; item++) {
        if (*item->first == *coordinate) return item->second;
    }
    return nullptr;
}

MetalBlock* Stage::getMetalBlock(Coordinate* coordinate) {
    for (auto item = metal_blocks.begin() ; item != metal_blocks.end() ; item++) {
        if (*item->first == *coordinate) return item->second;
    }
    return nullptr;
}

DiagonalMetalBlock* Stage::getDiagonalMetalBlock(Coordinate* coordinate) {
    for (auto item = diagonal_metal_blocks.begin() ; item != diagonal_metal_blocks.end() ; item++) {
        if (*item->first == *coordinate) return item->second;
    }
    return nullptr;
}


Stage::~Stage() {
    delete world;

    for (auto item = brick_blocks.begin() ; item != brick_blocks.end() ; item++) {
        delete item->first;
        delete item->second;
    }

    for (auto item = metal_blocks.begin() ; item != metal_blocks.end() ; item++) {
        delete item->first;
        delete item->second;
    }

    for (auto item = diagonal_metal_blocks.begin() ; item != diagonal_metal_blocks.end() ; item++) {
        delete item->first;
        delete item->second;
    }
}
