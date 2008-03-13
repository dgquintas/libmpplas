/*
 * $Id$
 */

#ifndef __GFTEST_H
#define __GFTEST_H

#include "GF.h"
#include "GFx.h"
#include "Random.h"
#include "Primos.h"

#include "qtunit/TestCase.h"

using namespace mpplas;

namespace com_uwyn_qtunit{

  class GFTest : public TestCase {

    public:
      GFTest();

      void setUp();
      void tearDown();

      /* The actual tests */
      void testGeneratorFromPrimitivePoly();
      void testGetElement();

      void testAddition();
      void testSubstraction();
      void testMultiplication();
      void testSquare();
      void testDivision();

      void testInversion();
      void testExponentiation();

      void testConversions();

      void testInput();
    private:
      GF* gfIrred;
      GF* gfPrim;
      Random *rnd;
      PrimeGen *primes;

  };
}
#endif
