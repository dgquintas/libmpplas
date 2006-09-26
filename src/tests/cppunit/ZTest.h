#ifndef __ZTEST_H
#define __ZTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "Z.h"
#include "err.h"

using namespace numth;

class ZTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( ZTest );
    CPPUNIT_TEST( testEquality );
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST( testSubstraction );
    CPPUNIT_TEST_EXCEPTION( testDivideByZeroThrows, Errores::DivisionPorCero); 
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testEquality();
    void testAddition();
    void testSubstraction();
    void testDivideByZeroThrows();
  private:
    Z uno, dos, cero;
};

#endif
