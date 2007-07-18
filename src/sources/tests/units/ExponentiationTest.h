/*
 * $Id$
 */

#ifndef __EXPONENTIATIONTEST_H
#define __EXPONENTIATIONTEST_H

#include <string>
#include <pari/pari.h>

#include "qtunit/TestCase.h"
#include "Potencia.h"
#include "MethodsFactory.h"


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
    void testTwoThreadedModularExp();


    private:
    Z _base;
    R _baseR;
    Z _expZ;
    SignedDigit _exp;
    MethodsFactory* const funcs;
    Random* rnd;
    GenPrimos* primes;

    GEN x,y,Y,m;

  };
}
#endif
