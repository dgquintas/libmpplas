/*
 * $Id$
 */

#ifndef __MATRIXZTEST_H
#define __MATRIXZTEST_H

#include "qtunit/TestCase.h"
#include "MatrixZ.h"
#include "Funciones.h"
#include "Random.h"

using namespace mpplas;

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
      void testProduct();

    private:
      MatrixZ _A;
      MatrixZ _B;
      RandomRapido* rnd;
      Funciones& funcs;
  };
}

#endif
