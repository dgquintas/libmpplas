/*
 * $Id$
 */

#include <string>
#include "KernelTest.h"
#include "kernel.h"

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
  zro = (Digit)0;

  overflow = resto = 0;

  //Pre-defined constants:
  // mpplas::Constants::DIGIT_MAX
  // mpplas::Constants::SIGNEDDIGIT_MAX


}
void KernelTest::tearDown(){
//empty. new is not used
}

void KernelTest::testAdd(){
  qassertTrue( three == BasicCPU::Add(one,two, overflow) );
  qassertTrue( zro == BasicCPU::Add(Constants::DIGIT_MAX, one, overflow) );
  qassertTrue( one == overflow );
}

void KernelTest::testAddx(){
  const Digit CM = Constants::DIGIT_MAX;
  qassertTrue( zro ==BasicCPU::Addx(CM, one, overflow) );
  qassertTrue( one == BasicCPU::Addx(zro,zro, overflow) );
  qassertTrue( CM-1 == BasicCPU::Addx(CM,CM, overflow) );
  qassertTrue( one == overflow );

}

void KernelTest::testSub(){ 
    qassertTrue(two == BasicCPU::Sub(three, one, overflow) );
  qassertTrue( zro == overflow );

  qassertTrue( one == BasicCPU::Sub(three, two, overflow) );
  qassertTrue( zro == overflow );


  qassertTrue( zro == BasicCPU::Sub(three, three, overflow) );
  qassertTrue( zro == overflow );

  qassertTrue( Constants::DIGIT_MAX == BasicCPU::Sub(zro, one, overflow) );
  qassertTrue( one == overflow );
}

void KernelTest::testSubx(){
  qassertTrue( one == BasicCPU::Subx(three, two, overflow) );
  qassertTrue( zro == overflow);

  qassertTrue( zro == BasicCPU::Subx(three, three, overflow) );
  qassertTrue( zro ==  overflow );
  
//  qassertTrue( (Digit)(Constants::SIGNEDDIGIT_MAX)+1 == BasicCPU::Sub(Constants::DIGIT_MAX, (Digit)Constants::SIGNEDDIGIT_MAX) );
//  qassertTrue( zro ==  overflow );

  qassertTrue( Constants::DIGIT_MAX == BasicCPU::Sub(zro, one, overflow) );
  qassertTrue( one ==  overflow );

  qassertTrue( zro == BasicCPU::Subx(three, two, overflow) );
  qassertTrue( zro ==  overflow );

  qassertTrue( Constants::DIGIT_MAX == BasicCPU::Sub(zro, one, overflow) );
  qassertTrue( one ==  overflow );

  qassertTrue( Constants::DIGIT_MAX == BasicCPU::Subx(two, two, overflow) );
  qassertTrue( one ==  overflow );
}

void KernelTest::testMul(){
  qassertTrue( zro == BasicCPU::Mul(one, zro, resto) );

  qassertTrue( one == BasicCPU::Mul(Constants::DIGIT_MAX, Constants::DIGIT_MAX, resto) );
  qassertTrue( Constants::DIGIT_MAX - 1 /* base -2 */ ==  resto );
}
void KernelTest::testAddmul(){
  BasicCPU::Mul(Constants::DIGIT_MAX, Constants::DIGIT_MAX, resto);
  //  resto  == BASE-2
  qassertTrue( Constants::DIGIT_MAX-1 == BasicCPU::Addmul( zro, one, resto ) );

  resto = 0;

  qassertTrue( Constants::DIGIT_MAX << 1  == BasicCPU::Addmul( Constants::DIGIT_MAX, two , resto) );
  qassertTrue( three == BasicCPU::Addmul( one, two , resto) );
}

void KernelTest::testDiv(){
  //shouldn't try to divide by zro
  qassertTrue( three == BasicCPU::Div(three, one, resto) );


  qassertTrue( zro == BasicCPU::Div(one, two, resto) ); 
  qassertTrue( one ==  resto ); 
  
  qassertTrue( (Constants::DIGIT_MAX/2) +1 == BasicCPU::Div(zro, two, resto) ); 
  qassertTrue( zro ==  resto );
}

void KernelTest::testShiftl(){
  qassertTrue( two == BasicCPU::Shiftl(one,1, resto) );
  Digit tmp = one;
  tmp <<= Constants::BITS_EN_CIFRA-1;
  qassertTrue( tmp == BasicCPU::Shiftl(one, Constants::BITS_EN_CIFRA-1, resto));

  qassertTrue( zro == BasicCPU::Shiftl(two, Constants::BITS_EN_CIFRA-1, resto));
  qassertTrue( (Digit)1 ==  resto);
}

void KernelTest::testShiftlr(){
  qassertTrue( one == BasicCPU::Shiftlr(three, 1, resto) );
  Digit tmp = one;
  tmp <<= Constants::BITS_EN_CIFRA-1;
  qassertTrue( tmp ==  resto);

  qassertTrue( one == BasicCPU::Shiftlr(two, 1, resto) );
  qassertTrue( zro ==  resto);

}


void KernelTest::testMnob(){
  qassertTrue( (Digit)1 == BasicCPU::Mnob(one));
  qassertTrue( (Digit)2 == BasicCPU::Mnob(two));
  qassertTrue( (Digit)1 == BasicCPU::Mnob(zro));
  qassertTrue( (Digit)1 == BasicCPU::Mnob(zro));
  qassertTrue( (Digit)25== BasicCPU::Mnob((Digit)32490673));
  qassertTrue( (Digit)Constants::BITS_EN_CIFRA == BasicCPU::Mnob(Constants::DIGIT_MAX));

  //undefined for 0. Could be considered to be the number of bits of
  //the basic type, but that's not guaranted
}








