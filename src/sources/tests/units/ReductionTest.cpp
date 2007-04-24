/*
 * $Id $
 */

#include <string>
#include "ReductionTest.h"
#include "Potencia.h"
#include <pari/pari.h>
#include "aux.h"

using namespace com_uwyn_qtunit;
using namespace mpplas;

ReductionTest::ReductionTest()
  : _redMont(), _redBarret(), _redMersenne(), _funcs(Funciones::getInstance())
{

  pari_init(1000000, 0);

  _funcs->getFunc(_rnd);
  _funcs->getFunc(_primeGen);

  addTest(ReductionTest, testMontgomeryPrecomp);
  addTest(ReductionTest, testMontgomeryReduction);

  addTest(ReductionTest, testBarrettPrecomp  );
  addTest(ReductionTest, testBarrettReduction );

  addTest(ReductionTest, testALaMersenneReduction);
  
}
void ReductionTest::setUp(){
}
void ReductionTest::tearDown(){
//empty. new is not used
}


void ReductionTest::testMontgomeryPrecomp(){
  // montgomery's precomps correspond to 
  // -((modulus)^(-1)) mod BASE

  Z dummy;
  dummy.potenciaBase(1);
  

  _integer = _primeGen->leerPrimoProb(128);
  GEN x,m;

  x = gp_read_str(const_cast<char*>(_integer.toString().c_str()));
  m = gp_read_str(const_cast<char*>(dummy.toString().c_str()));

  GEN pariRes = Fp_invsafe(x,m);
  qassertTrue( pariRes );
  string pariStr(GENtostr( pariRes ));
  dummy -= Z(pariStr);

  Z libsRes = _redMont.precomputaciones(_integer);

  qassertTrue( libsRes == dummy );
  
}

void ReductionTest::testMontgomeryReduction(){
  Z primeMod(_primeGen->leerPrimoProb(128));
  _integer = _rnd->leerBits(256);
  int n = primeMod.longitud();
  Z R; R.hacerCero();
  R.potenciaBase(n);


  GEN x,y, m;

  x = gp_read_str(const_cast<char*>(R.toString().c_str()));
  y = gp_read_str(const_cast<char*>(_integer.toString().c_str()));
  m = gp_read_str(const_cast<char*>(primeMod.toString().c_str()));

  x = Fp_invsafe(x,m);
  qassertTrue( x != NULL);
  x = gmul(x, y);
  GEN pariRes = gmod(x,m);

  qassertTrue( pariRes );
  string pariStr(GENtostr( pariRes ));
  
  Z mPrima = _redMont.precomputaciones(primeMod);

  _redMont.redMontgomery(&_integer, primeMod, mPrima);

  qassertTrue( _integer.toString() == pariStr );

}

void ReductionTest::testBarrettPrecomp(){ 
  Z mod(_rnd->leerBits(brand(300,2000)));
  _integer = _rnd->leerBits(brand(2000, 4000));

  Z b2k; b2k.hacerUno();
  b2k.potenciaBase( 2*mod.longitud() );
  
  GEN x, m;

  x = gp_read_str(const_cast<char*>(b2k.toString().c_str()));
  m = gp_read_str(const_cast<char*>(mod.toString().c_str()));

  
  GEN pariRes = gfloor( gdiv(x, m) );

  Z mu( _redBarret.precomputaciones(mod) );

  string pariStr(GENtostr( pariRes ));
  qassertTrue( mu.toString() == pariStr );


}
void ReductionTest::testBarrettReduction(){
  Z mod(_rnd->leerBits(brand(1000,2000)));
  _integer = _rnd->leerBits( mod.numBits() * 2 );
 
  GEN x, m;

  x = gp_read_str(const_cast<char*>(_integer.toString().c_str()));
  m = gp_read_str(const_cast<char*>(mod.toString().c_str()));

  
  GEN pariRes = gmod(x, m);

  Z mu( _redBarret.precomputaciones(mod) );
  _redBarret.redBarrett(&_integer, mod, mu);
  string pariStr(GENtostr( pariRes ));
  qassertTrue( _integer.toString() == pariStr );


}

void ReductionTest::testALaMersenneReduction(){
}
