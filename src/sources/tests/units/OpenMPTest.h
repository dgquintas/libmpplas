/*
 * $Id$
 */

#ifndef __ZTEST_H
#define __ZTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "Z.h"
#include "err.h"
#include "Funciones.h"

using namespace numth;

class OpenMPTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( OpenMPTest );
    CPPUNIT_TEST( testParallelFor );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testParallelFor();
  private:
    Z *integers, *integersPAR, *integersSEQ;
    Z factor;
    Funciones funcs;

    static const int NUM_THREADS = 10;
};

#endif
