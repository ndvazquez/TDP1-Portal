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
bool suite_RockBlockTest_init = false;
#include "MyTestSuite.h"

static RockBlockTest suite_RockBlockTest;

static CxxTest::List Tests_RockBlockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RockBlockTest( "MyTestSuite.h", 9, "RockBlockTest", suite_RockBlockTest, Tests_RockBlockTest );

static class TestDescription_suite_RockBlockTest_testRockBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RockBlockTest_testRockBlock() : CxxTest::RealTestDescription( Tests_RockBlockTest, suiteDescription_RockBlockTest, 18, "testRockBlock" ) {}
 void runTest() { suite_RockBlockTest.testRockBlock(); }
} testDescription_suite_RockBlockTest_testRockBlock;

static MetalBlockTest suite_MetalBlockTest;

static CxxTest::List Tests_MetalBlockTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MetalBlockTest( "MyTestSuite.h", 35, "MetalBlockTest", suite_MetalBlockTest, Tests_MetalBlockTest );

static class TestDescription_suite_MetalBlockTest_testMetalBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MetalBlockTest_testMetalBlock() : CxxTest::RealTestDescription( Tests_MetalBlockTest, suiteDescription_MetalBlockTest, 44, "testMetalBlock" ) {}
 void runTest() { suite_MetalBlockTest.testMetalBlock(); }
} testDescription_suite_MetalBlockTest_testMetalBlock;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
