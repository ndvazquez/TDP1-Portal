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
bool suite_StageTest_init = false;
#include "MyTestSuite.h"

static StageTest suite_StageTest;

static CxxTest::List Tests_StageTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_StageTest( "MyTestSuite.h", 7, "StageTest", suite_StageTest, Tests_StageTest );

static class TestDescription_suite_StageTest_testFloorPosition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StageTest_testFloorPosition() : CxxTest::RealTestDescription( Tests_StageTest, suiteDescription_StageTest, 13, "testFloorPosition" ) {}
 void runTest() { suite_StageTest.testFloorPosition(); }
} testDescription_suite_StageTest_testFloorPosition;

static class TestDescription_suite_StageTest_testSubstraction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StageTest_testSubstraction() : CxxTest::RealTestDescription( Tests_StageTest, suiteDescription_StageTest, 24, "testSubstraction" ) {}
 void runTest() { suite_StageTest.testSubstraction(); }
} testDescription_suite_StageTest_testSubstraction;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
