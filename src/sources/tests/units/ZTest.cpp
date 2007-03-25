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
  : funcs(Funciones::getInstance()), uno((Cifra)1), dos((Cifra)2), cero((Cifra)0)
{
  pari_init(1000000, 0);
  
  funcs->getFunc(rnd);

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

  z1 = rnd->leerBits(brand(2000,5000));
  z2 = rnd->leerBits(brand(2000,5000));

//  this->uno = Z::convertir((Cifra)1);
//  this->dos = Z::convertir((Cifra)2);
//  this->cero= Z::convertir((Cifra)0);

  
}
void ZTest::tearDown(){
//empty. new is not used
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

  z2  = rnd->leerBits(brand(4,6));
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
  } catch (Errores::DivisionPorCero){
    return;
  }

  qassertTrue(false);

}
void ZTest::testModulusByZeroThrows(){
  try{
    uno % cero;
  } catch (Errores::DivisionPorCero){
    return;
  }

  qassertTrue(false);

}



void ZTest::testFactorial(){
  Cifra rand = (rnd->leerCifra()) % (1UL<<14);

  Z res(rand);

  string tmp;
  tmp += res.toString();
  tmp += "!";

  res.factorial();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();


  qassertEquals( pariStr, thisStr );
  
}
