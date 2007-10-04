/*
 * $Id $
 */

#include <string>
#include <sstream>
#include "Z_nTest.h"
#include <pari/pari.h>
#include "aux.h"
#include <exception>


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;

Z_nTest::Z_nTest() 
  : funcs(MethodsFactory::getInstance())
{

  funcs->getFunc(rnd);

  addTest(Z_nTest, testAdditionWithZ);
  addTest(Z_nTest, testAdditionWithDigit);
  addTest(Z_nTest, testAdditionWithSignedDigit);

  addTest(Z_nTest, testSubstractionWithZ);
  addTest(Z_nTest, testSubstractionWithDigit);
  addTest(Z_nTest, testSubstractionWithSignedDigit);

  addTest(Z_nTest, testProductWithZ);
  addTest(Z_nTest, testProductWithDigit);
  addTest(Z_nTest, testProductWithSignedDigit);

  addTest(Z_nTest, testDivisionWithZ);
  addTest(Z_nTest, testDivisionWithZThrows);
  addTest(Z_nTest, testDivisionWithDigit);
  addTest(Z_nTest, testDivisionWithDigitThrows);
  addTest(Z_nTest, testDivisionWithSignedDigit);
  addTest(Z_nTest, testDivisionWithSignedDigitThrows);

  addTest(Z_nTest, testExponentiationWithZ);
  addTest(Z_nTest, testExponentiationWithDigit);
  addTest(Z_nTest, testExponentiationWithSignedDigit);
  addTest(Z_nTest, testExponentiationWithSignedDigitThrows);

}

void Z_nTest::setUp(){
  integer = rnd->getInteger(brand(2000,5000));
  modulus = rnd->getInteger(brand(500,1000));
  modularInteger = new Z_n(rnd->getInteger(brand(1000,2000)), modulus);
  //anotherModularInteger = new Z_n(funcs.getRandomFast()->getInteger(1414), modulus);
  cifra = rnd->getDigit();
  cifraSigno = rnd->getSignedDigit();
  if( cifraSigno > 0 ){
    cifraSigno *= -1;  //force a negative number
  }
}


void Z_nTest::tearDown(){
  delete this->modularInteger;
}





void Z_nTest::testAdditionWithZ(){
  Z_n res = (*modularInteger) + integer; 

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " + ";
  tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue( pariStr == thisStr );
}
void Z_nTest::testAdditionWithDigit(){
  Z_n res = (*modularInteger) + cifra; 
 
  ostringstream oss;
  oss << cifra;
  string cifraStr = oss.str();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " + ";
  tmp += cifraStr;
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue( pariStr == thisStr );
}
void Z_nTest::testAdditionWithSignedDigit(){
  Z_n res = (*modularInteger) + cifraSigno; 
 
  ostringstream oss;
  oss << cifraSigno;
  string cifraStr = oss.str();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " + ";
  tmp += cifraStr;
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );

}





void Z_nTest::testSubstractionWithZ(){
  Z_n res = (*modularInteger) - integer ; 

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " - ";
  tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testSubstractionWithDigit(){
  Z_n res = (*modularInteger) - cifra; 
 
  ostringstream oss;
  oss << cifra;
  string cifraStr = oss.str();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " - ";
  tmp += cifraStr;
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testSubstractionWithSignedDigit(){
  Z_n res = (*modularInteger) - cifraSigno; 
 
  ostringstream oss;
  oss << cifraSigno;
  string cifraStr = oss.str();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " - ";
  tmp += cifraStr;
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );

}




void Z_nTest::testProductWithZ(){
  Z_n res = (*modularInteger) * integer ; 

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " * ";
  tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();
  
  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testProductWithDigit(){
  Z_n res = (*modularInteger) * cifra; 
 
  ostringstream oss;
  oss << cifra;
  string cifraStr = oss.str();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " * ";
  tmp += cifraStr;
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testProductWithSignedDigit(){
  Z_n res = (*modularInteger) * cifraSigno; 
 
  ostringstream oss;
  oss << cifraSigno;
  string cifraStr = oss.str();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " * ";
  tmp += cifraStr;
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}






void Z_nTest::testDivisionWithZ(){
  //make sure the modulus is prime (ie, invertible)
  GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);
  this->modulus = genPrimos->getPrime(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->getInteger(1234), modulus);
  Z_n res = (*modularInteger) / integer ; 

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " / ";
  tmp += integer.toString();
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testDivisionWithZThrows(){
  this->modulus = rnd->getInteger(500)*integer;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->getInteger(1234), modulus);


  try{
    Z_n res = (*modularInteger) / integer ; 
  } catch( Errors::NonInvertibleElement){
    return;
  }
  catch(exception& e){
    cerr << e.what() << endl;
  }


  //this point shouldn't be reached 
  qassertTrue(false);
}
void Z_nTest::testDivisionWithDigit(){
  //make sure the modulus is prime (ie, invertible)
  GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);
  this->modulus = genPrimos->getPrime(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->getInteger(1234), modulus);
  Z_n res = (*modularInteger) / cifra ; 

  ostringstream oss;
  oss << cifra;
  string cifraStr = oss.str();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " / ";
  tmp += cifraStr;
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );

}

void Z_nTest::testDivisionWithDigitThrows(){
  this->modulus = rnd->getInteger(500)*cifra;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->getInteger(1234), modulus);
  try{
    Z_n res = (*modularInteger) / cifra ; 
  } catch( Errors::NonInvertibleElement){
    return;
  }


  //this point shouldn't be reached 
  qassertTrue(false);

}
void Z_nTest::testDivisionWithSignedDigit(){
  //make sure the modulus is prime (ie, invertible)
  GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);
  this->modulus = genPrimos->getPrime(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->getInteger(1234), modulus);
  Z_n res = (*modularInteger) / cifraSigno ; 

  ostringstream oss;
  oss << cifraSigno;
  string cifraStr = oss.str();

  string tmp;
  tmp += '(';
  tmp += modularInteger->toString();
  tmp += " / ";
  tmp += cifraStr;
  tmp += ") % ";
  tmp += modulus.toString();

  string pariStr(GENtostr( gp_read_str((char*)tmp.c_str()) ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testDivisionWithSignedDigitThrows(){
  this->modulus = rnd->getInteger(500)*cifraSigno;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->getInteger(1234), modulus);

  try{
    Z_n res = (*modularInteger) / cifraSigno ; 
  } catch( Errors::NonInvertibleElement){
    return;
  }
  catch(exception& e){
    cerr << e.what() << endl;
  }

  //this point shouldn't be reached 
  qassertTrue(false);
}







void Z_nTest::testExponentiationWithZ(){
  Z_n res = (*modularInteger) ^ integer ; 

  GEN x,y,m;

  x = gp_read_str(const_cast<char*>(modularInteger->toString().c_str()));
  y = gp_read_str(const_cast<char*>(integer.toString().c_str()) );
  m = gp_read_str(const_cast<char*>(modulus.toString().c_str()));

  GEN pariRes = Fp_pow(x,y,m);

  string pariStr(GENtostr( pariRes ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testExponentiationWithDigit(){
  //make sure the modulus is coprime with the base
    GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);
  this->modulus = genPrimos->getPrime(128);
  delete this->modularInteger;
  this->modularInteger = new Z_n(rnd->getInteger(1234), modulus);

  Z_n res = (*modularInteger) ^ cifra ;

  ostringstream oss;
  oss << cifra;
  string cifraStr = oss.str();

  GEN x,y,m;

  x = gp_read_str(const_cast<char*>(modularInteger->toString().c_str()));
  y = gp_read_str(const_cast<char*>(cifraStr.c_str()));
  m = gp_read_str(const_cast<char*>(modulus.toString().c_str()));

  GEN pariRes = Fp_pow(x,y,m);

  string pariStr(GENtostr( pariRes ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testExponentiationWithSignedDigit(){ 
  //make sure the modulus is coprime with the base
   GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);

  this->modulus = genPrimos->getPrime(128);
  delete this->modularInteger;
  this->modularInteger = new Z_n(rnd->getInteger(1234), modulus);

  Z_n res = (*modularInteger) ^ cifraSigno ;

  ostringstream oss;
  oss << cifraSigno;
  string cifraStr = oss.str();

  GEN x,y,m;

  x = gp_read_str(const_cast<char*>(modularInteger->toString().c_str()));
  y = gp_read_str(const_cast<char*>(cifraStr.c_str()));
  m = gp_read_str(const_cast<char*>(modulus.toString().c_str()));

  GEN pariRes = Fp_pow(x,y,m);

  string pariStr(GENtostr( pariRes ));
  string thisStr = res.toString();

  qassertTrue(pariStr == thisStr );
}
void Z_nTest::testExponentiationWithSignedDigitThrows(){
  //make sure the modulus isn't coprime with the base
  this->modularInteger->operator*=(this->modulus);
  try{
    Z_n res = (*modularInteger) ^ cifraSigno ;
  } catch( Errors::NonInvertibleElement){
    return;
  }
  catch(exception& e){
    cerr << e.what() << endl;
  }


  qassertTrue(false);

}

