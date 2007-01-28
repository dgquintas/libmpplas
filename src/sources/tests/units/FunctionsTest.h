/*
 * $Id$
 */

#ifndef __FUNCTIONSTEST_H
#define __FUNCTIONSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "Z.h"

using namespace std;
using namespace numth;


class FunctionsTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( FunctionsTest );
    CPPUNIT_TEST( test );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void test();
  private:
    Z foo, bar;
};

#endif
