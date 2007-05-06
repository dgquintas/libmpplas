/*
 * $Id$
 */

#ifndef __KERNELGENERICTEST_H
#define __KERNELGENERICTEST_H

#include "qtunit/TestCase.h"
#include <string>
#include "Z.h"
#include "err.h"
#include "nucleo.h"

using namespace mpplas;
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

      void testMnob();

    private:
      Digit one;
      Digit two;
      Digit three;
      Digit zero;

      Digit overflow;
      Digit resto;

  };
}

#endif
