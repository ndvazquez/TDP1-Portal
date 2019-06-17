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
#include "EnergyReceptorRight.h"
#include "EnergyReceptorLeft.h"
#include "EnergyReceptorDown.h"
#include "EnergyReceptorUp.h"
#include "PortalManager.h"

Stage::Stage(size_t width, size_t height) {
    this->end_of_game = false;
    float module_gravity = gameConfiguration.gravity;
    b2Vec2 gravity(0.0f, module_gravity);
    b2World* world = new b2World(gravity);
    this->world = new PhysicsWorld(world, width, height);
    this->cake = nullptr;
}

void Stage::addBlock(std::string identifier, float side, float x_pos, float y_pos) {
    b2Body* block_body = world->addStaticRectangle(side, side, x_pos, y_pos);

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    if (identifier == BRICK_BLOCK_NAME) {
        BrickBlock* block = new BrickBlock(block_body);
        brick_blocks.insert({coordinates, block});
    } else if (identifier == METAL_BLOCK_NAME) {
        MetalBlock* block = new MetalBlock(block_body);
        metal_blocks.insert({coordinates, block});
    } else if (identifier == CAKE_NAME) {
      this->cake = new Cake(block_body);
    } else {
        world->destroyBody(block_body);
        throw StageBadIdentifierException();
    }
}

void Stage::addDiagonalBlock(float side, float x_pos, float y_pos, float angle) {
    b2Body *block_body = world->addTriangle(side, x_pos, y_pos, angle);

    Coordinate* coordinates = new Coordinate(x_pos, y_pos);

    DiagonalMetalBlock *block = new DiagonalMetalBlock(block_body, angle);
    diagonal_metal_blocks.insert({coordinates, block});
}

void Stage::addGate(std::string id, float v_side, float h_side, float x_pos,
        float y_pos, std::unordered_map<std::string, ItemActivable*> items,
                    std::string logic) {
    b2Body* gate_body = world->addStaticRectangle(v_side, h_side, x_pos, y_pos);

    Gate* gate = new Gate(gate_body, logic, items);
    gates.insert({id, gate});
}

void Stage::addChell(std::string id, float v_side, float h_side,
        float x_pos, float y_pos) {
    b2Body* chell_body = world->addDynamicRectangleWithWheels(v_side, h_side, x_pos, y_pos);

    Chell* chell = new Chell(chell_body);
    chells.insert({id, chell});
}

void Stage::addEnergyBall(std::string identifier, std::string id, float side,
        float x_pos, float y_pos) {
    b2Body* energy_ball_body = world->addDynamicRectangle(side, side, x_pos, y_pos);

    if (identifier == EB_HORIZONTAL_NAME) {
        EnergyBall* energy_ball = new EnergyBall(energy_ball_body, false);
        energy_balls.insert({id, energy_ball});

    } else if (identifier == EB_VERTICAL_NAME) {
        EnergyBall* energy_ball = new EnergyBall(energy_ball_body, true);
        energy_balls.insert({id, energy_ball});
    } else {
        world->destroyBody(energy_ball_body);
        throw StageBadIdentifierException();
    }
}

void Stage::addEnergyItem(std::string identifier, std::string id, float side,
        float x_pos, float y_pos) {
    b2Body *body = world->addStaticRectangle(side, side, x_pos, y_pos);

    if (identifier == ET_RIGHT_NAME) {
        EnergyTransmitterRight* energy = new EnergyTransmitterRight(body);
        energy_transmitters_horizontals.insert({id, energy});
    } else if (identifier == ET_LEFT_NAME) {
        EnergyTransmitterLeft* energy = new EnergyTransmitterLeft(body);
        energy_transmitters_horizontals.insert({id, energy});
    } else if (identifier == ET_DOWN_NAME) {
        EnergyTransmitterDown* energy = new EnergyTransmitterDown(body);
        energy_transmitters_verticals.insert({id, energy});
    } else if (identifier == ET_UP_NAME) {
        EnergyTransmitterUp* energy = new EnergyTransmitterUp(body);
        energy_transmitters_verticals.insert({id, energy});
    } else if (identifier == ER_RIGHT_NAME) {
        EnergyReceptorRight* energy = new EnergyReceptorRight(body);
        energy_receptors.insert({id, energy});
    } else if (identifier == ER_LEFT_NAME) {
        EnergyReceptorLeft* energy = new EnergyReceptorLeft(body);
        energy_receptors.insert({id, energy});
    } else if (identifier == ER_DOWN_NAME) {
        EnergyReceptorDown* energy = new EnergyReceptorDown(body);
        energy_receptors.insert({id, energy});
    } else if (identifier == ER_UP_NAME) {
        EnergyReceptorUp* energy = new EnergyReceptorUp(body);
        energy_receptors.insert({id, energy});
    } else {
        world->destroyBody(body);
        throw StageBadIdentifierException();
    }
}

void Stage::addRock(std::string id, float side, float x_pos, float y_pos) {
    b2Body* rock_body = world->addDynamicRectangle(side, side, x_pos, y_pos);
    b2Fixture* fixture = rock_body->GetFixtureList();
    fixture->SetFriction(gameConfiguration.rockFriction);

    Rock* rock = new Rock(rock_body);
    rocks.insert({id, rock});
}

void Stage::addShot(std::string identifier, std::string id, float v_side, float h_side,
                    Chell* chell, Coordinate* target) {
    float x_target = target->getX();
    float x_origin_right = chell->getHorizontalPosition() + 1;
    float x_origin_left = chell->getHorizontalPosition() - 1;

    float x = chell->getHorizontalPosition();
    float x_pos;
    float y_pos = chell->getVerticalPosition();

    if (x_target >= x) {
        x_pos = x_origin_right;
    } else {
        x_pos = x_origin_left;
    }

    y_pos += 1;

    b2Body* body = world->addDynamicRectangle(v_side, h_side, x_pos, y_pos);
    if (identifier == BLUE_SHOT_NAME) {
        BlueShot* blueShot = new BlueShot(body, chell, target);
        blue_shots.insert({id, blueShot});
    } else if (identifier == ORANGE_SHOT_NAME) {
        OrangeShot* orangeShot = new OrangeShot(body, chell, target);
        orange_shots.insert({id, orangeShot});
    } else {
        world->destroyBody(body);
        throw StageBadIdentifierException();
    }
}

void Stage::addPinTool(std::string id, float v_side, float h_side,
        float x_pos, float y_pos, Chell* chell) {
    PinTool* pinTool = chell->getPinTool();
    if (pinTool != nullptr) {
        if (world->hasObject(pinTool->getBody())) {
            world->destroyBody(pinTool->getBody());
        }
    }
    b2Body* body = world->addStaticRectangle(v_side, h_side, x_pos, y_pos);
    pinTool = new PinTool(body);
    chell->addPinTool(pinTool);
    pintools.insert({id, pinTool});
}

void Stage::addElement(std::string identifier, std::string id, float v_side,
        float h_side, float x_pos, float y_pos) {
    b2Body* body = world->addStaticRectangle(v_side, h_side, x_pos, y_pos);

    if (identifier == ENERGY_BAR_NAME) {
        EnergyBar* energy_bar = new EnergyBar(body);
        energy_bars.insert({id, energy_bar});
    } else if (identifier == ACID_NAME) {
        Acid* acid = new Acid(body);
        acids.insert({id, acid});
    } else if (identifier == BUTTON_NAME) {
        Button* button = new Button(body);
        buttons.insert({id, button});
    } else {
        world->destroyBody(body);
        throw StageBadIdentifierException();
    }
}

void Stage::managePortals(Chell* chell, std::string id) {
    PortalManager manager(portals, world);
    manager.managePortals(chell, id);
}

void Stage::step() {
    std::cout << pintools.size() << std::endl;
    for (auto i = chells.begin(); i != chells.end(); i++) {
        if (i->second->isDead()) {
            if (world->hasObject(i->second->getBody())) {
                world->destroyBody(i->second->getBody());
            }
        } else if (end_of_game) {
            i->second->win();
        } else if (i->second->hasWon()) {
            if (world->hasObject(i->second->getBody())) {
                world->destroyBody(i->second->getBody());
            }
            end_of_game = true;
        } else {
            managePortals(i->second, i->first);
            i->second->update();
        }
    }

    for (auto i = blue_shots.begin(); i != blue_shots.end(); i++) {
        if (i->second->isDead()) {
            world->destroyBody(i->second->getBody());
            {
                blue_shots.erase(i->first);
                break;
            }
        }
        i->second->shoot();
    }

    for (auto i = orange_shots.begin(); i != orange_shots.end(); i++) {
        if (i->second->isDead()) {
            world->destroyBody(i->second->getBody());
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
                addEnergyBall(EB_HORIZONTAL_NAME, id, 1, x_pos, y_pos);
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
            addEnergyBall(EB_VERTICAL_NAME, id, 1, x_pos, y_pos);
            delete energyBallCoordinates;
        }
    }

    for (auto i = energy_balls.begin(); i != energy_balls.end(); i++) {
        if (i->second->isDead()) {
            world->destroyBody(i->second->getBody());
            {
                energy_balls.erase(i->first);
                break;
            }
        }
        i->second->fly();
        i->second->update();
    }

    std::cout << pintools.size() << std::endl;

    for (auto i = pintools.begin(); i != pintools.end(); i++) {
        if (i->second->isDead()) {
            world->destroyBody(i->second->getBody());
            {
                pintools.erase(i->first);
                break;
            }
        }
        i->second->update();
    }

    for (auto i = gates.begin(); i != gates.end(); i++) {
        i->second->update();
    }

    for (auto i = rocks.begin(); i != rocks.end(); i++) {
        if (i->second->isDead()) {
            world->destroyBody(i->second->getBody());
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

    world->step();
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

EnergyReceptor* Stage::getEnergyReceptor(std::string id) {
    for (auto i = energy_receptors.begin() ; i != energy_receptors.end() ; i++) {
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
    for (auto i = energy_receptors.begin();
         i != energy_receptors.end(); i++) {
        std::string id_er = i->first;
        float x_pos_er = i->second->getHorizontalPosition();
        float y_pos_er = i->second->getVerticalPosition();
        SwitchState state = i->second->getState();
        /*request[id_er] = {
                {"state", state}, {"x", x_pos_er}, {"y", y_pos_er}
        };*/
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
        SwitchState state = i->second->getState();
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
    if (cake != nullptr) {
        float x_pos_cake = cake->getHorizontalPosition();
        float y_pos_cake = cake->getVerticalPosition();
        request["Cake"] = {
                {"state", 0}, {"x", x_pos_cake}, {"y", y_pos_cake}
        };
    }

    /*for (auto i = pintools.begin(); i != pintools.end(); i++) {
        std::string id_pintool = i->first;
        float x_pos_portal = i->second->getHorizontalPosition();
        float y_pos_portal = i->second->getVerticalPosition();
        request[id_pintool] = {
                {"state", 0}, {"x", x_pos_portal}, {"y", y_pos_portal}
        };
    }*/

    return request;
}


Stage::~Stage() {
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

    for (auto i = energy_receptors.begin();
    i != energy_receptors.end(); i++) {
        delete i->second;
    }

    for (auto i = pintools.begin(); i != pintools.end(); i++) {
        delete i->second;
    }

    delete world;
    delete cake;
}
