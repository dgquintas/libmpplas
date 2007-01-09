/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include <sstream>
#include "Z_nTest.h"
#include <pari/pari.h>


using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( Z_nTest );

Z_nTest::Z_nTest(){
  pari_init(1000000, 0);
}

void Z_nTest::setUp(){
  integer = funcs.getRandomRapido()->leerBits(2000);
  modulus = funcs.getRandomRapido()->leerBits(500);
  modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);
  //anotherModularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1414), modulus);
  cifra = funcs.getRandomRapido()->leerCifra();
  cifraSigno = funcs.getRandomRapido()->leerCifraSigno();
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testAdditionWithCifra(){
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testAdditionWithCifraSigno(){
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );

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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testSubstractionWithCifra(){
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testSubstractionWithCifraSigno(){
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );

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
  
  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testProductWithCifra(){
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testProductWithCifraSigno(){
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}






void Z_nTest::testDivisionWithZ(){
  //make sure the modulus is prime (ie, invertible)
  this->modulus = funcs.getGenPrimos()->leerPrimoProb(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testDivisionWithZThrows(){
  this->modulus = funcs.getRandomRapido()->leerBits(500)*integer;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);

  Z_n res = (*modularInteger) / integer ; 

  //this point shouldn't be reached 
  CPPUNIT_ASSERT(false);
}
void Z_nTest::testDivisionWithCifra(){
  //make sure the modulus is prime (ie, invertible)
  this->modulus = funcs.getGenPrimos()->leerPrimoProb(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );

}

void Z_nTest::testDivisionWithCifraThrows(){
  this->modulus = funcs.getRandomRapido()->leerBits(500)*cifra;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);

  Z_n res = (*modularInteger) / cifra ; 

  //this point shouldn't be reached 
  CPPUNIT_ASSERT(false);

}
void Z_nTest::testDivisionWithCifraSigno(){
  //make sure the modulus is prime (ie, invertible)
  this->modulus = funcs.getGenPrimos()->leerPrimoProb(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testDivisionWithCifraSignoThrows(){
  this->modulus = funcs.getRandomRapido()->leerBits(500)*cifraSigno;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);

  Z_n res = (*modularInteger) / cifraSigno ; 

  //this point shouldn't be reached 
  CPPUNIT_ASSERT(false);
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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testExponentiationWithCifra(){
  //make sure the modulus is coprime with the base
  this->modulus = funcs.getGenPrimos()->leerPrimoProb(128);
  delete this->modularInteger;
  this->modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);

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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testExponentiationWithCifraSigno(){ 
  //make sure the modulus is coprime with the base
  this->modulus = funcs.getGenPrimos()->leerPrimoProb(128);
  delete this->modularInteger;
  this->modularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1234), modulus);

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

  CPPUNIT_ASSERT_EQUAL( pariStr, thisStr );
}
void Z_nTest::testExponentiationWithCifraSignoThrows(){
  //make sure the modulus isn't coprime with the base
  this->modularInteger->operator*=(this->modulus);

  Z_n res = (*modularInteger) ^ cifraSigno ;

}

