/*
 * $Id$
 */

#ifndef __REDUCTIONTEST_H
#define __REDUCTIONTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Functions.h"
#include "RedModular.h"
#include "Random.h"
#include "Primos.h"

using namespace mpplas;

namespace com_uwyn_qtunit{

  class ReductionTest : public TestCase {

    public:
      ReductionTest();

      void setUp();
      void tearDown();

    protected:
      /* The actual tests */
      void testMontgomeryPrecomp();
      void testMontgomeryReduction();

      void testBarrettPrecomp();
      void testBarrettReduction();

      void testALaMersenneReduction();

    private:
      RedMontgomery _redMont;
      RedBarrett _redBarret;
      RedModularALaMersenne _redMersenne;
    
      Functions* const _funcs;
      RandomFast *_rnd;
      GenPrimos *_primeGen;

      Z _integer;

  };
}
#endif
