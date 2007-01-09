/*
 * $Id$
 */

#ifndef __RANDOMTEST_H
#define __RANDOMTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "Random.h"

using namespace numth;

class RandomTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( RandomTest );
    CPPUNIT_TEST( testRC4 );
    CPPUNIT_TEST( testCongruent );
    CPPUNIT_TEST( testBBS );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testRC4();
    void testCongruent();
    void testBBS();

  private:
    FIPS_140_1 fips;
};

#endif
