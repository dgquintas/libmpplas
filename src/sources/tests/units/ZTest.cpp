/*
 * $Id$
 */

#include <string>
#include "ZTest.h"
#include <pari/pari.h>
#include "aux.h" 


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;


ZTest::ZTest()
  : funcs(Functions::getInstance()), uno((Digit)1), dos((Digit)2), cero((Digit)0)
{
  
  funcs->getFunc(rnd);

  addTest(ZTest, testInput);
  addTest(ZTest, testEquality);
  addTest(ZTest, testAddition);
  addTest(ZTest, testSubstraction);
  addTest(ZTest, testMultiplication);
  addTest(ZTest, testDivision);
  addTest(ZTest, testModulus);
  addTest(ZTest, testExponentiation);
  addTest(ZTest, testSquare);
  addTest(ZTest, testDivideByZeroThrows);
  addTest(ZTest, testModulusByZeroThrows);
  addTest(ZTest, testFactorial);
}

void ZTest::setUp(){

  z1 = rnd->getInteger(brand(2000,5000));
  z2 = rnd->getInteger(brand(2000,5000));

//  this->uno = Z::convertir((Digit)1);
//  this->dos = Z::convertir((Digit)2);
//  this->cero= Z::convertir((Digit)0);

  
}
void ZTest::tearDown(){
//empty. new is not used
}

void ZTest::testInput(){
  std::string
    somePiDecimals("31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
  "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"
  "4428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273"
  "724587006606315588174881520920962829254091715364367892590360011330530548820466521384146");
  Z foo(somePiDecimals);
  qassertTrue( foo.toString() == somePiDecimals );

}

void ZTest::testEquality(){
  qassertTrue( uno != cero );
  qassertTrue( uno == uno );

  qassertTrue( !(uno == cero) );
  qassertTrue( !(uno != uno) );
}
void ZTest::testAddition(){
  qassertTrue( uno + uno == dos );
  qassertTrue( uno + cero == uno );
  qassertTrue( cero + cero == cero );

  Z res = z1 + z2;
   
  string tmp;
  tmp += z1.toString();
  tmp += " + ";
  tmp += z2.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertEquals( pariStr, thisStr );


}
void ZTest::testSubstraction(){
  qassertTrue( dos - uno == uno );
  qassertTrue( cero - uno == -uno );
  qassertTrue( cero - cero == cero );

  Z res = z1 - z2;
   
  string tmp;
  tmp += z1.toString();
  tmp += " - ";
  tmp += z2.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertEquals( pariStr, thisStr );
};
void ZTest::testMultiplication(){
  qassertTrue( dos * uno == dos );
  qassertTrue( cero * uno == cero );
  qassertTrue( cero * cero == cero );

  Z res = z1 * z2;
   
  string tmp;
  tmp += z1.toString();
  tmp += " * ";
  tmp += z2.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertEquals( pariStr, thisStr );
};
void ZTest::testDivision(){
  qassertTrue( dos / uno == dos );
  qassertTrue( cero / uno == cero );

  Z res = z1 / z2;
   
  string tmp;
  tmp += z1.toString();
  tmp += " / ";
  tmp += z2.toString();
  
  GEN x = gp_read_str(const_cast<char*>(tmp.c_str()));
  x = gtrunc(x);

  string pariStr(GENtostr( x ));
  string thisStr = res.toString();

  qassertEquals( pariStr, thisStr );
};

void ZTest::testModulus(){
  qassertTrue( dos % uno == cero );
  qassertTrue( uno % dos == uno );

  Z res = z1 % z2;
   
  string tmp;
  tmp += z1.toString();
  tmp += " % ";
  tmp += z2.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertEquals( pariStr, thisStr );
};
void ZTest::testExponentiation(){
  qassertTrue( (dos ^ uno) == dos );
  qassertTrue( (dos ^ cero) == uno );

  z2  = rnd->getInteger(brand(4,6));
  Z res = (z1 ^ z2) ;
   
  string tmp;
  tmp += z1.toString();
  tmp += " ^ ";
  tmp += z2.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertEquals( pariStr, thisStr );
};

void ZTest::testSquare(){
  Z res = (cuadrado(z1)) ;
   
  string tmp;
  tmp += z1.toString();
  tmp += " ^ ";
  tmp += "2";

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertEquals( pariStr, thisStr );
};


void ZTest::testDivideByZeroThrows(){
  try{
    uno / cero;
  } catch (Errors::DivisionPorCero){
    return;
  }

  qassertTrue(false);

}
void ZTest::testModulusByZeroThrows(){
  try{
    uno % cero;
  } catch (Errors::DivisionPorCero){
    return;
  }

  qassertTrue(false);

}



void ZTest::testFactorial(){
  Digit rand = (rnd->getDigit()) % (1UL<<14);

  Z res(rand);

  string tmp;
  tmp += res.toString();
  tmp += "!";

  res.factorial();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();


  qassertEquals( pariStr, thisStr );
  
}
