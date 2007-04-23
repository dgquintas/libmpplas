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
  one = (Digit)1;
  two = (Digit)2;
  three = (Digit)3;
  zero = (Digit)0;

  overflow = resto = 0;

  //Pre-defined constants:
  // mpplas::Constants::CIFRA_MAX
  // mpplas::Constants::CIFRASIGNO_MAX


}
void KernelTest::tearDown(){
//empty. new is not used
}

void KernelTest::testAdd(){
  qassertTrue( three == vCPUBasica::Add(one,two, overflow) );
  qassertTrue( zero == vCPUBasica::Add(Constants::CIFRA_MAX, one, overflow) );
  qassertTrue( one == overflow );
}

void KernelTest::testAddx(){
  const Digit CM = Constants::CIFRA_MAX;
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

//  qassertTrue( (Digit)(Constants::CIFRASIGNO_MAX)+1 == vCPUBasica::Sub(Constants::CIFRA_MAX, (Digit)Constants::CIFRASIGNO_MAX) );
//  qassertTrue( zero ==  overflow );

  qassertTrue( Constants::CIFRA_MAX == vCPUBasica::Sub(zero, one, overflow) );
  qassertTrue( one == overflow );
}

void KernelTest::testSubx(){
  qassertTrue( one == vCPUBasica::Subx(three, two, overflow) );
  qassertTrue( zero == overflow);

  qassertTrue( zero == vCPUBasica::Subx(three, three, overflow) );
  qassertTrue( zero ==  overflow );
  
//  qassertTrue( (Digit)(Constants::CIFRASIGNO_MAX)+1 == vCPUBasica::Sub(Constants::CIFRA_MAX, (Digit)Constants::CIFRASIGNO_MAX) );
//  qassertTrue( zero ==  overflow );

  qassertTrue( Constants::CIFRA_MAX == vCPUBasica::Sub(zero, one, overflow) );
  qassertTrue( one ==  overflow );

  qassertTrue( zero == vCPUBasica::Subx(three, two, overflow) );
  qassertTrue( zero ==  overflow );

  qassertTrue( Constants::CIFRA_MAX == vCPUBasica::Sub(zero, one, overflow) );
  qassertTrue( one ==  overflow );

  qassertTrue( Constants::CIFRA_MAX == vCPUBasica::Subx(two, two, overflow) );
  qassertTrue( one ==  overflow );
}

void KernelTest::testMul(){
  qassertTrue( zero == vCPUBasica::Mul(one, zero, resto) );

  qassertTrue( one == vCPUBasica::Mul(Constants::CIFRA_MAX, Constants::CIFRA_MAX, resto) );
  qassertTrue( Constants::CIFRA_MAX - 1 /* base -2 */ ==  resto );
}
void KernelTest::testAddmul(){
  vCPUBasica::Mul(Constants::CIFRA_MAX, Constants::CIFRA_MAX, resto);
  //  resto  == BASE-2
  qassertTrue( Constants::CIFRA_MAX-1 == vCPUBasica::Addmul( zero, one, resto ) );

  resto = 0;

  qassertTrue( Constants::CIFRA_MAX << 1  == vCPUBasica::Addmul( Constants::CIFRA_MAX, two , resto) );
  qassertTrue( three == vCPUBasica::Addmul( one, two , resto) );
}

void KernelTest::testDiv(){
  //shouldn't try to divide by zero
  qassertTrue( three == vCPUBasica::Div(three, one, resto) );


  qassertTrue( zero == vCPUBasica::Div(one, two, resto) ); 
  qassertTrue( one ==  resto ); 
  
  qassertTrue( (Constants::CIFRA_MAX/2) +1 == vCPUBasica::Div(zero, two, resto) ); 
  qassertTrue( zero ==  resto );
}

void KernelTest::testShiftl(){
  qassertTrue( two == vCPUBasica::Shiftl(one,1, resto) );
  Digit tmp = one;
  tmp <<= Constants::BITS_EN_CIFRA-1;
  qassertTrue( tmp == vCPUBasica::Shiftl(one, Constants::BITS_EN_CIFRA-1, resto));

  qassertTrue( zero == vCPUBasica::Shiftl(two, Constants::BITS_EN_CIFRA-1, resto));
  qassertTrue( (Digit)1 ==  resto);
}

void KernelTest::testShiftlr(){
  qassertTrue( one == vCPUBasica::Shiftlr(three, 1, resto) );
  Digit tmp = one;
  tmp <<= Constants::BITS_EN_CIFRA-1;
  qassertTrue( tmp ==  resto);

  qassertTrue( one == vCPUBasica::Shiftlr(two, 1, resto) );
  qassertTrue( zero ==  resto);

}


void KernelTest::testBfffo(){
  qassertTrue( (Digit)1 == vCPUBasica::Bfffo(one));
  qassertTrue( (Digit)2 == vCPUBasica::Bfffo(two));
  qassertTrue( (Digit)1 == vCPUBasica::Bfffo(zero));
  qassertTrue( (Digit)1 == vCPUBasica::Bfffo(zero));
  qassertTrue( (Digit)25== vCPUBasica::Bfffo((Digit)32490673));
  qassertTrue( (Digit)Constants::BITS_EN_CIFRA == vCPUBasica::Bfffo(Constants::CIFRA_MAX));

  //undefined for 0. Could be considered to be the number of bits of
  //the basic type, but that's not guaranted
}








