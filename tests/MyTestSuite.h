#ifndef __MYTESTSUITE_H
#define __MYTESTSUITE_H

#include <cxxtest/TestSuite.h>
#include "../server/Stage.h"

  class StageTest : public CxxTest::TestSuite
  {
    size_t width_stage = 500;
    size_t height_stage = 500;

  public:
      void testFloorPosition( void )
      {
          std::cout << "Testing the floor position" << std::endl;




          TS_ASSERT( 1 + 1 > 1 );
          TS_ASSERT_EQUALS( 1 + 1, 2 );
      }

      void testSubstraction ( void )
      {
          TS_ASSERT ( 1 - 1 == 0);
          TS_ASSERT_EQUALS ( 1 - 1, 0);
      }
  };


#endif