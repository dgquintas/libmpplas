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
  x = gmul(x, y);
  GEN pariRes = gmod(x,m);

  qassertTrue( pariRes );
  string pariStr(GENtostr( pariRes ));
  
  Z mPrima = _redMont.precomputaciones(primeMod);
  cout << _integer << endl;
  cout << primeMod << endl;

  _redMont.redMontgomery(&_integer, primeMod, mPrima);

  cout << _integer << endl;
  cout << pariStr << endl;
  qassertTrue( _integer.toString() == pariStr );

}

void ReductionTest::testBarrettPrecomp(){
}
void ReductionTest::testBarrettReduction(){
}

void ReductionTest::testALaMersenneReduction(){
}
