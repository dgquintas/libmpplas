/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include "FunctionsTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( FunctionsTest );

void FunctionsTest::setUp(){
  this->foo = Z::convertir(1);
  this->bar= Z::convertir(0);
}
void FunctionsTest::tearDown(){
//empty. new is not used
}

void FunctionsTest::test(){

}
