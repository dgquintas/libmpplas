/*
 * $Id$
 */

#ifndef __TEMPLATE_H
#define __TEMPLATE_H

#include "qtunit/TestCase.h"
#include <string>


using namespace numth;

class Test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( Test );
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
