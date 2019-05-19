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
CxxTest::StaticSuiteDescription suiteDescription_BrickBlockTest( "MyTestSuite.h", 11, "BrickBlockTest", suite_BrickBlockTest, Tests_BrickBlockTest );

static class TestDescription_suite_BrickBlockTest_testBrickBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BrickBlockTest_testBrickBlock() : CxxTest::RealTestDescription( Tests_BrickBlockTest, suiteDescription_BrickBlockTest, 20, "testBrickBlock" ) {}
 void runTest() { suite_BrickBlockTest.testBrickBlock(); }
} testDescription_suite_BrickBlockTest_testBrickBlock;

static MetalBlockTest suite_MetalBlockTest;

static CxxTest::List Tests_MetalBlockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MetalBlockTest( "MyTestSuite.h", 37, "MetalBlockTest", suite_MetalBlockTest, Tests_MetalBlockTest );

static class TestDescription_suite_MetalBlockTest_testMetalBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MetalBlockTest_testMetalBlock() : CxxTest::RealTestDescription( Tests_MetalBlockTest, suiteDescription_MetalBlockTest, 46, "testMetalBlock" ) {}
 void runTest() { suite_MetalBlockTest.testMetalBlock(); }
} testDescription_suite_MetalBlockTest_testMetalBlock;

static EnergyTransmitterTest suite_EnergyTransmitterTest;

static CxxTest::List Tests_EnergyTransmitterTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EnergyTransmitterTest( "MyTestSuite.h", 62, "EnergyTransmitterTest", suite_EnergyTransmitterTest, Tests_EnergyTransmitterTest );

static class TestDescription_suite_EnergyTransmitterTest_testEnergyTransmitter : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyTransmitterTest_testEnergyTransmitter() : CxxTest::RealTestDescription( Tests_EnergyTransmitterTest, suiteDescription_EnergyTransmitterTest, 71, "testEnergyTransmitter" ) {}
 void runTest() { suite_EnergyTransmitterTest.testEnergyTransmitter(); }
} testDescription_suite_EnergyTransmitterTest_testEnergyTransmitter;

static RockTest suite_RockTest;

static CxxTest::List Tests_RockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RockTest( "MyTestSuite.h", 88, "RockTest", suite_RockTest, Tests_RockTest );

static class TestDescription_suite_RockTest_testRock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RockTest_testRock() : CxxTest::RealTestDescription( Tests_RockTest, suiteDescription_RockTest, 97, "testRock" ) {}
 void runTest() { suite_RockTest.testRock(); }
} testDescription_suite_RockTest_testRock;

static EnergyBarTest suite_EnergyBarTest;

static CxxTest::List Tests_EnergyBarTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EnergyBarTest( "MyTestSuite.h", 113, "EnergyBarTest", suite_EnergyBarTest, Tests_EnergyBarTest );

static class TestDescription_suite_EnergyBarTest_testEnergyBar : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBarTest_testEnergyBar() : CxxTest::RealTestDescription( Tests_EnergyBarTest, suiteDescription_EnergyBarTest, 123, "testEnergyBar" ) {}
 void runTest() { suite_EnergyBarTest.testEnergyBar(); }
} testDescription_suite_EnergyBarTest_testEnergyBar;

static ButtonTest suite_ButtonTest;

static CxxTest::List Tests_ButtonTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ButtonTest( "MyTestSuite.h", 140, "ButtonTest", suite_ButtonTest, Tests_ButtonTest );

static class TestDescription_suite_ButtonTest_testButton : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ButtonTest_testButton() : CxxTest::RealTestDescription( Tests_ButtonTest, suiteDescription_ButtonTest, 150, "testButton" ) {}
 void runTest() { suite_ButtonTest.testButton(); }
} testDescription_suite_ButtonTest_testButton;

static AcidTest suite_AcidTest;

static CxxTest::List Tests_AcidTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AcidTest( "MyTestSuite.h", 166, "AcidTest", suite_AcidTest, Tests_AcidTest );

static class TestDescription_suite_AcidTest_testAcid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AcidTest_testAcid() : CxxTest::RealTestDescription( Tests_AcidTest, suiteDescription_AcidTest, 176, "testAcid" ) {}
 void runTest() { suite_AcidTest.testAcid(); }
} testDescription_suite_AcidTest_testAcid;

static OutOfRangeTest suite_OutOfRangeTest;

static CxxTest::List Tests_OutOfRangeTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_OutOfRangeTest( "MyTestSuite.h", 192, "OutOfRangeTest", suite_OutOfRangeTest, Tests_OutOfRangeTest );

static class TestDescription_suite_OutOfRangeTest_testOutOfRange : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_OutOfRangeTest_testOutOfRange() : CxxTest::RealTestDescription( Tests_OutOfRangeTest, suiteDescription_OutOfRangeTest, 202, "testOutOfRange" ) {}
 void runTest() { suite_OutOfRangeTest.testOutOfRange(); }
} testDescription_suite_OutOfRangeTest_testOutOfRange;

static ChellTest suite_ChellTest;

static CxxTest::List Tests_ChellTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ChellTest( "MyTestSuite.h", 228, "ChellTest", suite_ChellTest, Tests_ChellTest );

static class TestDescription_suite_ChellTest_testChellInit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellInit() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 239, "testChellInit" ) {}
 void runTest() { suite_ChellTest.testChellInit(); }
} testDescription_suite_ChellTest_testChellInit;

static class TestDescription_suite_ChellTest_testChellFalls : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellFalls() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 252, "testChellFalls" ) {}
 void runTest() { suite_ChellTest.testChellFalls(); }
} testDescription_suite_ChellTest_testChellFalls;

static class TestDescription_suite_ChellTest_testChellMovesRight : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellMovesRight() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 273, "testChellMovesRight" ) {}
 void runTest() { suite_ChellTest.testChellMovesRight(); }
} testDescription_suite_ChellTest_testChellMovesRight;

static class TestDescription_suite_ChellTest_testChellMovesLeft : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellMovesLeft() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 296, "testChellMovesLeft" ) {}
 void runTest() { suite_ChellTest.testChellMovesLeft(); }
} testDescription_suite_ChellTest_testChellMovesLeft;

static class TestDescription_suite_ChellTest_testChellJumps : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ChellTest_testChellJumps() : CxxTest::RealTestDescription( Tests_ChellTest, suiteDescription_ChellTest, 319, "testChellJumps" ) {}
 void runTest() { suite_ChellTest.testChellJumps(); }
} testDescription_suite_ChellTest_testChellJumps;

static EnergyBallTest suite_EnergyBallTest;

static CxxTest::List Tests_EnergyBallTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EnergyBallTest( "MyTestSuite.h", 344, "EnergyBallTest", suite_EnergyBallTest, Tests_EnergyBallTest );

static class TestDescription_suite_EnergyBallTest_testEnergyBallInit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallInit() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 353, "testEnergyBallInit" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallInit(); }
} testDescription_suite_EnergyBallTest_testEnergyBallInit;

static class TestDescription_suite_EnergyBallTest_testEnergyBallDoesntFall : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EnergyBallTest_testEnergyBallDoesntFall() : CxxTest::RealTestDescription( Tests_EnergyBallTest, suiteDescription_EnergyBallTest, 366, "testEnergyBallDoesntFall" ) {}
 void runTest() { suite_EnergyBallTest.testEnergyBallDoesntFall(); }
} testDescription_suite_EnergyBallTest_testEnergyBallDoesntFall;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
