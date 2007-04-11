/*
 * $Id$
 */

#ifndef __MATRIXDOUBLETEST_H
#define __MATRIXDOUBLETEST_H

#include "qtunit/TestCase.h"
#include "MatrixDouble.h"

using namespace mpplas;

namespace com_uwyn_qtunit{

  class MatrixDoubleTest : public TestCase {

    public:
      MatrixDoubleTest();

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
      MatrixDouble mat;
  };
}

#endif
