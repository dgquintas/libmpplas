/*
 * $Id$
 */

#ifndef __EXPONENTIATIONTEST_H
#define __EXPONENTIATIONTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Potencia.h"
#include <pari/pari.h>

using namespace mpplas;

namespace com_uwyn_qtunit{
 
  class ExponentiationTest : public TestCase {

    public:
    ExponentiationTest();

    void setUp();
    void tearDown();

    protected:
    /* The actual tests */

    void testSlidingWindowExp();
    void testSlidingWindowExpR();
    void testExpLeftRight();
    void testExpMontgomery();
    void testExpBarrett();

    private:
    Z _base;
    R _baseR;
    Z _expZ;
    SignedDigit _exp;
    Funciones* const funcs;
    Random* rnd;
    GenPrimos* primes;

    GEN x,y,Y,m;

  };
}
#endif
