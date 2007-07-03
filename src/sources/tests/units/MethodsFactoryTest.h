/*
 * $Id: MethodsFactoryTest.h 338 2007-06-29 21:59:44Z dgquintas $
 */

#ifndef __FUNCTIONSTEST_H
#define __FUNCTIONSTEST_H

#include <string>

#include "qtunit/TestCase.h"
#include "MethodsFactory.h"

namespace com_uwyn_qtunit{

  class MethodsFactoryTest : public TestCase{

    public:
      MethodsFactoryTest();
      void setUp();
      void tearDown();

      /* The actual tests */
      void testSet();
      void testGet();
      void testReset();
    private:
      mpplas::MethodsFactory& _funcs;
  };
}
#endif
