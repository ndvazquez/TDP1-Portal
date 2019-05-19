#ifndef __MYTESTSUITE_H
#define __MYTESTSUITE_H

#include <cxxtest/TestSuite.h>
#include <Acid.h>
#include "../server/Stage.h"
#include "BrickBlock.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"

class BrickBlockTest : public CxxTest::TestSuite
  {
    size_t width_stage = 500;
    size_t height_stage = 500;
    size_t x_pos = 10;
    size_t y_pos = 10;
    size_t side = 2;

  public:
      void testBrickBlock(void) {
          std::cout << "Testing the brick block dimentions" << std::endl;

          Stage stage(width_stage, height_stage);
          stage.addBrickBlock(side, x_pos, y_pos);

          Coordinate* coordinates = new Coordinate(x_pos, y_pos);

          BrickBlock* block = stage.getBrickBlock(coordinates);

          TS_ASSERT_EQUALS(x_pos, block->getHorizontalPosition());
          TS_ASSERT_EQUALS(y_pos, block->getVerticalPosition());

          delete coordinates;
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
    void testMetalBlock(void) {
        std::cout << "Testing the metal block dimentions" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addMetalBlock(side, x_pos, y_pos);

        Coordinate* coordinates = new Coordinate(x_pos, y_pos);

        MetalBlock* block = stage.getMetalBlock(coordinates);

        TS_ASSERT_EQUALS(x_pos, block->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, block->getVerticalPosition());

        delete coordinates;
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
    void testEnergyTransmitter(void) {
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
    void testRock(void) {
        std::cout << "Testing the rock dimentions" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addRock(side, x_pos, y_pos);

        Coordinate* coordinates = new Coordinate(x_pos, y_pos);

        Rock* rock = stage.getRock(coordinates);

        TS_ASSERT_EQUALS(x_pos, rock->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, rock->getVerticalPosition());

        delete coordinates;
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
    void testEnergyBar(void) {
        std::cout << "Testing the energy bar dimentions" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addEnergyBar(v_side, h_side, x_pos, y_pos);

        Coordinate* coordinates = new Coordinate(x_pos, y_pos);

        EnergyBar* energy_bar = stage.getEnergyBar(coordinates);

        TS_ASSERT_EQUALS(x_pos, energy_bar->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, energy_bar->getVerticalPosition());

        delete coordinates;
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
    void testButton(void) {
        std::cout << "Testing the button dimentions" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addButton(v_side, h_side, x_pos, y_pos);

        Coordinate* coordinates = new Coordinate(x_pos, y_pos);

        Button* button = stage.getButton(coordinates);

        TS_ASSERT_EQUALS(x_pos, button->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, button->getVerticalPosition());

        delete coordinates;
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
    void testAcid(void) {
        std::cout << "Testing the acid dimentions" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addAcid(v_side, h_side, x_pos, y_pos);

        Coordinate* coordinates = new Coordinate(x_pos, y_pos);

        Acid* button = stage.getAcid(coordinates);

        TS_ASSERT_EQUALS(x_pos, button->getHorizontalPosition());
        TS_ASSERT_EQUALS(y_pos, button->getVerticalPosition());

        delete coordinates;
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
    void testOutOfRange(void) {
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
    void testChellInit(void) {
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

    void testChellFalls(void) {
        std::cout << "Testing chell falling" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addChell(h_side, v_side, initial_position_x, initial_position_y);
        Coordinate* coordinate = new Coordinate(initial_position_x, initial_position_y);
        Chell* chell = stage.getChell(coordinate);

        float dt = 1.0f/60.0f;
        float gravity = -1.0f;
        float velocity_y = 0;
        float position = initial_position_y;

        for (size_t i = 0; i < 120; i++) { //2s
            stage.step();
            velocity_y += gravity * dt;
            position += velocity_y * dt;
            TS_ASSERT_DELTA(position, chell->getVerticalPosition(), 0.1f);
            TS_ASSERT_DELTA(velocity_y, chell->getVerticalVelocity(), 0.1f);
        }
    }

    void testChellMovesRight(void) {
        std::cout << "Testing chell moving right" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addChell(h_side, v_side, initial_position_x, initial_position_y);
        Coordinate* coordinate = new Coordinate(initial_position_x, initial_position_y);
        Chell* chell = stage.getChell(coordinate);
        chell->moveRight();

        float dt = 1.0f/60.0f;
        float velocity_x = 0;
        float position = initial_position_x;
        float force = 15;
        float acceleration = force / mass;

        for (size_t i = 0; i < 120; i++) { //2s
            stage.step();
            velocity_x += acceleration * dt;
            position += velocity_x * dt;
            TS_ASSERT_DELTA(position, chell->getHorizontalPosition(), 0.1f);
            TS_ASSERT_DELTA(velocity_x, chell->getHorizontalVelocity(), 0.1f);
        }
    }

    void testChellMovesLeft(void) {
        std::cout << "Testing chell moving left" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addChell(h_side, v_side, initial_position_x, initial_position_y);
        Coordinate* coordinate = new Coordinate(initial_position_x, initial_position_y);
        Chell* chell = stage.getChell(coordinate);
        chell->moveLeft();

        float dt = 1.0f/60.0f;
        float velocity_x = 0;
        float position = initial_position_x;
        float force = -15;
        float acceleration = force / mass;

        for (size_t i = 0; i < 120; i++) { //2s
            stage.step();
            velocity_x += acceleration * dt;
            position += velocity_x * dt;
            TS_ASSERT_DELTA(position, chell->getHorizontalPosition(), 0.1f);
            TS_ASSERT_DELTA(velocity_x, chell->getHorizontalVelocity(), 0.1f);
        }
    }

    void testChellJumps(void) {
        std::cout << "Testing chell jumping" << std::endl;
        Stage stage(width_stage, height_stage);
        float position = 5;

        stage.addChell(h_side, v_side, initial_position_x, position);
        Coordinate* coordinate = new Coordinate(initial_position_x, position);
        Chell* chell = stage.getChell(coordinate);
        chell->jump();

        float velocity_y = chell->getVerticalVelocity();
        float dt = 1.0f/60.f;
        float gravity = -1.0f;

        for (size_t i = 0; i < 130; i++) { //2s
            stage.step();
            velocity_y += gravity * dt;
            position += velocity_y * dt;
            if (position <= 5) continue; //it has reached the floor
            TS_ASSERT_DELTA(velocity_y, chell->getVerticalVelocity(), 0.1f);
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
    void testEnergyBallInit(void) {
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

    void testEnergyBallDoesntFall(void) {
        std::cout << "Testing that the energy ball doesn't fall" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addEnergyBallHorizontal(side, initial_position_x, initial_position_y);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        for (size_t i = 0; i < 120; i++) { //2s
            stage.step();
            TS_ASSERT_EQUALS(initial_position_y, energy_ball->getVerticalPosition());
            TS_ASSERT_EQUALS(0, energy_ball->getVerticalVelocity());
        }
    }

    void testEnergyBallHorizontalCollidesAndChangeDirection(void) {
        std::cout << "Testing that the horizontal energy ball collides and change direction" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addEnergyBallHorizontal(side, initial_position_x, initial_position_y);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();
        float position = energy_ball->getHorizontalPosition();
        float velocity;
        float dt = 1.0f/60.f;

        for (size_t i = 0; i < 120000; i++) { //2s
            stage.step();
            velocity = energy_ball->getHorizontalVelocity();
            position += velocity * dt;
            TS_ASSERT_DELTA(position, energy_ball->getHorizontalPosition(), 1.0f);
        }
    }

    void testEnergyBallVerticalCollidesAndChangeDirection(void) {
        std::cout << "Testing that the vertical energy ball collides and change direction" << std::endl;
        Stage stage(width_stage, height_stage);
        stage.addEnergyBallVertical(side, initial_position_x, initial_position_y);
        Coordinate* coordinates = new Coordinate(initial_position_x, initial_position_y);
        EnergyBall* energy_ball = stage.getEnergyBall(coordinates);

        energy_ball->fly();
        float position = energy_ball->getVerticalPosition();
        float velocity;
        float dt = 1.0f/60.f;

        for (size_t i = 0; i < 1200; i++) { //2s
            stage.step();
            velocity = energy_ball->getVerticalVelocity();
            position += velocity * dt;
            TS_ASSERT_DELTA(position, energy_ball->getVerticalPosition(), 1.0f);
        }
    }


};
#endif