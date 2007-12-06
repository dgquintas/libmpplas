/*
 * $Id$
 */

#ifndef __MATRIXRTEST_H
#define __MATRIXRTEST_H

#include "qtunit/TestCase.h"
#include "MatrixR.h"
#include "MethodsFactory.h"
#include "Random.h"


#include <pari/pari.h>

using namespace mpplas;

namespace com_uwyn_qtunit{

  class MatrixRTest : public TestCase {

    public:
      MatrixRTest();

      void setUp();
      void tearDown();

    protected:
      /* The actual tests */
      void testInverse();
      void testSolve();

    private:
      MatrixR _A;
      MatrixR _b;
      RandomFast* rnd;
      MethodsFactory& funcs;
  };
}

#endif
