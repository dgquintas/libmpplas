/*
 * $Id$
 */

#ifndef __EXPONENTIATIONTEST_H
#define __EXPONENTIATIONTEST_H

#include <string>
#include <pari/pari.h>

#include "qtunit/TestCase.h"
#include "Potencia.h"
#include "Functions.h"


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
    Functions* const funcs;
    Random* rnd;
    GenPrimos* primes;

    GEN x,y,Y,m;

  };
}
#endif
