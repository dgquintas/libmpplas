#ifndef Z_NTEST_H
#define Z_NTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Z.h"
#include "Z_n.h"
#include "Funciones.h"
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
    void testAdditionWithCifra();
    void testAdditionWithCifraSigno();

    void testSubstractionWithZ();
    void testSubstractionWithCifra();
    void testSubstractionWithCifraSigno();

    void testProductWithZ();
    void testProductWithCifra();
    void testProductWithCifraSigno();

    void testDivisionWithZ();
    void testDivisionWithZThrows();
    void testDivisionWithCifra();
    void testDivisionWithCifraThrows();
    void testDivisionWithCifraSigno();
    void testDivisionWithCifraSignoThrows();

    void testExponentiationWithZ();
    void testExponentiationWithCifra();
    void testExponentiationWithCifraSigno();
    void testExponentiationWithCifraSignoThrows();

    private:
    Z integer;
    Z_n *modularInteger;
    Z modulus;
    Z primeModulus;
    Cifra cifra;
    CifraSigno cifraSigno;

    Funciones* const funcs;
    RandomRapido *rnd;

  };
}
#endif /*Z_NTEST_H_*/
