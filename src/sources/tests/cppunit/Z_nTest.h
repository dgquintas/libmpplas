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
    CPPUNIT_TEST( testAdditionWithZn );
    CPPUNIT_TEST( testAdditionWithCifra );
    CPPUNIT_TEST( testAdditionWithCifraSigno );
    
    CPPUNIT_TEST( testSubstractionWithZ );
    CPPUNIT_TEST( testSubstractionWithZn );
    CPPUNIT_TEST( testSubstractionWithCifra );
    CPPUNIT_TEST( testSubstractionWithCifraSigno );
    
    CPPUNIT_TEST( testProductWithZ);
    CPPUNIT_TEST( testProductWithZn);
    CPPUNIT_TEST( testProductWithCifra);
    CPPUNIT_TEST( testProductWithCifraSigno);
    
    CPPUNIT_TEST( testDivisionWithZ);
    CPPUNIT_TEST_EXCEPTION( testDivisionWithZThrows, Errores::ElementoNoInvertible );
    CPPUNIT_TEST( testDivisionWithZn);
    CPPUNIT_TEST( testDivisionWithCifra);
    CPPUNIT_TEST( testDivisionWithCifraSigno);
    
    CPPUNIT_TEST( testExponentiationWithZ);
    CPPUNIT_TEST( testExponentiationWithZn);
    CPPUNIT_TEST( testExponentiationWithCifra);
    CPPUNIT_TEST( testExponentiationWithCifraSigno);

  CPPUNIT_TEST_SUITE_END();
  
  public:
    Z_nTest();
    void setUp();
    void tearDown();
    
    /* The actual tests */
    void testAdditionWithZ();
    void testAdditionWithZn();
    void testAdditionWithCifra();
    void testAdditionWithCifraSigno();
    
    void testSubstractionWithZ();
    void testSubstractionWithZn();
    void testSubstractionWithCifra();
    void testSubstractionWithCifraSigno();
    
    void testProductWithZ();
    void testProductWithZn();
    void testProductWithCifra();
    void testProductWithCifraSigno();
    
    void testDivisionWithZ();
    void testDivisionWithZThrows();
    void testDivisionWithZn();
    void testDivisionWithCifra();
    void testDivisionWithCifraSigno();
    
    void testExponentiationWithZ();
    void testExponentiationWithZn();
    void testExponentiationWithCifra();
    void testExponentiationWithCifraSigno();
    
  private:
    Z integer;
    Z_n *modularInteger;
    Z modulus;
    Z primeModulus;
    Cifra cifra;
    CifraSigno cifraSigno;

    std::ostringstream oss;

    Funciones funcs;
};

#endif /*Z_NTEST_H_*/
