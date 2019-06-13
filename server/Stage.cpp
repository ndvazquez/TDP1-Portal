//
// Created by cecix on 12/05/19.
//

#include <string>
#include <iostream>
#include "Stage.h"
#include "BrickBlock.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"
#include "EnergyBar.h"
#include "Button.h"
#include "Acid.h"
#include "EnergyBall.h"
#include "EnergyTransmitterRight.h"
#include "EnergyTransmitterLeft.h"
#include "EnergyTransmitterUp.h"
#include "EnergyTransmitterDown.h"

Stage::Stage(size_t width, size_t height):
    width(width), height(height) {
    float module_gravity = gameConfiguration.gravity;
    b2Vec2 gravity(0.0f, module_gravity);
    this->world = new b2World(gravity);

    // Setting initial configuration
    b2BodyDef body;
    body.type = b2_staticBody;
    b2PolygonShape shape;

    // Setting floor
    b2Body* body_floor = addStaticRectangle(4, width, width/2, -2);
    Floor* floor = new Floor(body_floor);
    this->floor = floor;

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

    this->cake = nullptr;
}

b2Body* Stage::addStaticRectangle(float v_side, float h_side,
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

b2Body* Stage::addDynamicRectangle(float v_side, float h_side,
                                   float x_pos, float y_pos) {
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

void Stage::addCake(float side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* cake_body = addStaticRectangle(side, side, x_pos, y_pos);

    this->cake = new Cake(cake_body);
}

void Stage::addBrickBlock(float side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* block_body = addStaticRectangle(side, side, x_pos, y_pos);

    BrickBlock* block = new BrickBlock(block_body);
    brick_blocks.insert({coordinates, block});
}

void Stage::addMetalBlock(float side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* block_body = addStaticRectangle(side, side, x_pos, y_pos);

    MetalBlock* block = new MetalBlock(block_body);
    metal_blocks.insert({coordinates, block});
}

void Stage::addDiagonalMetalBlock(float side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    b2Body* block_body = addStaticRectangle(side, side, x_pos, y_pos);

    DiagonalMetalBlock* block = new DiagonalMetalBlock(block_body);

    diagonal_metal_blocks.insert(std::make_pair(coordinates, block));
}

void Stage::addGate(std::string id, float v_side, float h_side, float x_pos,
        float y_pos, std::unordered_map<std::string, Button*> buttons,
                    std::string logic) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* gate_body = addStaticRectangle(v_side, h_side, x_pos, y_pos);

    Gate* gate = new Gate(gate_body, logic, buttons);
    gates.insert({id, gate});
}

void Stage::addEnergyBar(std::string id, float v_side, float h_side,
                         float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* energy_bar_body = addStaticRectangle(v_side, h_side, x_pos, y_pos);

    EnergyBar* energy_bar = new EnergyBar(energy_bar_body);
    energy_bars.insert({id, energy_bar});
}

void Stage::addButton(std::string id, float v_side, float h_side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* button_body = addStaticRectangle(v_side, h_side, x_pos, y_pos);

    Button* button = new Button(button_body);
    buttons.insert({id, button});
}

void Stage::addAcid(std::string id, float v_side, float h_side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* acid_body = addStaticRectangle(v_side, h_side, x_pos, y_pos);

    Acid* acid = new Acid(acid_body);
    acids.insert({id, acid});
}

void Stage::addChell(std::string id, float v_side, float h_side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* chell_body = addDynamicRectangle(v_side, h_side, x_pos, y_pos);

    Chell* chell = new Chell(chell_body);
    chells.insert({id, chell});
}

void Stage::addEnergyBallHorizontal(std::string id, float side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* energy_ball_body = addDynamicRectangle(side, side, x_pos, y_pos);

    EnergyBall* energy_ball = new EnergyBall(energy_ball_body, false);
    energy_balls.insert({id, energy_ball});
}

void Stage::addEnergyBallVertical(std::string id, float side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* energy_ball_body = addDynamicRectangle(side, side, x_pos, y_pos);

    EnergyBall* energy_ball = new EnergyBall(energy_ball_body, true);
    energy_balls.insert({id, energy_ball});
}

void Stage::addEnergyTransmitterRight(std::string id, float side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* body = addStaticRectangle(side, side, x_pos, y_pos);

    EnergyTransmitterRight* energy = new EnergyTransmitterRight(body);
    energy_transmitters_horizontals.insert({id, energy});
}

void Stage::addEnergyTransmitterLeft(std::string id, float side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* body = addStaticRectangle(side, side, x_pos, y_pos);

    EnergyTransmitterLeft* energy = new EnergyTransmitterLeft(body);
    energy_transmitters_horizontals.insert({id, energy});
}

void Stage::addEnergyTransmitterUp(std::string id, float side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* transmitter_body = addStaticRectangle(side, side, x_pos, y_pos);

    EnergyTransmitterUp* energy = new EnergyTransmitterUp(transmitter_body);
    energy_transmitters_verticals.insert({id, energy});
}

void Stage::addEnergyTransmitterDown(std::string id, float side,
        float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* transmitter_body = addStaticRectangle(side, side, x_pos, y_pos);

    EnergyTransmitterDown* energy = new EnergyTransmitterDown(transmitter_body);
    energy_transmitters_verticals.insert({id, energy});
}

void Stage::addRock(std::string id, float side, float x_pos, float y_pos) {
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* rock_body = addDynamicRectangle(side, side, x_pos, y_pos);
    b2Fixture* fixture = rock_body->GetFixtureList();
    fixture->SetFriction(gameConfiguration.rockFriction);

    Rock* rock = new Rock(rock_body);
    rocks.insert({id, rock});
}

void Stage::addBlueShot(std::string id, float v_side, float h_side,
        Chell* chell, Coordinate* target) {
    float x_target = target->getX();
    float x_origin_right = chell->getHorizontalPosition() + 2 + h_side/2;
    float x_origin_left = chell->getHorizontalPosition() - 2 - h_side/2;

    float x_pos;
    float y_pos = chell->getVerticalPosition();

    if (x_target >= x_origin_right) x_pos = x_origin_right;
    if (x_target <= x_origin_left) x_pos = x_origin_left;

    y_pos += 1;

    b2Body* blue_shot_body = addDynamicRectangle(v_side, h_side, x_pos, y_pos);
    BlueShot* blueShot = new BlueShot(blue_shot_body, chell, target);
    blue_shots.insert({id, blueShot});
}

void Stage::addOrangeShot(std::string id, float v_side, float h_side,
        Chell* chell, Coordinate* target) {
    float x_target = target->getX();
    float x_origin_right = chell->getHorizontalPosition() + 2 + h_side/2;
    float x_origin_left = chell->getHorizontalPosition() - 2 - h_side/2;

    float x = chell->getHorizontalPosition();
    float x_pos;
    float y_pos = chell->getVerticalPosition();

    if (x_target >= x) {
        x_pos = x_origin_right;
    } else {
        x_pos = x_origin_left;
    }

    y_pos += 1;

    b2Body* orange_body = addDynamicRectangle(v_side, h_side, x_pos, y_pos);
    OrangeShot* orangeShot = new OrangeShot(orange_body, chell, target);
    orange_shots.insert({id, orangeShot});
}

void Stage::addPortal(std::string id, float v_side, float h_side,
        Coordinate* origin, Coordinate* target,
        PortalOrientation orientation) {
    float x_pos = origin->getX();
    float y_pos = origin->getY();
    if (x_pos < 0 || x_pos > width || y_pos < 0 || y_pos > height) {
        throw StageOutOfRangeException();
    }

    b2Body* portal_body = addStaticRectangle(v_side, h_side, x_pos, y_pos);

    Portal* portal = new Portal(portal_body, target, orientation);
    portals.insert({id, portal});
}

void Stage::managePortals(Chell* chell, std::string id) {
    BluePortal *blue_portal = chell->getBluePortal();
    OrangePortal *orange_portal = chell->getOrangePortal();
    if (blue_portal == nullptr && orange_portal == nullptr) return;
    std::string id_orange = id;
    id_orange.replace(0, id.length(), "OrangePortal");
    std::string id_blue = id;
    id_blue.replace(0, id.length(), "BluePortal");

    std::unordered_map<std::string, Portal *>::iterator it;
    it = portals.find(id_orange);
    if (it != portals.end()) {
        Portal* portal = it->second;
        float x_portal = portal->getHorizontalPosition();
        float y_portal = portal->getVerticalPosition();
        Coordinate coord_portal(x_portal, y_portal);
        if (orange_portal != nullptr) {
            if (*orange_portal->getPortal() != coord_portal) {
                world->DestroyBody(it->second->getBody());
                portals.erase(it->first);
            }
        }
        if (blue_portal != nullptr) {
            float x_blue = blue_portal->getPortal()->getX();
            float y_blue = orange_portal->getPortal()->getY();
            portal->addTarget(new Coordinate(x_blue, y_blue));
        }
    }
    else if (orange_portal != nullptr) {
        Coordinate* blue_portal_coord = chell->getBluePortalToTeleport();
        if (orange_portal->isVertical()) {
            addPortal(id_orange, PORTAL_HEIGHT, PORTAL_WIDTH, orange_portal->getPortal(),
                    blue_portal_coord, VERTICAL);
        } else {
            addPortal(id_orange, PORTAL_WIDTH, PORTAL_HEIGHT, orange_portal->getPortal(),
                    blue_portal_coord, HORIZONTAL);
        }
    }

    it = portals.find(id_blue);
    if (it != portals.end()) {
        std::string portal_id = it->first;
        Portal *portal = it->second;
        float x_portal = portal->getHorizontalPosition();
        float y_portal = portal->getVerticalPosition();
        Coordinate coord_portal(x_portal, y_portal);
        if (blue_portal != nullptr) {
            if (*blue_portal->getPortal() != coord_portal) {
                world->DestroyBody(portal->getBody());
                {
                    portals.erase(portal_id);
                }
            }
        }
        if (orange_portal != nullptr) {
            float x_orange = orange_portal->getPortal()->getX();
            float y_orange = orange_portal->getPortal()->getY();
            portal->addTarget(new Coordinate(x_orange, y_orange));
        }
    }
    else if (blue_portal != nullptr) {
        Coordinate* orange_portal_coord = chell->getOrangePortalToTeleport();
        if (blue_portal->isVertical()) {
            addPortal(id_blue, PORTAL_HEIGHT, PORTAL_WIDTH, blue_portal->getPortal(),
                    orange_portal_coord, VERTICAL);
        } else {
            addPortal(id_blue, PORTAL_WIDTH, PORTAL_HEIGHT, blue_portal->getPortal(),
                    orange_portal_coord, HORIZONTAL);
        }
    }
}

void Stage::step() {
    for (auto i = chells.begin(); i != chells.end(); i++) {
        managePortals(i->second, i->first);

        if (i->second->isDead()) {
            world->DestroyBody(i->second->getBody());
            {
                chells.erase(i->first);
                break;
            }
        }
        if (i->second->hasWon()) {
        //TODO: Tell client to end game
        }
        i->second->update();
    }

    for (auto i = blue_shots.begin(); i != blue_shots.end(); i++) {
        if (i->second->isDead()) {
            world->DestroyBody(i->second->getBody());
            {
                blue_shots.erase(i->first);
                break;
            }
        }
        i->second->shoot();
    }

    for (auto i = orange_shots.begin(); i != orange_shots.end(); i++) {
        if (i->second->isDead()) {
            world->DestroyBody(i->second->getBody());
            {
                orange_shots.erase(i->first);
                break;
            }
        }
        i->second->shoot();
    }

    for (auto i = energy_transmitters_horizontals.begin();
    i != energy_transmitters_horizontals.end(); i++) {
        Coordinate* energyBallCoordinates = i->second->throwEnergyBall();
            if (energyBallCoordinates != nullptr) {
                float x_pos = energyBallCoordinates->getX();
                float y_pos = energyBallCoordinates->getY();
                std::string id = i->first;
                std::string to_replace = "EnergyBall";
                std::string replaced = "EnergyTransmitter";
                id.replace(0, replaced.length(), to_replace);
                addEnergyBallHorizontal(id, 1, x_pos, y_pos);
                delete energyBallCoordinates;
            }
    }

    for (auto i = energy_transmitters_verticals.begin();
    i != energy_transmitters_verticals.end(); i++) {
        Coordinate* energyBallCoordinates = i->second->throwEnergyBall();
        if (energyBallCoordinates != nullptr) {
            float x_pos = energyBallCoordinates->getX();
            float y_pos = energyBallCoordinates->getY();
            std::string id = i->first;
            std::string to_replace = "EnergyBall";
            std::string replaced = "EnergyTransmitter";
            id.replace(0, replaced.length(), to_replace);
            addEnergyBallVertical(id, 1, x_pos, y_pos);
            delete energyBallCoordinates;
        }
    }

    for (auto i = energy_balls.begin(); i != energy_balls.end(); i++) {
        if (i->second->isDead()) {
            world->DestroyBody(i->second->getBody());
            {
                energy_balls.erase(i->first);
                break;
            }
        }
        i->second->fly();
    }

    for (auto i = gates.begin(); i != gates.end(); i++) {
        i->second->update();
    }

    for (auto i = rocks.begin(); i != rocks.end(); i++) {
        if (i->second->isDead()) {
            world->DestroyBody(i->second->getBody());
            {
                rocks.erase(i->first);
                break;
            }
        }
        i->second->update();
    }

    for (auto i = energy_bars.begin(); i != energy_bars.end(); i++) {
        i->second->activateBody();
    }

    for (auto i = buttons.begin(); i != buttons.end(); i++) {
        i->second->update();
    }

    float timeStep = 1.0f / 60;
    int velocityIterations = 8;
    int positionIterations = 2;
    world->Step(timeStep, velocityIterations, positionIterations);
}

Cake* Stage::getCake() {
    return cake;
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

EnergyBar* Stage::getEnergyBar(std::string id) {
    for (auto item = energy_bars.begin() ; item != energy_bars.end() ; item++) {
        if (item->first == id) return item->second;
    }
    return nullptr;
}

Button* Stage::getButton(std::string id) {
    for (auto item = buttons.begin() ; item != buttons.end() ; item++) {
        if (item->first == id) return item->second;
    }
    return nullptr;
}

Acid* Stage::getAcid(std::string id) {
    for (auto item = acids.begin() ; item != acids.end() ; item++) {
        if (item->first == id) return item->second;
    }
    return nullptr;
}

Chell* Stage::getChell(std::string id) {
    for (auto item = chells.begin() ; item != chells.end() ; item++) {
        if (item->first == id) return item->second;
    }
    return nullptr;
}

EnergyBall* Stage::getEnergyBall(std::string id) {
    for (auto i = energy_balls.begin(); i != energy_balls.end(); i++) {
        if (i->first == id) return i->second;
    }
    return nullptr;
}

BlueShot* Stage::getBlueShot(std::string id) {
    for (auto i = blue_shots.begin() ; i != blue_shots.end() ; i++) {
        if (i->first == id) return i->second;
    }
    return nullptr;
}

OrangeShot* Stage::getOrangeShot(std::string id) {
    for (auto i = orange_shots.begin() ; i != orange_shots.end() ; i++) {
        if (i->first == id) return i->second;
    }
    return nullptr;
}

EnergyTransmitter* Stage::getEnergyTransmitter(std::string id) {
    for (auto i = energy_transmitters_horizontals.begin() ;
         i != energy_transmitters_horizontals.end() ; i++) {
        if (i->first == id) return i->second;
    }
    for (auto i = energy_transmitters_verticals.begin() ;
         i != energy_transmitters_verticals.end() ; i++) {
        if (i->first == id) return i->second;
    }
    return nullptr;
}

Rock* Stage::getRock(std::string id) {
    for (auto item = rocks.begin() ; item != rocks.end() ; item++) {
        if (item->first == id) return item->second;
    }
    return nullptr;
}

Rock* Stage::getClosestRock(float x_pos, float y_pos) {
    b2Vec2 origin(x_pos, y_pos);
    Rock *result_rock = nullptr;
    float distance = -1;
    for (auto i = rocks.begin(); i != rocks.end(); i++) {
        Rock *rock = i->second;
        float x_rock = i->second->getHorizontalPosition();
        float y_rock = i->second->getVerticalPosition();
        b2Vec2 target(x_rock, y_rock);
        float new_distance = (target - origin).Length();
        if (distance < 0 || new_distance < distance) {
            distance = new_distance;
            result_rock = rock;
        }
    }
    return result_rock;
}

Gate* Stage::getGate(std::string id) {
    for (auto item = gates.begin() ; item != gates.end() ; item++) {
        if (item->first == id) return item->second;
    }
    return nullptr;
}

nlohmann::json Stage::getCurrentState() {
    nlohmann::json request;
    for (auto i = chells.begin(); i != chells.end(); i++)  {
        std::string id_chell = i->first;
        ChellState state_chell = i->second->getState();
        float x_pos_chell = i->second->getHorizontalPosition();
        float y_pos_chell = i->second->getVerticalPosition();
        request[id_chell] = {
                {"state", state_chell}, {"x", x_pos_chell}, {"y", y_pos_chell}
        };
    }
    for (auto i = rocks.begin(); i != rocks.end(); i++)  {
        std::string id_rock = i->first;
        float x_pos_rock = i->second->getHorizontalPosition();
        float y_pos_rock = i->second->getVerticalPosition();
        request[id_rock] = {
                {"state", 0}, {"x", x_pos_rock}, {"y", y_pos_rock}
        };
    }
    for (auto i = blue_shots.begin(); i != blue_shots.end(); i++)  {
        std::string id_blue_shot = i->first;
        float x_pos_blue_shot = i->second->getHorizontalPosition();
        float y_pos_blue_shot = i->second->getVerticalPosition();
        request[id_blue_shot] = {
                {"state", 0}, {"x", x_pos_blue_shot}, {"y", y_pos_blue_shot}
        };
    }
    for (auto i = orange_shots.begin(); i != orange_shots.end(); i++)  {
        std::string id_orange_shot = i->first;
        float x_pos_orange_shot = i->second->getHorizontalPosition();
        float y_pos_orange_shot = i->second->getVerticalPosition();
        request[id_orange_shot] = {
                {"state", 0}, {"x", x_pos_orange_shot}, {"y", y_pos_orange_shot}
        };
    }
    for (auto i = energy_balls.begin(); i != energy_balls.end(); i++)  {
        std::string id_eb = i->first;
        float x_pos_eb = i->second->getHorizontalPosition();
        float y_pos_eb = i->second->getVerticalPosition();
        request[id_eb] = {
                {"state", 0}, {"x", x_pos_eb}, {"y", y_pos_eb}
        };
    }
    for (auto i = acids.begin(); i != acids.end(); i++) {
        std::string id_acid = i->first;
        float x_pos_acid = i->second->getHorizontalPosition();
        float y_pos_acid = i->second->getVerticalPosition();
        request[id_acid] = {
                {"state", 0}, {"x", x_pos_acid}, {"y", y_pos_acid}
        };
    }
    for (auto i = energy_transmitters_horizontals.begin();
    i != energy_transmitters_horizontals.end(); i++) {
        std::string id_et = i->first;
        float x_pos_et = i->second->getHorizontalPosition();
        float y_pos_et = i->second->getVerticalPosition();
        request[id_et] = {
                {"state", 0}, {"x", x_pos_et}, {"y", y_pos_et}
        };
    }
    for (auto i = energy_transmitters_verticals.begin();
         i != energy_transmitters_verticals.end(); i++) {
        std::string id_et = i->first;
        float x_pos_et = i->second->getHorizontalPosition();
        float y_pos_et = i->second->getVerticalPosition();
        request[id_et] = {
                {"state", 0}, {"x", x_pos_et}, {"y", y_pos_et}
        };
    }
    for (auto i = energy_bars.begin(); i != energy_bars.end(); i++) {
        std::string id_eb = i->first;
        float x_pos_eb = i->second->getHorizontalPosition();
        float y_pos_eb = i->second->getHorizontalPosition();
        request[id_eb] = {
                {"state", 0}, {"x", x_pos_eb}, {"y", y_pos_eb}
        };
    }
    for (auto i = buttons.begin(); i != buttons.end(); i++) {
        std::string id_button = i->first;
        ButtonState state = i->second->getState();
        float x_pos_button = i->second->getHorizontalPosition();
        float y_pos_button = i->second->getVerticalPosition();
        request[id_button] = {
                {"state", state}, {"x", x_pos_button}, {"y", y_pos_button}
        };
    }
    for (auto i = gates.begin(); i != gates.end(); i++) {
        std::string id_gate = i->first;
        GateState state = i->second->getState();
        float x_pos_gate = i->second->getHorizontalPosition();
        float y_pos_gate = i->second->getVerticalPosition();
        request[id_gate] = {
                {"state", state}, {"x", x_pos_gate}, {"y", y_pos_gate}
        };
    }
    for (auto i = portals.begin(); i != portals.end(); i++) {
        std::string id_portal = i->first;
        PortalOrientation orientation = i->second->getOrientation();
        float x_pos_portal = i->second->getHorizontalPosition();
        float y_pos_portal = i->second->getVerticalPosition();
        request[id_portal] = {
                {"state", orientation}, {"x", x_pos_portal}, {"y", y_pos_portal}
        };
    }
    float x_pos_cake = cake->getHorizontalPosition();
    float y_pos_cake = cake->getVerticalPosition();
    request["Cake"] = {
            {"state", 0}, {"x", x_pos_cake}, {"y", y_pos_cake}
    };
    return request;
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

    for (auto i = energy_transmitters_horizontals.begin() ;
         i != energy_transmitters_horizontals.end() ; i++) {
        delete i->second;
    }

    for (auto i = energy_transmitters_verticals.begin() ;
         i != energy_transmitters_verticals.end() ; i++) {
        delete i->second;
    }

    for (auto i = rocks.begin() ; i != rocks.end() ; i++) {
        delete i->second;
    }

    for (auto i = energy_bars.begin() ; i != energy_bars.end() ; i++) {
        delete i->second;
    }

    for (auto i = buttons.begin() ; i != buttons.end() ; i++) {
        delete i->second;
    }

    for (auto i = acids.begin() ; i != acids.end() ; i++) {
        delete i->second;
    }

    for (auto i = chells.begin() ; i != chells.end() ; i++) {
        delete i->second;
    }

    //just in case an energy balls isn't deleted before the end of the game
    for (auto i = energy_balls.begin() ; i != energy_balls.end() ; i++) {
        delete i->second;
    }

    for (auto i = gates.begin(); i != gates.end(); i++) {
        delete i->second;
    }

    delete floor;
    delete world;
    delete cake;
}
