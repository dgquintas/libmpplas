/*
 * $Id$
 */

#ifndef __ZXTEST_H
#define __ZXTEST_H

#include "qtunit/TestCase.h"
#include "Polynomial.h"
#include "Random.h"
#include "Zx.h"


#include <pari/pari.h>

using namespace mpplas;

namespace com_uwyn_qtunit{

  class ZxTest : public TestCase {

    public:
      ZxTest();

      void setUp();
      void tearDown();

    protected:
      void testAddition();
      void testDifference();
      void testProduct();
      void testPseudoDivision();
      void testGCDKnuth();
      void testGCDCollins();
      void testEvaluation();

    private:
      Zx polA;
      Zx polB;
      Zx polC;

      GEN polPariA;
      GEN polPariB;
      GEN polPariC;

      RandomFast* rnd;
  };
}

#endif
