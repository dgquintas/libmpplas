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

class ZTest : public CppUnit::TestFixture {


  CPPUNIT_TEST_SUITE( ZTest );
    CPPUNIT_TEST( testEquality );
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST( testSubstraction );
    CPPUNIT_TEST( testMultiplication );
    CPPUNIT_TEST( testDivision );
    CPPUNIT_TEST( testExponentiation);
    CPPUNIT_TEST( testSquare );
    CPPUNIT_TEST_EXCEPTION( testDivideByZeroThrows, Errores::DivisionPorCero); 
    CPPUNIT_TEST_EXCEPTION( testModulusByZeroThrows, Errores::DivisionPorCero); 

    CPPUNIT_TEST( testFactorial );
  CPPUNIT_TEST_SUITE_END();
  
  public:

    ZTest();

    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testEquality();
    void testAddition();
    void testSubstraction();
    void testMultiplication();
    void testDivision();
    void testModulus();
    void testExponentiation();
    void testSquare();
    void testDivideByZeroThrows();
    void testModulusByZeroThrows();

    void testFactorial();
  private:
    Z uno, dos, cero;
    Z z1, z2;

    Funciones funcs;
};

#endif
