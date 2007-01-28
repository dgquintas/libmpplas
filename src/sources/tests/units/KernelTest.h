/*
 * $Id $
 */

#ifndef __KERNELGENERICTEST_H
#define __KERNELGENERICTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "Z.h"
#include "err.h"
#include "nucleo.h"

using namespace numth;

class KernelTest: public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( KernelTest );
    CPPUNIT_TEST( testAdd );
    CPPUNIT_TEST( testAddx );
    CPPUNIT_TEST( testSub );
    CPPUNIT_TEST( testSubx );
    CPPUNIT_TEST( testMul );
    CPPUNIT_TEST( testAddmul );
    CPPUNIT_TEST( testDiv );
    CPPUNIT_TEST( testShiftl );
    CPPUNIT_TEST( testShiftlr );
    CPPUNIT_TEST( testBfffo );
  CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

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
    vCPUBasica<Arch::ARCH> cpu_;

    Cifra one;
    Cifra two;
    Cifra three;
    Cifra zero;

};

#endif
