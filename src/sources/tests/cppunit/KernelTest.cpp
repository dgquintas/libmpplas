/*
 * $Id$
 */

#include <cppunit/TestCase.h>
#include <string>
#include "KernelTest.h"

using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( KernelTest );

void KernelTest::setUp(){
  one = (Cifra)1;
  two = (Cifra)2;
  zero = (Cifra)0;

  //Pre-defined constants:
  // numth::Constantes::CIFRA_MAX
  // numth::Constantes::CIFRASIGNO_MAX

  
}
void KernelTest::tearDown(){
//empty. new is not used
}

void KernelTest::testAdd(){
  CPPUNIT_ASSERT( two == cpu_.Add(one,one) );
  CPPUNIT_ASSERT( zero == cpu_.Add(Constantes::CIFRA_MAX, one) );
}
