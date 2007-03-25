/*
 * $Id$
 */

#ifndef __ZTEST_H
#define __ZTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Z.h"
#include "err.h"
#include "Funciones.h"
#include "Random.h"

using namespace mpplas;

namespace com_uwyn_qtunit{

  class ZTest : public TestCase {

    protected:
      Funciones* const funcs;
      Z uno, dos, cero;
      Z z1, z2;

      RandomRapido* rnd;
    public:
      ZTest();

      void setUp();
      void tearDown();

    protected:
      /* The actual tests */
      void testEquality();
      void testAddition();
      void testSubstraction();
      void testMultiplication();
      void testDivision();
      void testModulus();
      void testExponentiation();
      void testSquare();
      void testDivideByZeroThrows();
      void testModulusByZeroThrows();

      void testFactorial();
  };
}

#endif
