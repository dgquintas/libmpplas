#ifndef Z_NTEST_H
#define Z_NTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Z.h"
#include "Z_n.h"
#include "MethodsFactory.h"
#include "Random.h"
#include "Primos.h"
#include <sstream>



using namespace mpplas;

namespace com_uwyn_qtunit{

  class Z_nTest : public TestCase{
  
    public:
    Z_nTest();
    void setUp();
    void tearDown();

    protected:
    /* The actual tests */
    void testAdditionWithZ();
    void testAdditionWithDigit();
    void testAdditionWithSignedDigit();

    void testSubstractionWithZ();
    void testSubstractionWithDigit();
    void testSubstractionWithSignedDigit();

    void testProductWithZ();
    void testProductWithDigit();
    void testProductWithSignedDigit();

    void testDivisionWithZ();
    void testDivisionWithZThrows();
    void testDivisionWithDigit();
    void testDivisionWithDigitThrows();
    void testDivisionWithSignedDigit();
    void testDivisionWithSignedDigitThrows();

    void testExponentiationWithZ();
    void testExponentiationWithDigit();
    void testExponentiationWithSignedDigit();
    void testExponentiationWithSignedDigitThrows();

    private:
    Z integer;
    Z_n *modularInteger;
    Z modulus;
    Z primeModulus;
    Digit cifra;
    SignedDigit cifraSigno;

    MethodsFactory* const funcs;
    RandomFast *rnd;

  };
}
#endif /*Z_NTEST_H_*/
