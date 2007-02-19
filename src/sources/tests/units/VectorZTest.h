/*
 * $Id$
 */

#ifndef __VECTORZTEST_H
#define __VECTORZTEST_H

#include "qtunit/TestCase.h"
#include "VectorZ.h"

using namespace numth;

namespace com_uwyn_qtunit{

  class VectorZTest : public TestCase {

    public:
      VectorZTest();

      void setUp();
      void tearDown();

    protected:
      /* The actual tests */
      void testInput();
      void testOperatorAsign();
      void testCopyConstructor();
      void testToString();

      void testOperatorAddition();
      void testOperatorProduct();

    private:
      VectorZ vecA;
      VectorZ vecB;
  };
}

#endif
