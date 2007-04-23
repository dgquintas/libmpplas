/*
 * $Id: VectorRTest.h 254 2007-04-11 18:37:15Z dgquintas $
 */

#ifndef __VECTORRTEST_H
#define __VECTORRTEST_H

#include "qtunit/TestCase.h"
#include "VectorR.h"

using namespace mpplas;

namespace com_uwyn_qtunit{

  class VectorRTest : public TestCase {

    public:
      VectorRTest();

      void setUp();
      void tearDown();

    protected:
      /* The actual tests */
      void testInput();
      void testOperatorAsign();
      void testCopyConstructor();
      void testToString();

      void testOperatorAddition();
      void testOperatorProductWithR();
      void testOperatorProductWithVectorR();

      void testDot();
      void testCross();

    private:
      VectorR vecA;
      VectorR vecB;
  };
}

#endif
