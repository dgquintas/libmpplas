/*
 * $Id $
 */

#include "Random.h"
#include "Primos.h"
#include "ExponentiationTest.h"
#include "aux.h"
#include "GCD.h"

#include <iostream>

using namespace com_uwyn_qtunit;
using namespace mpplas;

ExponentiationTest::ExponentiationTest()
  : funcs( MethodsFactory::getInstance() )
{

  addTest(ExponentiationTest, testSlidingWindowExp );
  addTest(ExponentiationTest, testSlidingWindowExpR );
  addTest(ExponentiationTest, testExpLeftRight );
  addTest(ExponentiationTest, testExpMontgomery );
  addTest(ExponentiationTest, testExpBarrett );
  addTest(ExponentiationTest, testTwoThreadedModularExp );
  addTest(ExponentiationTest, testMultiThreadedModularExp);

  funcs->getFunc(rnd);
  funcs->getFunc(primes);
}
void ExponentiationTest::setUp(){
  _base = rnd->getInteger( brand(300,600 ) );
  _exp  = rnd->getSignedDigit() % brand(500, 1500);
  _expZ = rnd->getInteger( brand(300,600) );
 

  x = gp_read_str(const_cast<char*>(_base.toString().c_str()));
  y = gp_read_str(const_cast<char*>(Z(_exp).toString().c_str()));
  Y = gp_read_str(const_cast<char*>(_expZ.toString().c_str()));




}
void ExponentiationTest::tearDown(){
//empty. new is not used
}


void ExponentiationTest::testSlidingWindowExp(){
  GEN pariRes = powgi(x,y);
  PotVentanaDeslizante potFunc;
  potFunc.exponentiation(&_base,_exp);

  std::string pariStr(GENtostr( pariRes ));
  qassertTrue( _base.toString() == pariStr );

}
void ExponentiationTest::testSlidingWindowExpR(){}
void ExponentiationTest::testExpLeftRight(){
  GEN pariRes = powgi(x,y);
  PotLeftRight potFunc;
  potFunc.exponentiation(&_base,_exp);

  std::string pariStr(GENtostr( pariRes ));

  qassertTrue ( _base.toString() == pariStr );

}
void ExponentiationTest::testExpMontgomery(){
  Z _mod(rnd->getInteger( brand(1000,2000) ));
  if( _mod.esPar() ){
    _mod++;
  }
  GEN m = gp_read_str(const_cast<char*>(_mod.toString().c_str()));
  GEN pariRes = Fp_pow(x,Y,m);
  PotMontgomery potFunc;
  Z_n base_n(_base, _mod);
  potFunc.exponentiation(&base_n,_expZ);

  std::string pariStr(GENtostr( pariRes ));
  qassertEquals( base_n.toString(), pariStr );
}
void ExponentiationTest::testExpBarrett(){
  Z _mod(primes->getPrime( brand(100,200) ));
  GEN m = gp_read_str(const_cast<char*>(_mod.toString().c_str()));
  GEN pariRes = Fp_pow(x,Y,m);
  ClasicoConBarrett potFunc;
  Z_n base_n(_base,_mod);
  potFunc.exponentiation(&base_n,_expZ);

  std::string pariStr(GENtostr( pariRes ));
  qassertEquals( base_n.toString(), pariStr );

  Y = gmul(Y, gp_read_str("-1"));
  pariRes = Fp_pow(x,Y,m);

  base_n = _base;
  _expZ.cambiarSigno();
  potFunc.exponentiation(&base_n,_expZ);
  pariStr = GENtostr( pariRes );
  qassertEquals( base_n.toString() ,pariStr );


}

void ExponentiationTest::testTwoThreadedModularExp(){
  Z _mod(rnd->getInteger( brand(1000,2000) )); 
  GCD<Z>::DFL gcd;

  while( _mod.esPar() || !gcd.gcd(_base, _mod).esUno() ){
    _mod = rnd->getInteger( brand(1000,2000) ); 
  }
  GEN m = gp_read_str(const_cast<char*>(_mod.toString().c_str()));
  GEN pariRes = Fp_pow(x,Y,m);

  TwoThreadedModularExp potFunc;
  Z_n base_n(_base,_mod);
  potFunc.exponentiation(&base_n,_expZ);

  std::string pariStr(GENtostr( pariRes ));

  qassertEquals( base_n.toString(), pariStr );
}

void ExponentiationTest::testMultiThreadedModularExp(){

  MultiThreadedModularExp potFunc;
  Z _mod(rnd->getInteger( brand(1000,2000) )); 
  GEN m = gp_read_str(const_cast<char*>(_mod.toString().c_str()));
  GEN pariRes = Fp_pow(x,Y,m);

  Z_n base_n(_base,_mod);
  potFunc.exponentiation(&base_n,_expZ);

  std::string pariStr(GENtostr( pariRes ));

  qassertEquals( base_n.toString() ,pariStr );

  return;
}

