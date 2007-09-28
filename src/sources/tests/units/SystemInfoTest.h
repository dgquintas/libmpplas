/*
 * $Id $
 */

#ifndef __SYSTEMINFOTEST_H
#define __SYSTEMINFOTEST_H

#include "qtunit/TestCase.h"
#include "SystemInfo.h"

#include <string>


using namespace mpplas;

namespace com_uwyn_qtunit{
  class SystemInfoTest : public TestCase {

    public:
      SystemInfoTest();

      void setUp();
      void tearDown();

      /* The actual tests */
      void testSystemInfo();
  };
}
#endif
