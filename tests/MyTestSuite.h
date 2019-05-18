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
      void testBrickBlock( void ) {
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
    void testMetalBlock( void ) {
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
    void testEnergyTransmitter( void ) {
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
    void testRock( void ) {
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
    void testEnergyBar( void ) {
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
    void testButton( void ) {
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
    void testButton( void ) {
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



#endif