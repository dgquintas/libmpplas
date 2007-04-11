/*
 * $Id$
 */

#ifndef __EXPONENTIATIONTEST_H
#define __EXPONENTIATIONTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Potencia.h"

using namespace mpplas;

namespace com_uwyn_qtunit{
 
  class ExponentiationTest : public TestCase {

    public:
    ExponentiationTest();

    void setUp();
    void tearDown();

    protected:
    /* The actual tests */
    void testMontgomeryPrecomp();
    void testMontgomeryReduction();

    void testBarrettPrecomp();
    void testBarrettReduction();

    void testALaMersenneReduction();

    void testClassicMontgomeryInverse();

  };
}
#endif
