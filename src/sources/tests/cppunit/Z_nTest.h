#ifndef Z_NTEST_H_
#define Z_NTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "Z.h"
#include "Z_n.h"
#include "Funciones.h"
#include <sstream>



using namespace numth;

class Z_nTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( Z_nTest );
    CPPUNIT_TEST( testAdditionWithZ );
    CPPUNIT_TEST( testAdditionWithCifra );
    CPPUNIT_TEST( testAdditionWithCifraSigno );
    
    CPPUNIT_TEST( testSubstractionWithZ );
    CPPUNIT_TEST( testSubstractionWithCifra );
    CPPUNIT_TEST( testSubstractionWithCifraSigno );
    
    CPPUNIT_TEST( testProductWithZ);
    CPPUNIT_TEST( testProductWithCifra);
    CPPUNIT_TEST( testProductWithCifraSigno);
    
    CPPUNIT_TEST( testDivisionWithZ);
    CPPUNIT_TEST_EXCEPTION( testDivisionWithZThrows, Errores::ElementoNoInvertible );
    CPPUNIT_TEST( testDivisionWithCifra);
    CPPUNIT_TEST_EXCEPTION( testDivisionWithCifraThrows, Errores::ElementoNoInvertible);
    CPPUNIT_TEST( testDivisionWithCifraSigno);
    CPPUNIT_TEST_EXCEPTION( testDivisionWithCifraSignoThrows, Errores::ElementoNoInvertible);
    
    CPPUNIT_TEST( testExponentiationWithZ);
    CPPUNIT_TEST( testExponentiationWithCifra);
    CPPUNIT_TEST_EXCEPTION( testExponentiationWithCifraSignoThrows, Errores::ElementoNoInvertible );
    CPPUNIT_TEST( testExponentiationWithCifraSigno );

  CPPUNIT_TEST_SUITE_END();
  
  public:
    Z_nTest();
    ~Z_nTest();
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testAdditionWithZ();
    void testAdditionWithCifra();
    void testAdditionWithCifraSigno();
    
    void testSubstractionWithZ();
    void testSubstractionWithCifra();
    void testSubstractionWithCifraSigno();
    
    void testProductWithZ();
    void testProductWithCifra();
    void testProductWithCifraSigno();
    
    void testDivisionWithZ();
    void testDivisionWithZThrows();
    void testDivisionWithCifra();
    void testDivisionWithCifraThrows();
    void testDivisionWithCifraSigno();
    void testDivisionWithCifraSignoThrows();
    
    void testExponentiationWithZ();
    void testExponentiationWithCifra();
    void testExponentiationWithCifraSigno();
    void testExponentiationWithCifraSignoThrows();
    
  private:
    Z integer;
    Z_n *modularInteger;
    Z modulus;
    Z primeModulus;
    Cifra cifra;
    CifraSigno cifraSigno;

    Funciones funcs;
};

#endif /*Z_NTEST_H_*/
