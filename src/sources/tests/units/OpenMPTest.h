/*
 * $Id$
 */

#ifdef _OPENMP
#ifndef __OPENMPTEST_H
#define __OPENMPTEST_H

#include <string>
#include "Z.h"
#include "Random.h"
#include "MethodsFactory.h"

#include "qtunit/TestCase.h"

using namespace mpplas;

namespace com_uwyn_qtunit{

  class OpenMPTest : public TestCase {

    public:
      OpenMPTest();

      void setUp();
      void tearDown();

      /* The actual tests */
      void testParallelFor();
    private:
      Z *integers, *integersPAR, *integersSEQ;
      Z factor;
      MethodsFactory* const funcs;
      Random* rnd;

      static const int NUM_THREADS = 10;

  };
}
#endif
#endif
