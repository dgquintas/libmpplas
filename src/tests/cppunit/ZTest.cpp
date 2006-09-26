#include <cppunit/TestCase.h>
#include <string>
#include "ZTest.h"

using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( ZTest );

void ZTest::setUp(){
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
