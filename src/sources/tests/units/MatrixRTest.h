/*
 * $Id$
 */

#ifndef __MATRIXRTEST_H
#define __MATRIXRTEST_H

#include "qtunit/TestCase.h"
#include "MatrixR.h"

using namespace mpplas;

namespace com_uwyn_qtunit{

  class MatrixRTest : public TestCase {

    public:
      MatrixRTest();

      void setUp();
      void tearDown();

    protected:
      /* The actual tests */
      void testTranspose();
      void testOperatorAsign();
      void testCopyConstructor();
      void testToString();
      void testSetDiagonal();

    private:
      MatrixR mat;
  };
}

#endif
