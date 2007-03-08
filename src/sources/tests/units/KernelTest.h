/*
 * $Id $
 */

#ifndef __KERNELGENERICTEST_H
#define __KERNELGENERICTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Z.h"
#include "err.h"
#include "nucleo.h"

using namespace numth;
namespace com_uwyn_qtunit{

  class KernelTest: public TestCase {


    public:
      KernelTest();
      void setUp();
      void tearDown();
    protected:
      /* The actual tests */
      void testAdd();
      void testAddx();

      void testSub();
      void testSubx();

      void testMul();
      void testAddmul();

      void testDiv();

      void testShiftl();
      void testShiftlr();

      void testBfffo();

    private:
      Cifra one;
      Cifra two;
      Cifra three;
      Cifra zero;

      Cifra overflow;
      Cifra resto;

  };
}

#endif
