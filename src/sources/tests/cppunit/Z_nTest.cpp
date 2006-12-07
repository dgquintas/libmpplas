/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include "Z_nTest.h"


using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( Z_NTest );

void Test::setUp(){
  
  this->integer = Z::convertir("171122452428141311372468338881272839092270544893520369393648040923257279754140647424000000000000000");
  this->modulus = Z::convertir(
  this->bar= Z::convertir(0);
}
void Test::tearDown(){
//empty. new is not used
}

void Test::testEquality(){

}
