#ifndef ZM_NTEST_H
#define ZM_NTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Z.h"
#include "ZM_n.h"
#include "Funciones.h"
#include "Random.h"
#include "Primos.h"
#include <sstream>



using namespace mpplas;

namespace com_uwyn_qtunit{

  class ZM_nTest : public TestCase{
  
    public:
    ZM_nTest();
    void setUp();
    void tearDown();

    protected:
    /* The actual tests */
    void testAdditionWithZ();
    void testAdditionWithZM_n();

    void testSubstractionWithZ();
    void testSubstractionWithZM_n();

    void testProductWithZ();
    void testProductWithZM_n();

    void testExponentiation();

    private:
    Z integer;
    Z modulus;
    ZM_n* modularInteger;
    ZM_n* modularInteger2;

    Funciones* const funcs;
    RandomRapido *rnd;

  };
}
#endif 
