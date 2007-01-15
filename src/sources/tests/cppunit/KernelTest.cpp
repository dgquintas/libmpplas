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
  const Cifra CM = Constantes::CIFRA_MAX;
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Addx(CM, one) );
  CPPUNIT_ASSERT_EQUAL( one,  cpu_.Addx(zero,zero) );
  CPPUNIT_ASSERT_EQUAL( CM-1, cpu_.Addx(CM,CM) );
  CPPUNIT_ASSERT_EQUAL( one, cpu_.getOverflow() );

}

void KernelTest::testSub(){
  CPPUNIT_ASSERT_EQUAL( one, cpu_.Sub(three, two) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getOverflow() );

  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Sub(three, three) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getOverflow() );

  CPPUNIT_ASSERT_EQUAL( (Cifra)(Constantes::CIFRASIGNO_MAX)+1, cpu_.Sub(Constantes::CIFRA_MAX, (Cifra)Constantes::CIFRASIGNO_MAX) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getOverflow() );

  CPPUNIT_ASSERT_EQUAL( Constantes::CIFRA_MAX, cpu_.Sub(zero, one) );
  CPPUNIT_ASSERT_EQUAL( one, cpu_.getOverflow() );
}

void KernelTest::testSubx(){
  CPPUNIT_ASSERT_EQUAL( one, cpu_.Subx(three, two) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getOverflow() );

  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Subx(three, three) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getOverflow() );
  
  CPPUNIT_ASSERT_EQUAL( (Cifra)(Constantes::CIFRASIGNO_MAX)+1, cpu_.Sub(Constantes::CIFRA_MAX, (Cifra)Constantes::CIFRASIGNO_MAX) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getOverflow() );

  CPPUNIT_ASSERT_EQUAL( Constantes::CIFRA_MAX, cpu_.Sub(zero, one) );
  CPPUNIT_ASSERT_EQUAL( one, cpu_.getOverflow() );

  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Subx(three, two) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getOverflow() );

  CPPUNIT_ASSERT_EQUAL( Constantes::CIFRA_MAX, cpu_.Sub(zero, one) );
  CPPUNIT_ASSERT_EQUAL( one, cpu_.getOverflow() );

  CPPUNIT_ASSERT_EQUAL( Constantes::CIFRA_MAX, cpu_.Subx(two, two) );
  CPPUNIT_ASSERT_EQUAL( one, cpu_.getOverflow() );
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
  //shouldn't try to divide by zero
  CPPUNIT_ASSERT_EQUAL( three, cpu_.Div(three, one) );


  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Div(one, two) ); 
  CPPUNIT_ASSERT_EQUAL( one, cpu_.getResto() ); 
  
  CPPUNIT_ASSERT_EQUAL( (Constantes::CIFRA_MAX/2) +1, cpu_.Div(zero, two) ); 
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getResto() );
}

void KernelTest::testShiftl(){
  CPPUNIT_ASSERT_EQUAL( two, cpu_.Shiftl(one,1) );
  Cifra tmp = one;
  tmp <<= Constantes::BITS_EN_CIFRA-1;
  CPPUNIT_ASSERT_EQUAL( tmp, cpu_.Shiftl(one, Constantes::BITS_EN_CIFRA-1));

  CPPUNIT_ASSERT_EQUAL( zero, cpu_.Shiftl(two, Constantes::BITS_EN_CIFRA-1));
  CPPUNIT_ASSERT_EQUAL( (Cifra)1, cpu_.getResto());
}

void KernelTest::testShiftlr(){
  CPPUNIT_ASSERT_EQUAL( one, cpu_.Shiftlr(three, 1) );
  Cifra tmp = one;
  tmp <<= Constantes::BITS_EN_CIFRA-1;
  CPPUNIT_ASSERT_EQUAL( tmp, cpu_.getResto());

  CPPUNIT_ASSERT_EQUAL( one, cpu_.Shiftlr(two, 1) );
  CPPUNIT_ASSERT_EQUAL( zero, cpu_.getResto());

}


void KernelTest::testBfffo(){
  CPPUNIT_ASSERT_EQUAL( (Cifra)Constantes::BITS_EN_CIFRA-1, cpu_.Bfffo(one));
  CPPUNIT_ASSERT_EQUAL( (Cifra)Constantes::BITS_EN_CIFRA-2, cpu_.Bfffo(two));
  //undefined for 0. Could be considered to be the number of bits of
  //the basic type, but that's not guaranted
}








