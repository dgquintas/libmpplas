/*
 * $Id$
 */

#include <string>
#include "KernelTest.h"

using namespace std;
using namespace numth;
using namespace com_uwyn_qtunit;


KernelTest::KernelTest(){
    addTest(KernelTest, testAdd );
    addTest(KernelTest, testAddx );
    addTest(KernelTest, testSub );
    addTest(KernelTest, testSubx );
    addTest(KernelTest, testMul );
    addTest(KernelTest, testAddmul );
    addTest(KernelTest, testDiv );
    addTest(KernelTest, testShiftl );
    addTest(KernelTest, testShiftlr );
    addTest(KernelTest, testBfffo );

}

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
  qassertTrue( three == cpu_.Add(one,two) );
  qassertTrue( zero == cpu_.Add(Constantes::CIFRA_MAX, one) );
  qassertTrue( one == cpu_.getOverflow() );
}

void KernelTest::testAddx(){
  const Cifra CM = Constantes::CIFRA_MAX;
  qassertTrue( zero ==cpu_.Addx(CM, one) );
  qassertTrue( one == cpu_.Addx(zero,zero) );
  qassertTrue( CM-1 == cpu_.Addx(CM,CM) );
  qassertTrue( one == cpu_.getOverflow() );

}

void KernelTest::testSub(){ 
  qassertTrue( one == cpu_.Sub(three, two) );
  qassertTrue( zero == cpu_.getOverflow() );

  qassertTrue( zero == cpu_.Sub(three, three) );
  qassertTrue( zero == cpu_.getOverflow() );

  qassertTrue( (Cifra)(Constantes::CIFRASIGNO_MAX)+1 == cpu_.Sub(Constantes::CIFRA_MAX, (Cifra)Constantes::CIFRASIGNO_MAX) );
  qassertTrue( zero == cpu_.getOverflow() );

  qassertTrue( Constantes::CIFRA_MAX == cpu_.Sub(zero, one) );
  qassertTrue( one == cpu_.getOverflow() );
}

void KernelTest::testSubx(){
  qassertTrue( one == cpu_.Subx(three, two) );
  qassertTrue( zero == cpu_.getOverflow() );

  qassertTrue( zero == cpu_.Subx(three, three) );
  qassertTrue( zero == cpu_.getOverflow() );
  
  qassertTrue( (Cifra)(Constantes::CIFRASIGNO_MAX)+1 == cpu_.Sub(Constantes::CIFRA_MAX, (Cifra)Constantes::CIFRASIGNO_MAX) );
  qassertTrue( zero == cpu_.getOverflow() );

  qassertTrue( Constantes::CIFRA_MAX == cpu_.Sub(zero, one) );
  qassertTrue( one == cpu_.getOverflow() );

  qassertTrue( zero == cpu_.Subx(three, two) );
  qassertTrue( zero == cpu_.getOverflow() );

  qassertTrue( Constantes::CIFRA_MAX == cpu_.Sub(zero, one) );
  qassertTrue( one == cpu_.getOverflow() );

  qassertTrue( Constantes::CIFRA_MAX == cpu_.Subx(two, two) );
  qassertTrue( one == cpu_.getOverflow() );
}

void KernelTest::testMul(){
  qassertTrue( zero == cpu_.Mul(one, zero) );

  qassertTrue( one == cpu_.Mul(Constantes::CIFRA_MAX, Constantes::CIFRA_MAX) );
  qassertTrue( Constantes::CIFRA_MAX - 1 /* base -2 */ == cpu_.getResto() );
}
void KernelTest::testAddmul(){
  cpu_.Mul(Constantes::CIFRA_MAX, Constantes::CIFRA_MAX);
  // cpu_.getResto()  == BASE-2
  qassertTrue( Constantes::CIFRA_MAX-1 == cpu_.Addmul( zero, one ) );

  cpu_.reset();

  qassertTrue( Constantes::CIFRA_MAX << 1  == cpu_.Addmul( Constantes::CIFRA_MAX, two ) );
  qassertTrue( three == cpu_.Addmul( one, two ) );
}

void KernelTest::testDiv(){
  //shouldn't try to divide by zero
  qassertTrue( three == cpu_.Div(three, one) );


  qassertTrue( zero == cpu_.Div(one, two) ); 
  qassertTrue( one == cpu_.getResto() ); 
  
  qassertTrue( (Constantes::CIFRA_MAX/2) +1 == cpu_.Div(zero, two) ); 
  qassertTrue( zero == cpu_.getResto() );
}

void KernelTest::testShiftl(){
  qassertTrue( two == cpu_.Shiftl(one,1) );
  Cifra tmp = one;
  tmp <<= Constantes::BITS_EN_CIFRA-1;
  qassertTrue( tmp == cpu_.Shiftl(one, Constantes::BITS_EN_CIFRA-1));

  qassertTrue( zero == cpu_.Shiftl(two, Constantes::BITS_EN_CIFRA-1));
  qassertTrue( (Cifra)1 == cpu_.getResto());
}

void KernelTest::testShiftlr(){
  qassertTrue( one == cpu_.Shiftlr(three, 1) );
  Cifra tmp = one;
  tmp <<= Constantes::BITS_EN_CIFRA-1;
  qassertTrue( tmp == cpu_.getResto());

  qassertTrue( one == cpu_.Shiftlr(two, 1) );
  qassertTrue( zero == cpu_.getResto());

}


void KernelTest::testBfffo(){
  qassertTrue( (Cifra)Constantes::BITS_EN_CIFRA-1 == cpu_.Bfffo(one));
  qassertTrue( (Cifra)Constantes::BITS_EN_CIFRA-2 == cpu_.Bfffo(two));
  //undefined for 0. Could be considered to be the number of bits of
  //the basic type, but that's not guaranted
}








