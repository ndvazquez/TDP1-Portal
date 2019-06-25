/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_BrickBlockTest_init = false;
#include "MyTestSuite.h"

static BrickBlockTest suite_BrickBlockTest;

static CxxTest::List Tests_BrickBlockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BrickBlockTest( "MyTestSuite.h", 13, "BrickBlockTest", suite_BrickBlockTest, Tests_BrickBlockTest );

static class TestDescription_suite_BrickBlockTest_testBrickBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BrickBlockTest_testBrickBlock() : CxxTest::RealTestDescription( Tests_BrickBlockTest, suiteDescription_BrickBlockTest, 22, "testBrickBlock" ) {}
 void runTest() { suite_BrickBlockTest.testBrickBlock(); }
} testDescription_suite_BrickBlockTest_testBrickBlock;

static MetalBlockTest suite_MetalBlockTest;

static CxxTest::List Tests_MetalBlockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MetalBlockTest( "MyTestSuite.h", 35, "MetalBlockTest", suite_MetalBlockTest, Tests_MetalBlockTest );

static class TestDescription_suite_MetalBlockTest_testMetalBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MetalBlockTest_testMetalBlock() : CxxTest::RealTestDescription( Tests_MetalBlockTest, suiteDescription_MetalBlockTest, 44, "testMetalBlock" ) {}
 void runTest() { suite_MetalBlockTest.testMetalBlock(); }
} testDescription_suite_MetalBlockTest_testMetalBlock;

static DiagonalMetalBlockTest suite_DiagonalMetalBlockTest;

static CxxTest::List Tests_DiagonalMetalBlockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DiagonalMetalBlockTest( "MyTestSuite.h", 58, "DiagonalMetalBlockTest", suite_DiagonalMetalBlockTest, Tests_DiagonalMetalBlockTest );

static class TestDescription_suite_DiagonalMetalBlockTest_testDiagonalMetalBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DiagonalMetalBlockTest_testDiagonalMetalBlock() : CxxTest::RealTestDescription( Tests_DiagonalMetalBlockTest, suiteDescription_DiagonalMetalBlockTest, 67, "testDiagonalMetalBlock" ) {}
 void runTest() { suite_DiagonalMetalBlockTest.testDiagonalMetalBlock(); }
} testDescription_suite_DiagonalMetalBlockTest_testDiagonalMetalBlock;

static EnergyTransmitterTest suite_EnergyTransmitterTest;

static CxxTest::List Tests_EnergyTransmitterTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EnergyTransmitterTest( "MyTestSuite.h", 82, "EnergyTransmitterTest", suite_EnergyTransmitterTest, Tests_EnergyTransmitterTest );

static class TestDescription_suite_EnergyTransmitterTest_testEnergyTransmitter : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyTransmitterTest_testEnergyTransmitter() : CxxTest::RealTestDescription( Tests_EnergyTransmitterTest, suiteDescription_EnergyTransmitterTest, 92, "testEnergyTransmitter" ) {}
 void runTest() { suite_EnergyTransmitterTest.testEnergyTransmitter(); }
} testDescription_suite_EnergyTransmitterTest_testEnergyTransmitter;

static RockTest suite_RockTest;

static CxxTest::List Tests_RockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RockTest( "MyTestSuite.h", 105, "RockTest", suite_RockTest, Tests_RockTest );

static class TestDescription_suite_RockTest_testRock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RockTest_testRock() : CxxTest::RealTestDescription( Tests_RockTest, suiteDescription_RockTest, 115, "testRock" ) {}
 void runTest() { suite_RockTest.testRock(); }
} testDescription_suite_RockTest_testRock;

static EnergyBarTest suite_EnergyBarTest;

static CxxTest::List Tests_EnergyBarTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EnergyBarTest( "MyTestSuite.h", 127, "EnergyBarTest", suite_EnergyBarTest, Tests_EnergyBarTest );

static class TestDescription_suite_EnergyBarTest_testEnergyBar : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBarTest_testEnergyBar() : CxxTest::RealTestDescription( Tests_EnergyBarTest, suiteDescription_EnergyBarTest, 138, "testEnergyBar" ) {}
 void runTest() { suite_EnergyBarTest.testEnergyBar(); }
} testDescription_suite_EnergyBarTest_testEnergyBar;

static ButtonTest suite_ButtonTest;

static CxxTest::List Tests_ButtonTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ButtonTest( "MyTestSuite.h", 152, "ButtonTest", suite_ButtonTest, Tests_ButtonTest );

static class TestDescription_suite_ButtonTest_testButton : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ButtonTest_testButton() : CxxTest::RealTestDescription( Tests_ButtonTest, suiteDescription_ButtonTest, 162, "testButton" ) {}
 void runTest() { suite_ButtonTest.testButton(); }
} testDescription_suite_ButtonTest_testButton;

static AcidTest suite_AcidTest;

static CxxTest::List Tests_AcidTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AcidTest( "MyTestSuite.h", 175, "AcidTest", suite_AcidTest, Tests_AcidTest );

static class TestDescription_suite_AcidTest_testAcid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AcidTest_testAcid() : CxxTest::RealTestDescription( Tests_AcidTest, suiteDescription_AcidTest, 186, "testAcid" ) {}
 void runTest() { suite_AcidTest.testAcid(); }
} testDescription_suite_AcidTest_testAcid;

static OutOfRangeTest suite_OutOfRangeTest;

static CxxTest::List Tests_OutOfRangeTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_OutOfRangeTest( "MyTestSuite.h", 198, "OutOfRangeTest", suite_OutOfRangeTest, Tests_OutOfRangeTest );

static class TestDescription_suite_OutOfRangeTest_testOutOfRange : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_OutOfRangeTest_testOutOfRange() : CxxTest::RealTestDescription( Tests_OutOfRangeTest, suiteDescription_OutOfRangeTest, 208, "testOutOfRange" ) {}
 void runTest() { suite_OutOfRangeTest.testOutOfRange(); }
} testDescription_suite_OutOfRangeTest_testOutOfRange;

static ChellTest suite_ChellTest;

static CxxTest::List Tests_ChellTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ChellTest( "MyTestSuite.h", 235, "ChellTest", suite_ChellTest, Tests_ChellTest );

static class TestDescription_suite_ChellTest_testChellInit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellInit() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 247, "testChellInit" ) {}
 void runTest() { suite_ChellTest.testChellInit(); }
} testDescription_suite_ChellTest_testChellInit;

static class TestDescription_suite_ChellTest_testChellFalls : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellFalls() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 260, "testChellFalls" ) {}
 void runTest() { suite_ChellTest.testChellFalls(); }
} testDescription_suite_ChellTest_testChellFalls;

static class TestDescription_suite_ChellTest_testChellMovesRight : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellMovesRight() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 281, "testChellMovesRight" ) {}
 void runTest() { suite_ChellTest.testChellMovesRight(); }
} testDescription_suite_ChellTest_testChellMovesRight;

static class TestDescription_suite_ChellTest_testChellMovesLeft : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellMovesLeft() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 305, "testChellMovesLeft" ) {}
 void runTest() { suite_ChellTest.testChellMovesLeft(); }
} testDescription_suite_ChellTest_testChellMovesLeft;

static class TestDescription_suite_ChellTest_testChellJumps : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellJumps() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 329, "testChellJumps" ) {}
 void runTest() { suite_ChellTest.testChellJumps(); }
} testDescription_suite_ChellTest_testChellJumps;

static EnergyBallTest suite_EnergyBallTest;

static CxxTest::List Tests_EnergyBallTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EnergyBallTest( "MyTestSuite.h", 353, "EnergyBallTest", suite_EnergyBallTest, Tests_EnergyBallTest );

static class TestDescription_suite_EnergyBallTest_testEnergyBallInit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallInit() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 363, "testEnergyBallInit" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallInit(); }
} testDescription_suite_EnergyBallTest_testEnergyBallInit;

static class TestDescription_suite_EnergyBallTest_testEnergyBallDoesntFall : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallDoesntFall() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 376, "testEnergyBallDoesntFall" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallDoesntFall(); }
} testDescription_suite_EnergyBallTest_testEnergyBallDoesntFall;

static class TestDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAndInvertsDirection : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAndInvertsDirection() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 390, "testEnergyBallVerticalCollidesAndInvertsDirection" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallVerticalCollidesAndInvertsDirection(); }
} testDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAndInvertsDirection;

static class TestDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAgainstMetalBlockAndInvertsDirection : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAgainstMetalBlockAndInvertsDirection() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 415, "testEnergyBallVerticalCollidesAgainstMetalBlockAndInvertsDirection" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallVerticalCollidesAgainstMetalBlockAndInvertsDirection(); }
} testDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAgainstMetalBlockAndInvertsDirection;

static class TestDescription_suite_EnergyBallTest_testEnergyBallHorizontalCollidesAgainstMetalBlockAndInvertsDirection : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallHorizontalCollidesAgainstMetalBlockAndInvertsDirection() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 443, "testEnergyBallHorizontalCollidesAgainstMetalBlockAndInvertsDirection" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallHorizontalCollidesAgainstMetalBlockAndInvertsDirection(); }
} testDescription_suite_EnergyBallTest_testEnergyBallHorizontalCollidesAgainstMetalBlockAndInvertsDirection;

static class TestDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAgainstBrickBlockAndDies : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAgainstBrickBlockAndDies() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 471, "testEnergyBallVerticalCollidesAgainstBrickBlockAndDies" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallVerticalCollidesAgainstBrickBlockAndDies(); }
} testDescription_suite_EnergyBallTest_testEnergyBallVerticalCollidesAgainstBrickBlockAndDies;

static class TestDescription_suite_EnergyBallTest_testEnergyBallHorizontalCollidesAgainstBrickBlockAndDies : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallHorizontalCollidesAgainstBrickBlockAndDies() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 494, "testEnergyBallHorizontalCollidesAgainstBrickBlockAndDies" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallHorizontalCollidesAgainstBrickBlockAndDies(); }
} testDescription_suite_EnergyBallTest_testEnergyBallHorizontalCollidesAgainstBrickBlockAndDies;

static MovingRockTest suite_MovingRockTest;

static CxxTest::List Tests_MovingRockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MovingRockTest( "MyTestSuite.h", 517, "MovingRockTest", suite_MovingRockTest, Tests_MovingRockTest );

static class TestDescription_suite_MovingRockTest_testRockBlockHasGravity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MovingRockTest_testRockBlockHasGravity() : CxxTest::RealTestDescription( Tests_MovingRockTest, suiteDescription_MovingRockTest, 531, "testRockBlockHasGravity" ) {}
 void runTest() { suite_MovingRockTest.testRockBlockHasGravity(); }
} testDescription_suite_MovingRockTest_testRockBlockHasGravity;

static ChellDiesTest suite_ChellDiesTest;

static CxxTest::List Tests_ChellDiesTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ChellDiesTest( "MyTestSuite.h", 552, "ChellDiesTest", suite_ChellDiesTest, Tests_ChellDiesTest );

static class TestDescription_suite_ChellDiesTest_testChellDiesAgainstAcid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellDiesTest_testChellDiesAgainstAcid() : CxxTest::RealTestDescription( Tests_ChellDiesTest, suiteDescription_ChellDiesTest, 565, "testChellDiesAgainstAcid" ) {}
 void runTest() { suite_ChellDiesTest.testChellDiesAgainstAcid(); }
} testDescription_suite_ChellDiesTest_testChellDiesAgainstAcid;

static ShootingTest suite_ShootingTest;

static CxxTest::List Tests_ShootingTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ShootingTest( "MyTestSuite.h", 589, "ShootingTest", suite_ShootingTest, Tests_ShootingTest );

static class TestDescription_suite_ShootingTest_testBlueShotCollidesAndDies : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ShootingTest_testBlueShotCollidesAndDies() : CxxTest::RealTestDescription( Tests_ShootingTest, suiteDescription_ShootingTest, 602, "testBlueShotCollidesAndDies" ) {}
 void runTest() { suite_ShootingTest.testBlueShotCollidesAndDies(); }
} testDescription_suite_ShootingTest_testBlueShotCollidesAndDies;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
