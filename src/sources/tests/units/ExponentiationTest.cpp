/*
 * $Id $
 */

#include <string>
#include "Random.h"
#include "Primos.h"
#include "Funciones.h"
#include "ExponentiationTest.h"
#include "aux.h"

using namespace com_uwyn_qtunit;
using namespace mpplas;

ExponentiationTest::ExponentiationTest()
  : funcs( Funciones::getInstance() )
{

  addTest(ExponentiationTest, testSlidingWindowExp );
  addTest(ExponentiationTest, testSlidingWindowExpR );
  addTest(ExponentiationTest, testExpLeftRight );
  addTest(ExponentiationTest, testExpMontgomery );
  addTest(ExponentiationTest, testExpBarrett );

  funcs->getFunc(rnd);
  funcs->getFunc(primes);
}
void ExponentiationTest::setUp(){
  _base = rnd->leerBits( brand(100,200 ) );
  _exp  = rnd->leerSignedDigit() % brand(500, 1500);
  _expZ = rnd->leerBits( brand(1000,2000) );
 

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
  potFunc.potencia(&_base,_exp);

  std::string pariStr(GENtostr( pariRes ));
  qassertTrue( _base.toString() == pariStr );

}
void ExponentiationTest::testSlidingWindowExpR(){}
void ExponentiationTest::testExpLeftRight(){
  GEN pariRes = powgi(x,y);
  PotLeftRight potFunc;
  potFunc.potencia(&_base,_exp);

  std::string pariStr(GENtostr( pariRes ));

  qassertTrue ( _base.toString() == pariStr );

}
void ExponentiationTest::testExpMontgomery(){
  Z _mod(rnd->leerBits( brand(1000,2000) ));
  if( _mod.esPar() ){
    _mod++;
  }
  GEN m = gp_read_str(const_cast<char*>(_mod.toString().c_str()));
  GEN pariRes = Fp_pow(x,Y,m);
  PotMontgomery potFunc;
  potFunc.potModular(&_base,_expZ,_mod);

  std::string pariStr(GENtostr( pariRes ));
  qassertEquals( _base.toString(), pariStr );
}
void ExponentiationTest::testExpBarrett(){
  Z _mod(rnd->leerBits( brand(1000,2000) ));
  GEN m = gp_read_str(const_cast<char*>(_mod.toString().c_str()));
  GEN pariRes = Fp_pow(x,Y,m);
  ClasicoConBarrett potFunc;
  potFunc.potModular(&_base,_expZ,_mod);

  std::string pariStr(GENtostr( pariRes ));
  qassertTrue( _base.toString() == pariStr );

}
