/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include "template.h"

using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( Test );

void Test::setUp(){
  this->foo = Z::convertir(1);
  this->bar= Z::convertir(0);
}
void Test::tearDown(){
//empty. new is not used
}

void Test::testEquality(){
  CPPUNIT_ASSERT( foo != bar );

}