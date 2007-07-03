/*
 * $Id$
 */

#include <string>
#include <sstream>
#include "ZM_nTest.h"
#include <pari/pari.h>
#include "aux.h"
#include <exception>


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;

ZM_nTest::ZM_nTest() 
  : funcs(MethodsFactory::getInstance())
{

  funcs->getFunc(rnd);

  addTest(ZM_nTest, testAdditionWithZ);
  addTest(ZM_nTest, testAdditionWithZM_n);

  addTest(ZM_nTest, testSubstractionWithZ);
  addTest(ZM_nTest, testSubstractionWithZM_n);

  addTest(ZM_nTest, testProductWithZ);
  addTest(ZM_nTest, testProductWithZM_n);
  
  addTest(ZM_nTest, testSquare);

  addTest(ZM_nTest, testExponentiation);
//  addTest(ZM_nTest, testExponentiation);

}

void ZM_nTest::setUp(){
  integer = rnd->getInteger(brand(2000,5000));
  modulus = rnd->getInteger(brand(500,1000));
  if( modulus.esPar() ){
    modulus++;
  }
  modularInteger = new ZM_n(rnd->getInteger(brand(1000,2000)), modulus);
  modularInteger2 = new ZM_n(rnd->getInteger(brand(1000,2000)), modulus);
}


void ZM_nTest::tearDown(){
  delete modularInteger;
  delete modularInteger2;
}





void ZM_nTest::testAdditionWithZ(){
  ZM_n res(*modularInteger + integer); 

  string tmp;
  tmp += '(';
  tmp += modularInteger->toZ().toString();
  tmp += " + ";
  tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toZ().toString();

  qassertTrue( pariStr == thisStr );
}
void ZM_nTest::testAdditionWithZM_n(){
  ZM_n res(*modularInteger + *modularInteger2); 


  string tmp;
  tmp += '(';
  tmp += modularInteger->toZ().toString();
  tmp += " + ";
  tmp += modularInteger2->toZ().toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toZ().toString();

  qassertTrue( pariStr == thisStr );
}



void ZM_nTest::testSubstractionWithZ(){
  ZM_n res( *modularInteger - integer) ; 

  string tmp;
  tmp += '(';
  tmp += modularInteger->toZ().toString();
  tmp += " - ";
  tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toZ().toString();

  qassertTrue(pariStr == thisStr );
}
void ZM_nTest::testSubstractionWithZM_n(){
  ZM_n res(*modularInteger - *modularInteger2); 


  string tmp;
  tmp += '(';
  tmp += modularInteger->toZ().toString();
  tmp += " - ";
  tmp += modularInteger2->toZ().toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toZ().toString();

  qassertTrue( pariStr == thisStr );
}




void ZM_nTest::testProductWithZ(){
  ZM_n res(*modularInteger * integer) ; 

  string tmp;
  tmp += '(';
  tmp += modularInteger->toZ().toString();
  tmp += " * ";
  tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toZ().toString();
  
  qassertTrue(pariStr == thisStr );
}
void ZM_nTest::testProductWithZM_n(){
  ZM_n res(*modularInteger * *modularInteger2); 

  string tmp;
  tmp += '(';
  tmp += modularInteger->toZ().toString();
  tmp += " * ";
  tmp += modularInteger2->toZ().toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toZ().toString();

  qassertTrue( pariStr == thisStr );
}

void ZM_nTest::testSquare(){
  ZM_n res( *modularInteger );
  res.square();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toZ().toString();
  tmp += " * ";
  tmp += modularInteger->toZ().toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toZ().toString();

  qassertEquals(  thisStr,pariStr );
}




void ZM_nTest::testExponentiation(){
  ZM_n res(*modularInteger ^ integer) ; 

  GEN x,y,m;

  x = gp_read_str(const_cast<char*>(modularInteger->toZ().toString().c_str()));
  y = gp_read_str(const_cast<char*>(integer.toString().c_str()) );
  m = gp_read_str(const_cast<char*>(modulus.toString().c_str()));

  GEN pariRes = Fp_pow(x,y,m);

  string pariStr(GENtostr( pariRes ));
  string thisStr = res.toZ().toString();

  qassertEquals(thisStr, pariStr );
}

