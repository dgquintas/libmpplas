/*
 * $Id$
 */

#include <cppunit/TestCase.h>
#include <string>
#include "ZTest.h"
#include <pari/pari.h>
#include "aux.h" 


using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( ZTest );

ZTest::ZTest(){
  pari_init(1000000, 0);
}

void ZTest::setUp(){
  z1 = funcs.getRandomRapido()->leerBits(brand(2000,5000));
  z2 = funcs.getRandomRapido()->leerBits(brand(2000,5000));

  this->uno = Z::convertir(1);
  this->dos = Z::convertir(2);
  this->cero= Z::convertir(0);

  
}
void ZTest::tearDown(){
//empty. new is not used
}

void ZTest::testEquality(){
  CPPUNIT_ASSERT( uno != cero );
  CPPUNIT_ASSERT( uno == uno );

  CPPUNIT_ASSERT( !(uno == cero) );
  CPPUNIT_ASSERT( !(uno != uno) );
}
void ZTest::testAddition(){
  CPPUNIT_ASSERT( uno + uno == dos );
  CPPUNIT_ASSERT( uno + cero == uno );
  CPPUNIT_ASSERT( cero + cero == cero );
}
void ZTest::testSubstraction(){
  CPPUNIT_ASSERT( dos - uno == uno );
  CPPUNIT_ASSERT( cero - uno == -uno );
  CPPUNIT_ASSERT( cero - cero == cero );
};
void ZTest::testDivideByZeroThrows(){
  uno / cero;
}

void ZTest::testFactorial(){
  Cifra rnd = (funcs.getRandomRapido()->leerCifra()) % (1UL<<10);

  Z res = Z::convertir(rnd);

  string tmp;
  tmp += res.toString();
  tmp += "!";

  res.factorial();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();


  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
  
}
