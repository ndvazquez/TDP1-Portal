/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
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
CxxTest::StaticSuiteDescription suiteDescription_BrickBlockTest( "MyTestSuite.h", 12, "BrickBlockTest", suite_BrickBlockTest, Tests_BrickBlockTest );

static class TestDescription_suite_BrickBlockTest_testBrickBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BrickBlockTest_testBrickBlock() : CxxTest::RealTestDescription( Tests_BrickBlockTest, suiteDescription_BrickBlockTest, 21, "testBrickBlock" ) {}
 void runTest() { suite_BrickBlockTest.testBrickBlock(); }
} testDescription_suite_BrickBlockTest_testBrickBlock;

static MetalBlockTest suite_MetalBlockTest;

static CxxTest::List Tests_MetalBlockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MetalBlockTest( "MyTestSuite.h", 39, "MetalBlockTest", suite_MetalBlockTest, Tests_MetalBlockTest );

static class TestDescription_suite_MetalBlockTest_testMetalBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MetalBlockTest_testMetalBlock() : CxxTest::RealTestDescription( Tests_MetalBlockTest, suiteDescription_MetalBlockTest, 48, "testMetalBlock" ) {}
 void runTest() { suite_MetalBlockTest.testMetalBlock(); }
} testDescription_suite_MetalBlockTest_testMetalBlock;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
