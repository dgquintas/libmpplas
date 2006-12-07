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

using namespace numth;

class OpenMPTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( OpenMPTest );
    CPPUNIT_TEST( testEquality );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testEquality();
  private:
    Z uno, dos, cero;
};

#endif
