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
    addTest(KernelTest, testMnob );

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
  qassertTrue( three == BasicCPU::Add(one,two, overflow) );
  qassertTrue( zero == BasicCPU::Add(Constants::CIFRA_MAX, one, overflow) );
  qassertTrue( one == overflow );
}

void KernelTest::testAddx(){
  const Digit CM = Constants::CIFRA_MAX;
  qassertTrue( zero ==BasicCPU::Addx(CM, one, overflow) );
  qassertTrue( one == BasicCPU::Addx(zero,zero, overflow) );
  qassertTrue( CM-1 == BasicCPU::Addx(CM,CM, overflow) );
  qassertTrue( one == overflow );

}

void KernelTest::testSub(){ 
  qassertTrue( one == BasicCPU::Sub(three, two, overflow) );
  qassertTrue( zero == overflow );

  qassertTrue( zero == BasicCPU::Sub(three, three, overflow) );
  qassertTrue( zero == overflow );

//  qassertTrue( (Digit)(Constants::CIFRASIGNO_MAX)+1 == BasicCPU::Sub(Constants::CIFRA_MAX, (Digit)Constants::CIFRASIGNO_MAX) );
//  qassertTrue( zero ==  overflow );

  qassertTrue( Constants::CIFRA_MAX == BasicCPU::Sub(zero, one, overflow) );
  qassertTrue( one == overflow );
}

void KernelTest::testSubx(){
  qassertTrue( one == BasicCPU::Subx(three, two, overflow) );
  qassertTrue( zero == overflow);

  qassertTrue( zero == BasicCPU::Subx(three, three, overflow) );
  qassertTrue( zero ==  overflow );
  
//  qassertTrue( (Digit)(Constants::CIFRASIGNO_MAX)+1 == BasicCPU::Sub(Constants::CIFRA_MAX, (Digit)Constants::CIFRASIGNO_MAX) );
//  qassertTrue( zero ==  overflow );

  qassertTrue( Constants::CIFRA_MAX == BasicCPU::Sub(zero, one, overflow) );
  qassertTrue( one ==  overflow );

  qassertTrue( zero == BasicCPU::Subx(three, two, overflow) );
  qassertTrue( zero ==  overflow );

  qassertTrue( Constants::CIFRA_MAX == BasicCPU::Sub(zero, one, overflow) );
  qassertTrue( one ==  overflow );

  qassertTrue( Constants::CIFRA_MAX == BasicCPU::Subx(two, two, overflow) );
  qassertTrue( one ==  overflow );
}

void KernelTest::testMul(){
  qassertTrue( zero == BasicCPU::Mul(one, zero, resto) );

  qassertTrue( one == BasicCPU::Mul(Constants::CIFRA_MAX, Constants::CIFRA_MAX, resto) );
  qassertTrue( Constants::CIFRA_MAX - 1 /* base -2 */ ==  resto );
}
void KernelTest::testAddmul(){
  BasicCPU::Mul(Constants::CIFRA_MAX, Constants::CIFRA_MAX, resto);
  //  resto  == BASE-2
  qassertTrue( Constants::CIFRA_MAX-1 == BasicCPU::Addmul( zero, one, resto ) );

  resto = 0;

  qassertTrue( Constants::CIFRA_MAX << 1  == BasicCPU::Addmul( Constants::CIFRA_MAX, two , resto) );
  qassertTrue( three == BasicCPU::Addmul( one, two , resto) );
}

void KernelTest::testDiv(){
  //shouldn't try to divide by zero
  qassertTrue( three == BasicCPU::Div(three, one, resto) );


  qassertTrue( zero == BasicCPU::Div(one, two, resto) ); 
  qassertTrue( one ==  resto ); 
  
  qassertTrue( (Constants::CIFRA_MAX/2) +1 == BasicCPU::Div(zero, two, resto) ); 
  qassertTrue( zero ==  resto );
}

void KernelTest::testShiftl(){
  qassertTrue( two == BasicCPU::Shiftl(one,1, resto) );
  Digit tmp = one;
  tmp <<= Constants::BITS_EN_CIFRA-1;
  qassertTrue( tmp == BasicCPU::Shiftl(one, Constants::BITS_EN_CIFRA-1, resto));

  qassertTrue( zero == BasicCPU::Shiftl(two, Constants::BITS_EN_CIFRA-1, resto));
  qassertTrue( (Digit)1 ==  resto);
}

void KernelTest::testShiftlr(){
  qassertTrue( one == BasicCPU::Shiftlr(three, 1, resto) );
  Digit tmp = one;
  tmp <<= Constants::BITS_EN_CIFRA-1;
  qassertTrue( tmp ==  resto);

  qassertTrue( one == BasicCPU::Shiftlr(two, 1, resto) );
  qassertTrue( zero ==  resto);

}


void KernelTest::testMnob(){
  qassertTrue( (Digit)1 == BasicCPU::Mnob(one));
  qassertTrue( (Digit)2 == BasicCPU::Mnob(two));
  qassertTrue( (Digit)1 == BasicCPU::Mnob(zero));
  qassertTrue( (Digit)1 == BasicCPU::Mnob(zero));
  qassertTrue( (Digit)25== BasicCPU::Mnob((Digit)32490673));
  qassertTrue( (Digit)Constants::BITS_EN_CIFRA == BasicCPU::Mnob(Constants::CIFRA_MAX));

  //undefined for 0. Could be considered to be the number of bits of
  //the basic type, but that's not guaranted
}








