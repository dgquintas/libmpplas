/*
 * $Id: RandomTest.h 254 2007-04-11 18:37:15Z dgquintas $
 */

#ifndef __PRIMESTEST_H
#define __PRIMESTEST_H

#include <string>

#include "qtunit/TestCase.h"
#include "Primos.h"


using namespace mpplas;

namespace com_uwyn_qtunit{
 
  class PrimesTest: public TestCase {

    public:
    PrimesTest();

    void setUp();
    void tearDown();

    protected:
    /* The actual tests */
    void testRabinMiller();
    void testMersenneLucasLehmer();
    void testGenerator();

    private:
      RabinMiller _rm;
      PrimeGen _primeGen;
  };
}
#endif
