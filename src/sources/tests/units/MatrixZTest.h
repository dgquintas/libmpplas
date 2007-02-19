/*
 * $Id$
 */

#ifndef __MATRIXZTEST_H
#define __MATRIXZTEST_H

#include "qtunit/TestCase.h"
#include "MatrixZ.h"

using namespace numth;

namespace com_uwyn_qtunit{

  class MatrixZTest : public TestCase {

    public:
      MatrixZTest();

      void setUp();
      void tearDown();

    protected:
      /* The actual tests */
      void testTranspose();
      void testInput();
      void testOperatorAsign();
      void testCopyConstructor();
      void testToString();
      void testSetDiagonal();

    private:
      MatrixZ mat;
  };
}

#endif
