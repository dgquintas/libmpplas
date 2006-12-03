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
  cpu_.reset();
  one = (Cifra)1;
  two = (Cifra)2;
  three = (Cifra)3;
  zero = (Cifra)0;

  //Pre-defined constants:
  // numth::Constantes::CIFRA_MAX
  // numth::Constantes::CIFRASIGNO_MAX


}
void KernelTest::tearDown(){
//empty. new is not used
}

void KernelTest::testAdd(){
  CPPUNIT_ASSERT_EQUAL( three, cpu_.Add(one,two) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Add(Constantes::CIFRA_MAX, one) );
  CPPUNIT_ASSERT_EQUAL( one, cpu_.getOverflow() );
}

void KernelTest::testAddx(){
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Addx(Constantes::CIFRA_MAX, one) );
  CPPUNIT_ASSERT_EQUAL( one,  cpu_.Addx(zero,zero) );
}

void KernelTest::testSub(){

}

void KernelTest::testSubx(){

}

void KernelTest::testMul(){
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Mul(one, zero) );

  CPPUNIT_ASSERT_EQUAL( one, cpu_.Mul(Constantes::CIFRA_MAX, Constantes::CIFRA_MAX) );
  CPPUNIT_ASSERT_EQUAL( Constantes::CIFRA_MAX - 1 /* base -2 */, cpu_.getResto() );
}
void KernelTest::testAddmul(){
  cpu_.Mul(Constantes::CIFRA_MAX, Constantes::CIFRA_MAX);
  // cpu_.getResto()  == BASE-2
  CPPUNIT_ASSERT_EQUAL( Constantes::CIFRA_MAX-1, cpu_.Addmul( zero, one ) );

  cpu_.reset();

  CPPUNIT_ASSERT_EQUAL( Constantes::CIFRA_MAX << 1 , cpu_.Addmul( Constantes::CIFRA_MAX, two ) );
  CPPUNIT_ASSERT_EQUAL( three , cpu_.Addmul( one, two ) );
}

void KernelTest::testDiv(){


}





