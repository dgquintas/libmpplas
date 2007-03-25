/*
 * $Id$
 */

#ifndef __FUNCTIONSTEST_H
#define __FUNCTIONSTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Funciones.h"

namespace com_uwyn_qtunit{

  class FunctionsTest : public TestCase{

    public:
      FunctionsTest();
      void setUp();
      void tearDown();

      /* The actual tests */
      void test();
    private:
      mpplas::Funciones* const funcs;
  };
}
#endif
