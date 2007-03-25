/*
 * $Id$
 */

#include <string>
#include "KernelTest.h"

using namespace std;
using namespace mpplas;
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
  one = (Cifra)1;
  two = (Cifra)2;
  three = (Cifra)3;
  zero = (Cifra)0;

  overflow = resto = 0;

  //Pre-defined constants:
  // mpplas::Constantes::CIFRA_MAX
  // mpplas::Constantes::CIFRASIGNO_MAX


}
void KernelTest::tearDown(){
//empty. new is not used
}

void KernelTest::testAdd(){
  qassertTrue( three == vCPUBasica::Add(one,two, overflow) );
  qassertTrue( zero == vCPUBasica::Add(Constantes::CIFRA_MAX, one, overflow) );
  qassertTrue( one == overflow );
}

void KernelTest::testAddx(){
  const Cifra CM = Constantes::CIFRA_MAX;
  qassertTrue( zero ==vCPUBasica::Addx(CM, one, overflow) );
  qassertTrue( one == vCPUBasica::Addx(zero,zero, overflow) );
  qassertTrue( CM-1 == vCPUBasica::Addx(CM,CM, overflow) );
  qassertTrue( one == overflow );

}

void KernelTest::testSub(){ 
  qassertTrue( one == vCPUBasica::Sub(three, two, overflow) );
  qassertTrue( zero == overflow );

  qassertTrue( zero == vCPUBasica::Sub(three, three, overflow) );
  qassertTrue( zero == overflow );

//  qassertTrue( (Cifra)(Constantes::CIFRASIGNO_MAX)+1 == vCPUBasica::Sub(Constantes::CIFRA_MAX, (Cifra)Constantes::CIFRASIGNO_MAX) );
//  qassertTrue( zero ==  overflow );

  qassertTrue( Constantes::CIFRA_MAX == vCPUBasica::Sub(zero, one, overflow) );
  qassertTrue( one == overflow );
}

void KernelTest::testSubx(){
  qassertTrue( one == vCPUBasica::Subx(three, two, overflow) );
  qassertTrue( zero == overflow);

  qassertTrue( zero == vCPUBasica::Subx(three, three, overflow) );
  qassertTrue( zero ==  overflow );
  
//  qassertTrue( (Cifra)(Constantes::CIFRASIGNO_MAX)+1 == vCPUBasica::Sub(Constantes::CIFRA_MAX, (Cifra)Constantes::CIFRASIGNO_MAX) );
//  qassertTrue( zero ==  overflow );

  qassertTrue( Constantes::CIFRA_MAX == vCPUBasica::Sub(zero, one, overflow) );
  qassertTrue( one ==  overflow );

  qassertTrue( zero == vCPUBasica::Subx(three, two, overflow) );
  qassertTrue( zero ==  overflow );

  qassertTrue( Constantes::CIFRA_MAX == vCPUBasica::Sub(zero, one, overflow) );
  qassertTrue( one ==  overflow );

  qassertTrue( Constantes::CIFRA_MAX == vCPUBasica::Subx(two, two, overflow) );
  qassertTrue( one ==  overflow );
}

void KernelTest::testMul(){
  qassertTrue( zero == vCPUBasica::Mul(one, zero, resto) );

  qassertTrue( one == vCPUBasica::Mul(Constantes::CIFRA_MAX, Constantes::CIFRA_MAX, resto) );
  qassertTrue( Constantes::CIFRA_MAX - 1 /* base -2 */ ==  resto );
}
void KernelTest::testAddmul(){
  vCPUBasica::Mul(Constantes::CIFRA_MAX, Constantes::CIFRA_MAX, resto);
  //  resto  == BASE-2
  qassertTrue( Constantes::CIFRA_MAX-1 == vCPUBasica::Addmul( zero, one, resto ) );

  resto = 0;

  qassertTrue( Constantes::CIFRA_MAX << 1  == vCPUBasica::Addmul( Constantes::CIFRA_MAX, two , resto) );
  qassertTrue( three == vCPUBasica::Addmul( one, two , resto) );
}

void KernelTest::testDiv(){
  //shouldn't try to divide by zero
  qassertTrue( three == vCPUBasica::Div(three, one, resto) );


  qassertTrue( zero == vCPUBasica::Div(one, two, resto) ); 
  qassertTrue( one ==  resto ); 
  
  qassertTrue( (Constantes::CIFRA_MAX/2) +1 == vCPUBasica::Div(zero, two, resto) ); 
  qassertTrue( zero ==  resto );
}

void KernelTest::testShiftl(){
  qassertTrue( two == vCPUBasica::Shiftl(one,1, resto) );
  Cifra tmp = one;
  tmp <<= Constantes::BITS_EN_CIFRA-1;
  qassertTrue( tmp == vCPUBasica::Shiftl(one, Constantes::BITS_EN_CIFRA-1, resto));

  qassertTrue( zero == vCPUBasica::Shiftl(two, Constantes::BITS_EN_CIFRA-1, resto));
  qassertTrue( (Cifra)1 ==  resto);
}

void KernelTest::testShiftlr(){
  qassertTrue( one == vCPUBasica::Shiftlr(three, 1, resto) );
  Cifra tmp = one;
  tmp <<= Constantes::BITS_EN_CIFRA-1;
  qassertTrue( tmp ==  resto);

  qassertTrue( one == vCPUBasica::Shiftlr(two, 1, resto) );
  qassertTrue( zero ==  resto);

}


void KernelTest::testBfffo(){
  qassertTrue( (Cifra)Constantes::BITS_EN_CIFRA-1 == vCPUBasica::Bfffo(one));
  qassertTrue( (Cifra)Constantes::BITS_EN_CIFRA-2 == vCPUBasica::Bfffo(two));
  //undefined for 0. Could be considered to be the number of bits of
  //the basic type, but that's not guaranted
}








