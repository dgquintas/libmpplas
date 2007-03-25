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
  : funcs(Funciones::getInstance())
{
  pari_init(1000000, 0);

  funcs->getFunc(rnd);

  addTest(Z_nTest, testAdditionWithZ);
  addTest(Z_nTest, testAdditionWithCifra);
  addTest(Z_nTest, testAdditionWithCifraSigno);

  addTest(Z_nTest, testSubstractionWithZ);
  addTest(Z_nTest, testSubstractionWithCifra);
  addTest(Z_nTest, testSubstractionWithCifraSigno);

  addTest(Z_nTest, testProductWithZ);
  addTest(Z_nTest, testProductWithCifra);
  addTest(Z_nTest, testProductWithCifraSigno);

  addTest(Z_nTest, testDivisionWithZ);
  addTest(Z_nTest, testDivisionWithZThrows);
  addTest(Z_nTest, testDivisionWithCifra);
  addTest(Z_nTest, testDivisionWithCifraThrows);
  addTest(Z_nTest, testDivisionWithCifraSigno);
  addTest(Z_nTest, testDivisionWithCifraSignoThrows);

  addTest(Z_nTest, testExponentiationWithZ);
  addTest(Z_nTest, testExponentiationWithCifra);
  addTest(Z_nTest, testExponentiationWithCifraSigno);
  addTest(Z_nTest, testExponentiationWithCifraSignoThrows);

}

void Z_nTest::setUp(){
  integer = rnd->leerBits(brand(2000,5000));
  modulus = rnd->leerBits(brand(500,1000));
  modularInteger = new Z_n(rnd->leerBits(brand(1000,2000)), modulus);
  //anotherModularInteger = new Z_n(funcs.getRandomRapido()->leerBits(1414), modulus);
  cifra = rnd->leerCifra();
  cifraSigno = rnd->leerCifraSigno();
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

  qassertTrue( pariStr == thisStr );
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

  qassertTrue(pariStr == thisStr );
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

  qassertTrue(pariStr == thisStr );
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

  qassertTrue(pariStr == thisStr );
}






void Z_nTest::testDivisionWithZ(){
  //make sure the modulus is prime (ie, invertible)
  GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);
  this->modulus = genPrimos->leerPrimoProb(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->leerBits(1234), modulus);
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
  this->modulus = rnd->leerBits(500)*integer;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->leerBits(1234), modulus);


  try{
    Z_n res = (*modularInteger) / integer ; 
  } catch( Errores::ElementoNoInvertible){
    return;
  }
  catch(exception& e){
    cerr << e.what() << endl;
  }


  //this point shouldn't be reached 
  qassertTrue(false);
}
void Z_nTest::testDivisionWithCifra(){
  //make sure the modulus is prime (ie, invertible)
  GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);
  this->modulus = genPrimos->leerPrimoProb(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->leerBits(1234), modulus);
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

void Z_nTest::testDivisionWithCifraThrows(){
  this->modulus = rnd->leerBits(500)*cifra;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->leerBits(1234), modulus);
  try{
    Z_n res = (*modularInteger) / cifra ; 
  } catch( Errores::ElementoNoInvertible){
    return;
  }


  //this point shouldn't be reached 
  qassertTrue(false);

}
void Z_nTest::testDivisionWithCifraSigno(){
  //make sure the modulus is prime (ie, invertible)
  GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);
  this->modulus = genPrimos->leerPrimoProb(128);  
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->leerBits(1234), modulus);
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
void Z_nTest::testDivisionWithCifraSignoThrows(){
  this->modulus = rnd->leerBits(500)*cifraSigno;  //make sure the modulus isn't 
  //coprime with the divisor
  delete this->modularInteger; //get rid of the one set up by setUp()
  this->modularInteger = new Z_n(rnd->leerBits(1234), modulus);

  try{
    Z_n res = (*modularInteger) / cifraSigno ; 
  } catch( Errores::ElementoNoInvertible){
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
void Z_nTest::testExponentiationWithCifra(){
  //make sure the modulus is coprime with the base
    GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);
  this->modulus = genPrimos->leerPrimoProb(128);
  delete this->modularInteger;
  this->modularInteger = new Z_n(rnd->leerBits(1234), modulus);

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
void Z_nTest::testExponentiationWithCifraSigno(){ 
  //make sure the modulus is coprime with the base
   GenPrimos* genPrimos=0;
  funcs->getFunc(genPrimos);

  this->modulus = genPrimos->leerPrimoProb(128);
  delete this->modularInteger;
  this->modularInteger = new Z_n(rnd->leerBits(1234), modulus);

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
void Z_nTest::testExponentiationWithCifraSignoThrows(){
  //make sure the modulus isn't coprime with the base
  this->modularInteger->operator*=(this->modulus);
  try{
    Z_n res = (*modularInteger) ^ cifraSigno ;
  } catch( Errores::ElementoNoInvertible){
    return;
  }
  catch(exception& e){
    cerr << e.what() << endl;
  }


  qassertTrue(false);

}

