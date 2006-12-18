/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include <sstream>
#include "Z_nTest.h"
#include <pari/pari.h>


using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( Z_nTest );

Z_nTest::Z_nTest(){
  pari_init(1000000, 0);
}

void Z_nTest::setUp(){
  
  this->integer = funcs.randomRapido()->leerBits(2000);
  this->modulus = funcs.randomRapido()->leerBits(500);
  this->modularInteger = new Z_n(funcs.randomRapido()->leerBits(1234), modulus);
  this->cifra = funcs.randomRapido()->leerCifra();
  this->cifraSigno = (funcs.randomRapido()->leerCifra() >> 1)*(-1); //force a negative number
  
}
void Z_nTest::tearDown(){
  delete this->modularInteger;
}


void Z_nTest::testAdditionWithZ(){
  Z_n res = (*modularInteger) + integer; 
  
  string tmp;
  tmp += '(';
    tmp += modularInteger->toString();
    tmp += " + ";
    tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testAdditionWithZn(){}
void Z_nTest::testAdditionWithCifra(){}
void Z_nTest::testAdditionWithCifraSigno(){}

void Z_nTest::testSubstractionWithZ(){
  Z_n res = (*modularInteger) - integer ; 
  
  string tmp;
  tmp += '(';
    tmp += modularInteger->toString();
    tmp += " - ";
    tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testSubstractionWithZn(){}
void Z_nTest::testSubstractionWithCifra(){}
void Z_nTest::testSubstractionWithCifraSigno(){}

void Z_nTest::testProductWithZ(){
  Z_n res = (*modularInteger) * integer ; 
  
  string tmp;
  tmp += '(';
    tmp += modularInteger->toString();
    tmp += " * ";
    tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testProductWithZn(){}
void Z_nTest::testProductWithCifra(){}
void Z_nTest::testProductWithCifraSigno(){}

void Z_nTest::testDivisionWithZ(){
  this->modulus = funcs.genPrimos()->leerPrimoProb(128);  //make sure the modulus is prime (ie, invertible)
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(funcs.randomRapido()->leerBits(1234), modulus);
  Z_n res = (*modularInteger) / integer ; 
  
  string tmp;
  tmp += '(';
    tmp += modularInteger->toString();
    tmp += " / ";
    tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testDivisionWithZThrows(){
  this->modulus = funcs.randomRapido()->leerBits(500)*integer;  //make sure the modulus isn't 
                                                                //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(funcs.randomRapido()->leerBits(1234), modulus);

  Z_n res = (*modularInteger) / integer ; 

  //this point shouldn't be reached FIXME: remove this
  std::cout << "modular Integer = " << this->modularInteger->toString() << std::endl;
  std::cout << "modulus = " << this->modulus.toString() << std::endl;
  std::cout << "exponent = " << this->integer.toString() << std::endl;
  std::cout << "res = "      << res.toString() << std::endl;
}
void Z_nTest::testDivisionWithZn(){}
void Z_nTest::testDivisionWithCifra(){}
void Z_nTest::testDivisionWithCifraSigno(){}

void Z_nTest::testExponentiationWithZ(){
   Z_n res = (*modularInteger) ^ integer ; 
  
  GEN x,y,m;

  x = gp_read_str(const_cast<char*>(modularInteger->toString().c_str()));
  y = gp_read_str(const_cast<char*>(integer.toString().c_str()) );
  m = gp_read_str(const_cast<char*>(modulus.toString().c_str()));

  GEN pariRes = Fp_pow(x,y,m);

  string pariStr(GENtostr( pariRes ));
  string thisStr = res.toString();

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}

void Z_nTest::testExponentiationWithZn(){}
void Z_nTest::testExponentiationWithCifra(){
  Z_n res = (*modularInteger) ^ cifra ;

  ostringstream oss;
  oss << cifra;
  string cifraStr = oss.str();

  GEN x,y,m;

  x = gp_read_str(const_cast<char*>(modularInteger->toString().c_str()));
  y = gp_read_str(const_cast<char*>(cifraStr.c_str()));
  m = gp_read_str(const_cast<char*>(modulus.toString().c_str()));

  GEN pariRes = Fp_pow(x,y,m);

  string pariStr(GENtostr( pariRes ));
  string thisStr = res.toString();

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testExponentiationWithCifraSigno(){
  Z_n res = (*modularInteger) ^ cifraSigno ;

  ostringstream oss;
  oss << cifraSigno;
  string cifraStr = oss.str();

  GEN x,y,m;

  x = gp_read_str(const_cast<char*>(modularInteger->toString().c_str()));
  y = gp_read_str(const_cast<char*>(cifraStr.c_str()));
  m = gp_read_str(const_cast<char*>(modulus.toString().c_str()));

  GEN pariRes = Fp_pow(x,y,m);

  string pariStr(GENtostr( pariRes ));
  string thisStr = res.toString();

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}

