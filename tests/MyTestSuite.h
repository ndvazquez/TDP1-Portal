#ifndef __MYTESTSUITE_H
#define __MYTESTSUITE_H

#include <cxxtest/TestSuite.h>
#include <Acid.h>
#include "../server/Stage.h"
#include "BrickBlock.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"
#include "configuration.h"

class BrickBlockTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t side = 2;

public:
    void testBrickBlock() {
        std::cout << "Testing the brick block dimentions" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addBrickBlock(side, x_pos, y_pos);
        Coordinate* coordinates = new Coordinate(x_pos, y_pos);
        BrickBlock* block = stage.getBrickBlock(coordinates);

        TS_ASSERT_EQUALS(x_pos, block->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, block->getVerticalPosition());
    }
};

class MetalBlockTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t side = 2;

public:
    void testMetalBlock() {
        std::cout << "Testing the metal block dimentions" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addMetalBlock(side, x_pos, y_pos);
        Coordinate* coordinates = new Coordinate(x_pos, y_pos);
        MetalBlock* block = stage.getMetalBlock(coordinates);

        TS_ASSERT_EQUALS(x_pos, block->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, block->getVerticalPosition());
    }
};


class DiagonalMetalBlockTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t side = 2;

public:
    void testDiagonalMetalBlock() {
        std::cout << "Testing the diagonal metal block dimentions" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addDiagonalMetalBlock(side, x_pos, y_pos);
        Coordinate* coordinates = new Coordinate(x_pos, y_pos);
        DiagonalMetalBlock* block = stage.getDiagonalMetalBlock(coordinates);

        TS_ASSERT_EQUALS(x_pos, block->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, block->getVerticalPosition());
    }

};


class EnergyTransmitterTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t side = 2;

public:
    void testEnergyTransmitter() {
        std::cout << "Testing the energy transmitter dimentions" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addEnergyTransmitter(side, x_pos, y_pos);
        Coordinate* coordinates = new Coordinate(x_pos, y_pos);
        EnergyTransmitter* energy = stage.getEnergyTransmitter(coordinates);

        TS_ASSERT_EQUALS(x_pos, energy->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, energy->getVerticalPosition());

        delete coordinates;
    }
};


class RockTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t side = 2;

public:
    void testRock() {
        std::cout << "Testing the rock dimentions" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addRock(side, x_pos, y_pos);
        Coordinate* coordinates = new Coordinate(x_pos, y_pos);
        Rock* rock = stage.getRock(coordinates);

        TS_ASSERT_EQUALS(x_pos, rock->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, rock->getVerticalPosition());
    }
};

class EnergyBarTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t v_side = 2;
    size_t h_side = 4;

public:
    void testEnergyBar() {
        std::cout << "Testing the energy bar dimentions" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addEnergyBar(v_side, h_side, x_pos, y_pos);
        Coordinate* coordinates = new Coordinate(x_pos, y_pos);
        EnergyBar* energy_bar = stage.getEnergyBar(coordinates);

        TS_ASSERT_EQUALS(x_pos, energy_bar->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, energy_bar->getVerticalPosition());
    }
};


class ButtonTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t v_side = 2;
    size_t h_side = 4;

public:
    void testButton() {
        std::cout << "Testing the button dimentions" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addButton(v_side, h_side, x_pos, y_pos);
        Coordinate* coordinates = new Coordinate(x_pos, y_pos);
        Button* button = stage.getButton(coordinates);

        TS_ASSERT_EQUALS(x_pos, button->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, button->getVerticalPosition());
    }
};

class AcidTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t v_side = 2;
    size_t h_side = 4;

public:
    void testAcid() {
        std::cout << "Testing the acid dimentions" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addAcid(v_side, h_side, x_pos, y_pos);
        Coordinate* coordinates = new Coordinate(x_pos, y_pos);
        Acid* button = stage.getAcid(coordinates);

        TS_ASSERT_EQUALS(x_pos, button->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, button->getVerticalPosition());
    }
};

class OutOfRangeTest : public CxxTest::TestSuite
{
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos_bad = 600;
    size_t x_pos_ok = 1;
    size_t y_pos_bad = 600;
    size_t y_pos_ok = 1;

public:
    void testOutOfRange() {
        std::cout << "Testing the out of range excepcion" << std::endl;

        Stage stage(width_stage, height_stage);
        try {
            stage.addBrickBlock(5, x_pos_bad, y_pos_ok);
        }
        catch (...) {
            std::cout << "Catching the excepcion correctly 1" << std::endl;
        }
        try {
            stage.addBrickBlock(5, x_pos_ok, y_pos_bad);
        }
        catch (...) {
            std::cout << "Catching the excepcion correctly 2" << std::endl;
        }
        try {
            stage.addBrickBlock(5, x_pos_bad, y_pos_bad);
        }
        catch (...) {
            std::cout << "Catching the excepcion correctly 3" << std::endl;
            return;
        }
        TS_ASSERT_EQUALS(1, 0);
    }
};

class ChellTest : public CxxTest::TestSuite {

    size_t width_stage = 1000;
    size_t height_stage = 1000;
    size_t initial_position_x = 500;
    size_t initial_position_y = 100;
    size_t v_side = 10;
    size_t h_side = 10;
    size_t mass = v_side * h_side;

public:
    void testChellInit() {
        std::cout << "Testing the creation of Chell" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(v_side, h_side, initial_position_x, initial_position_y);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        Chell* chell = stage.getChell(coordinates);

        TS_ASSERT_EQUALS(initial_position_x, chell->getHorizontalPosition());
        TS_ASSERT_EQUALS(initial_position_y, chell->getVerticalPosition());
        TS_ASSERT_EQUALS(0, chell->getHorizontalVelocity());
        TS_ASSERT_EQUALS(0, chell->getVerticalVelocity());
    }

    void testChellFalls() {
        std::cout << "Testing chell falling" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(h_side, v_side, initial_position_x, initial_position_y);
        Coordinate* coordinate = new Coordinate(initial_position_x, initial_position_y);
        Chell* chell = stage.getChell(coordinate);

        float dt = 1.0f/60.0f;
        float gravity = gameConfiguration.gravity;
        float velocity_y = 0;
        float position = initial_position_y;

        for (size_t i = 0; i < 120; i++) {
            stage.step();
            velocity_y += gravity * dt;
            position += velocity_y * dt;
            TS_ASSERT_DELTA(position, chell->getVerticalPosition(), 0.1f);
            TS_ASSERT_DELTA(velocity_y, chell->getVerticalVelocity(), 0.1f);
        }
    }

    void testChellMovesRight() {
        std::cout << "Testing chell moving right" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(h_side, v_side, initial_position_x, initial_position_y);
        Coordinate* coordinate = new Coordinate(initial_position_x, initial_position_y);
        Chell* chell = stage.getChell(coordinate);

        chell->moveRight();

        float dt = 1.0f/60.0f;
        float velocity_x = 0;
        float position = initial_position_x;
        float force = gameConfiguration.chellForce;
        float acceleration = force / mass;

        for (size_t i = 0; i < 120; i++) {
            stage.step();
            if (velocity_x <= 0.5) velocity_x += acceleration * dt;
            position += velocity_x * dt;
            TS_ASSERT_DELTA(position, chell->getHorizontalPosition(), 0.1f);
            TS_ASSERT_DELTA(velocity_x, chell->getHorizontalVelocity(), 0.1f);
        }
    }

    void testChellMovesLeft() {
        std::cout << "Testing chell moving left" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(h_side, v_side, initial_position_x, initial_position_y);
        Coordinate* coordinate = new Coordinate(initial_position_x, initial_position_y);
        Chell* chell = stage.getChell(coordinate);

        chell->moveLeft();

        float dt = 1.0f/60.0f;
        float velocity_x = 0;
        float position = initial_position_x;
        float force = -gameConfiguration.chellForce;
        float acceleration = force / mass;

        for (size_t i = 0; i < 120; i++) {
            stage.step();
            if(velocity_x >= -0.5) velocity_x += acceleration * dt;
            position += velocity_x * dt;
            TS_ASSERT_DELTA(position, chell->getHorizontalPosition(), 0.1f);
            TS_ASSERT_DELTA(velocity_x, chell->getHorizontalVelocity(), 0.1f);
        }
    }

    void testChellJumps() {
        std::cout << "Testing chell jumping" << std::endl;

        Stage stage(width_stage, height_stage);
        float position = 5;
        stage.addChell(h_side, v_side, initial_position_x, position);
        Coordinate* coordinate = new Coordinate(initial_position_x, position);
        Chell* chell = stage.getChell(coordinate);

        chell->jump();

        float velocity_y = chell->getVerticalVelocity();
        float dt = 1.0f/60.f;
        float gravity = gameConfiguration.gravityJump;

        for (size_t i = 0; i < 130; i++) {
            stage.step();
            velocity_y += gravity * dt;
            position += velocity_y * dt;
            if (position <= 5) continue; //it has reached the floor
            TS_ASSERT_DELTA(position, chell->getVerticalPosition(), 0.1f);
        }
    }
};

class EnergyBallTest : public CxxTest::TestSuite {
    size_t width_stage = 1000;
    size_t height_stage = 1000;
    size_t initial_position_x = 500;
    size_t initial_position_y = 500;
    size_t side = 10;
    size_t mass = side * side;

public:
    void testEnergyBallInit() {
        std::cout << "Testing the creation of EnergyBall" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addEnergyBallHorizontal(side, initial_position_x, initial_position_y);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        TS_ASSERT_EQUALS(initial_position_x, energy_ball->getHorizontalPosition());
        TS_ASSERT_EQUALS(initial_position_y, energy_ball->getVerticalPosition());
        TS_ASSERT_EQUALS(0, energy_ball->getHorizontalVelocity());
        TS_ASSERT_EQUALS(0, energy_ball->getVerticalVelocity());
    }

    void testEnergyBallDoesntFall() {
        std::cout << "Testing that the energy ball doesn't fall" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addEnergyBallHorizontal(side, initial_position_x, initial_position_y);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        for (size_t i = 0; i < 120; i++) {
            stage.step();
            TS_ASSERT_EQUALS(initial_position_y, energy_ball->getVerticalPosition());
            TS_ASSERT_EQUALS(0, energy_ball->getVerticalVelocity());
        }
    }

    void testEnergyBallHorizontalCollidesAndInvertsDirection() {
        std::cout << "Testing that the horizontal energy ball collides against a wall and inverts direction" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addEnergyBallHorizontal(side, width_stage - 50, initial_position_y);
        Coordinate* coordinates = new Coordinate(width_stage - 50, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();

        float position = energy_ball->getHorizontalPosition();
        float velocity;
        float dt = 1.0f/60.f;

        bool test = false;

        for (size_t i = 0; i < 120000; i++) {
            stage.step();
            velocity = energy_ball->getHorizontalVelocity();
            position += velocity * dt;
            TS_ASSERT_DELTA(position, energy_ball->getHorizontalPosition(), 1.0f);
            if (position < width_stage - 50) test = true;
        }
        TS_ASSERT_EQUALS(test, true);
    }

    void testEnergyBallVerticalCollidesAndInvertsDirection() {
        std::cout << "Testing that the vertical energy ball collides against a wall and inverts direction" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addEnergyBallVertical(side, initial_position_x, height_stage - 50);
        Coordinate* coordinates = new Coordinate(initial_position_x, height_stage - 50);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();

        float position = energy_ball->getVerticalPosition();
        float velocity;
        float dt = 1.0f/60.f;

        bool test = false;

        for (size_t i = 0; i < 1100; i++) {
            stage.step();
            velocity = energy_ball->getVerticalVelocity();
            position += velocity * dt;
            TS_ASSERT_DELTA(position, energy_ball->getVerticalPosition(), 1.0f);
            if (position < height_stage - 50) test = true;
        }
        TS_ASSERT_EQUALS(test, true);
    }

    void testEnergyBallVerticalCollidesAgainstMetalBlockAndInvertsDirection() {
        std::cout << "Testing that the vertical energy ball collides against a metal block and inverts direction" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addEnergyBallVertical(side, initial_position_x, initial_position_y);
        stage.addMetalBlock(side, initial_position_x, initial_position_y + 10);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();

        float position = energy_ball->getVerticalPosition();
        float velocity;
        float dt = 1.0f/60.f;

        bool test = false;

        for (size_t i = 0; i < 120; i++) { //2s
            stage.step();
            velocity = energy_ball->getVerticalVelocity();
            position += velocity * dt;
            TS_ASSERT_DELTA(position, energy_ball->getVerticalPosition(), 1.0f);
            if (position < (initial_position_y + 10)) {
                test = true;
            }
        }
        TS_ASSERT_EQUALS(test, true);
    }

    void testEnergyBallHorizontalCollidesAgainstMetalBlockAndInvertsDirection() {
        std::cout << "Testing that the horizontal energy ball collides against a metal block and inverts direction" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addEnergyBallHorizontal(side, initial_position_x, initial_position_y);
        stage.addMetalBlock(side, initial_position_x + 10, initial_position_y);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();

        float position = energy_ball->getHorizontalPosition();
        float velocity;
        float dt = 1.0f/60.f;

        bool test = false;

        for (size_t i = 0; i < 120; i++) { //2s
            stage.step();
            velocity = energy_ball->getHorizontalVelocity();
            position += velocity * dt;
            TS_ASSERT_DELTA(position, energy_ball->getHorizontalPosition(), 1.0f);
            if (position < initial_position_x + 10) {
                test = true;
            }
        }
        TS_ASSERT_EQUALS(test, true);
    }

    void testEnergyBallVerticalCollidesAgainstBrickBlockAndDies() {
        std::cout << "Testing that the vertical energy ball collides against brick block and dies" << std::endl;

        float initial_position_x_brick_block = initial_position_x;
        float initial_position_y_brick_block = initial_position_y + 10; //colliding
        Stage stage(width_stage, height_stage);
        stage.addEnergyBallVertical(side, initial_position_x, initial_position_y);
        stage.addBrickBlock(side, initial_position_x_brick_block, initial_position_y_brick_block);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();

        bool test = false;
        for (size_t i = 0; i < 300; i++) {
            if (energy_ball->isDead()) {
                test = true;
                break;
            }
            stage.step();
        }
        TS_ASSERT_EQUALS(test, true);
    }

    void testEnergyBallHorizontalCollidesAgainstBrickBlockAndDies() {
        std::cout << "Testing that the horizontal energy ball collides against brick block and dies" << std::endl;

        float initial_position_x_brick_block = initial_position_x + 10;
        float initial_position_y_brick_block = initial_position_y; //colliding
        Stage stage(width_stage, height_stage);
        stage.addEnergyBallHorizontal(side, initial_position_x, initial_position_y);
        stage.addBrickBlock(side, initial_position_x_brick_block, initial_position_y_brick_block);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();
        bool test = false;
        for (size_t i = 0; i < 300; i++) {
            if (energy_ball->isDead()) {
                test = true;
                break;
            }
            stage.step();
        }
        TS_ASSERT_EQUALS(test, true);
    }

    void testEnergyBallHorizontalCollidesAgainstDiagonalMetalBlockAndChangesDirection() {
        std::cout << "Testing that the horizontal energy ball collides against diagonal metal block and changes direction" << std::endl;

        float initial_position_x_diagonal_block = initial_position_x + 100;
        float initial_position_y_diagonal_block = initial_position_y; //colliding
        Stage stage(width_stage, height_stage);
        stage.addEnergyBallHorizontal(side, initial_position_x, initial_position_y);
        stage.addDiagonalMetalBlock(side, initial_position_x_diagonal_block, initial_position_y_diagonal_block);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();

        bool test = false;
        for (size_t i = 0; i < 3000; i++) {
            if (energy_ball->isVertical()) {
                test = true;
                break;
            }
            stage.step();
        }
        TS_ASSERT_EQUALS(test, true);
    }

    void testEnergyBallVerticalCollidesAgainstDiagonalMetalBlockAndChangesDirection() {
        std::cout << "Testing that the vertical energy ball collides against diagonal metal block and changes direction" << std::endl;

        float initial_position_x_diagonal_block = initial_position_x;
        float initial_position_y_diagonal_block = initial_position_y + 100; //colliding
        Stage stage(width_stage, height_stage);
        stage.addEnergyBallVertical(side, initial_position_x, initial_position_y);
        stage.addDiagonalMetalBlock(side, initial_position_x_diagonal_block, initial_position_y_diagonal_block);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();

        bool test = false;
        for (size_t i = 0; i < 3000; i++) {
            if (! energy_ball->isVertical()) {
                test = true;
                break;
            }
            stage.step();
        }
        TS_ASSERT_EQUALS(test, true);
    }
};

class MovingRockTest :  public CxxTest::TestSuite {
    size_t width_stage = 1000;
    size_t height_stage = 1000;
    size_t initial_pos_x_chell = 500;
    size_t initial_pos_y = 500;
    size_t initial_pos_x_rock = 520;
    size_t side_rock = 10;
    size_t mass_rock = side_rock * side_rock;
    size_t side_chell = 2;
    size_t mass_chell = side_chell * side_chell;

public:
    void testRockBlockHasGravity() {
        std::cout << "Testing that the rock has gravity" << std::endl;

        /* Stage stage(width_stage, height_stage);
         stage.addRock(side_rock, initial_pos_x_rock, initial_pos_y);
         Coordinate* coordinate = new Coordinate(initial_pos_x_rock, initial_pos_y);
         Rock* rock = stage.getRock(coordinate);
         float dt = 1.0f/60.0f;
         float gravity = gameConfiguration.gravity;
         float velocity_y = 0;
         float position = initial_pos_y;
         for (size_t i = 0; i < 120; i++) {
             stage.step();
             velocity_y += gravity * dt;
             position += velocity_y * dt;
             TS_ASSERT_DELTA(position, rock->getVerticalPosition(), 0.1f);
             TS_ASSERT_DELTA(velocity_y, rock->getVerticalVelocity(), 0.1f);
         }*/
    }

    void testRockBlockMovesRight() {
        std::cout << "Testing that the rock block moves right" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(side_chell, side_chell, initial_pos_x_chell, initial_pos_y);
        Coordinate* coordinate_chell = new Coordinate(initial_pos_x_chell, initial_pos_y);
        Chell* chell = stage.getChell(coordinate_chell);
        stage.addRock(side_rock, initial_pos_x_rock, initial_pos_y);
        Coordinate* coordinate_rock = new Coordinate(initial_pos_x_rock, initial_pos_y);
        Rock* rock = stage.getRock(coordinate_rock);

        chell->grabRock(rock);
        chell->moveRight();

        float dt = 1.0f/60.0f;

        float old_pos = rock->getHorizontalPosition();

        float velocity_x_chell = 0;
        float position_chell = initial_pos_x_chell;
        float force_chell = gameConfiguration.chellForce;
        float acceleration_chell = force_chell / mass_chell;

        for (size_t i = 0; i < 120; i++) {
            stage.step();

            float pos_actual = rock->getHorizontalPosition();
            TS_ASSERT_EQUALS(old_pos <= pos_actual, true)
            TS_ASSERT_EQUALS(rock->getHorizontalVelocity() > 0, true);
            old_pos = rock->getHorizontalPosition();

            if (velocity_x_chell <= 0.5) velocity_x_chell += acceleration_chell * dt;
            position_chell += velocity_x_chell * dt;
            TS_ASSERT_DELTA(position_chell, chell->getHorizontalPosition(), 0.2f);
            TS_ASSERT_DELTA(velocity_x_chell, chell->getHorizontalVelocity(), 0.1f);
        }
    }

    void testRockBlockMovesLeft() {
        std::cout << "Testing that the rock block moves left" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(side_chell, side_chell, initial_pos_x_chell, initial_pos_y);
        Coordinate* coordinate_chell = new Coordinate(initial_pos_x_chell, initial_pos_y);
        Chell* chell = stage.getChell(coordinate_chell);
        stage.addRock(side_rock, initial_pos_x_rock, initial_pos_y);
        Coordinate* coordinate_rock = new Coordinate(initial_pos_x_rock, initial_pos_y);
        Rock* rock = stage.getRock(coordinate_rock);

        chell->grabRock(rock);
        chell->moveLeft();

        float dt = 1.0f/60.0f;

        float old_pos = rock->getHorizontalPosition();

        float velocity_x_chell = 0;
        float position_chell = initial_pos_x_chell;
        float force_chell = -gameConfiguration.chellForce;
        float acceleration_chell = force_chell / mass_chell;

        for (size_t i = 0; i < 120; i++) {
            stage.step();

            float pos_actual = rock->getHorizontalPosition();
            TS_ASSERT_EQUALS(old_pos >= pos_actual, true)
            TS_ASSERT_EQUALS(rock->getHorizontalVelocity() < 0, true);
            old_pos = rock->getHorizontalPosition();

            if (velocity_x_chell >= -0.5) velocity_x_chell += acceleration_chell * dt;
            position_chell += velocity_x_chell * dt;
            TS_ASSERT_DELTA(position_chell, chell->getHorizontalPosition(), 0.2f);
            TS_ASSERT_DELTA(velocity_x_chell, chell->getHorizontalVelocity(), 0.1f);
        }
    }

};

class ChellDiesTest :  public CxxTest::TestSuite {
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos_chell = 1;
    size_t y_pos = 1;
    size_t x_pos_acid = 4;
    size_t side_chell = 2;
    size_t side_acid = 1;


public:
    void testChellDiesAgainstAcid() {
        std::cout << "Testing that Chell dies against acid" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(side_chell, side_chell, x_pos_chell, y_pos);
        stage.addAcid(side_acid, side_acid, x_pos_acid, y_pos);

        Coordinate* coordinates = new Coordinate(x_pos_chell, y_pos);
        Chell* chell_right = stage.getChell(coordinates);

        bool test_right = false;
        chell_right->moveRight();

        TS_ASSERT_EQUALS(chell_right->isDead(), false);

        for (size_t i = 0; i < 120000; i++) {
            if (chell_right->isDead()) {
                test_right = true;
            }
            stage.step();
        }
        TS_ASSERT_EQUALS(test_right, true);

        stage.addChell(side_chell, side_chell, x_pos_acid, y_pos);
        stage.addAcid(side_acid, side_acid, x_pos_chell, y_pos);

        Coordinate* coordinate_left = new Coordinate(x_pos_acid, y_pos);
        Chell* chell_left = stage.getChell(coordinate_left);

        bool test_left = false;
        chell_left->moveLeft();

        TS_ASSERT_EQUALS(chell_left->isDead(), false);

        std::cout << "Now the other direction" << std::endl;

        for (size_t i = 0; i < 120000; i++) {
            if (chell_left->isDead()) {
                test_left = true;
            }
            stage.step();
        }
        TS_ASSERT_EQUALS(test_left, true);
    }

    void testChellDiesAgainstEnergyBall() {
        std::cout << "Testing that Chell dies against an energy ball" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(side_chell, side_chell, x_pos_chell, y_pos);
        stage.addEnergyBallHorizontal(side_acid + 1, x_pos_acid, y_pos);

        Coordinate* coordinates = new Coordinate(x_pos_chell, y_pos);
        Chell* chell = stage.getChell(coordinates);
        EnergyBall* energy_ball = stage.getEnergyBall(new Coordinate(x_pos_acid, y_pos));

        bool test_right = false;
        chell->moveRight();

        TS_ASSERT_EQUALS(chell->isDead(), false);

        for (size_t i = 0; i < 120000; i++) {
            if (chell->isDead()) {
                test_right = true;
                TS_ASSERT_EQUALS(test_right, true);
                return;
            }
            stage.step();
        }
        TS_ASSERT_EQUALS(1, 0);
    }


    void testChellDiesWhenARockFallsOnHer() {
        std::cout << "Testing that Chell dies when a rock falls on her" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(side_chell, side_chell, x_pos_chell, 1);
        stage.addRock(side_acid + 1, x_pos_chell, 20);

        Chell* chell = stage.getChell(new Coordinate(x_pos_chell, 1));
        Rock* rock = stage.getRock(new Coordinate(x_pos_chell, 20));

        for (size_t i = 0; i < 1200; i++) {
            stage.step();
            if (chell->isDead()) {
                TS_ASSERT_EQUALS(chell->isDead(), true);
                return;
            }
        }
        TS_ASSERT_EQUALS(1, 0);
    }

    void testChellDoesntDieWhenSheHitsARock() {
        std::cout << "Testing that Chell doesn't die when a she hits a rock" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(side_chell, side_chell, x_pos_chell, 1);
        stage.addRock(side_acid + 1, x_pos_chell + 5, 1);

        Chell* chell = stage.getChell(new Coordinate(x_pos_chell, 1));
        Rock* rock = stage.getRock(new Coordinate(x_pos_chell + 5, 1));
        chell->moveRight();
        /*
        for (size_t i = 0; i < 1200; i++) {
            stage.step();
        }*/
    }
};

class PortalTest :  public CxxTest::TestSuite {
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos_chell = 1;
    size_t y_pos = 1;
    size_t side_chell = 2;
    size_t side_portal = 2;

public:
    void testChellTeleportsCorrectly() {
        std::cout << "Testing that Chell teleports correctly" << std::endl;

        Coordinate* original_coordinate = new Coordinate(x_pos_chell, y_pos);
        Coordinate* coordinate_to_teleport = new Coordinate(5, 9);

        Stage stage(width_stage, height_stage);
        stage.addChell(side_chell, side_chell, x_pos_chell, y_pos);

        Chell* chell = stage.getChell(new Coordinate(x_pos_chell, y_pos));
        chell->teleport(coordinate_to_teleport);

        TS_ASSERT_EQUALS(chell->getHorizontalPosition() == 5, true);
        TS_ASSERT_EQUALS(chell->getVerticalPosition() == 9, true);
    }

    void testChellTeleportsWhenHittingAPortal() {
        std::cout << "Testing that Chell teleports while hitting a portal" << std::endl;

        Stage stage(width_stage, height_stage);
        stage.addChell(side_chell, side_chell, x_pos_chell, y_pos);
        stage.addOrangePortal(side_portal, x_pos_chell + 5, y_pos);
        stage.addBluePortal(side_portal, x_pos_chell + 20, y_pos + 20);
        Chell* chell = stage.getChell(new Coordinate(x_pos_chell, y_pos));

        chell->moveRight();

        for (size_t i = 0; i < 1200; i++) {
            stage.step();
            if (chell->getHorizontalPosition() > 20 && chell->getVerticalPosition() > 20) return;
        }
        TS_ASSERT_EQUALS(1, 0);
    }
};


#endif