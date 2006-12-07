/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include "OpenMPTest.h"

using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( OpenMPTest );

void OpenMPTest::setUp(){
  this->uno = Z::convertir(1);
  this->dos = Z::convertir(2);
  this->cero= Z::convertir(0);
}
void OpenMPTest::tearDown(){
//empty. new is not used
}

void OpenMPTest::testEquality(){
  CPPUNIT_ASSERT( uno != cero );
  CPPUNIT_ASSERT( uno == uno );

  CPPUNIT_ASSERT( !(uno == cero) );
  CPPUNIT_ASSERT( !(uno != uno) );
}
