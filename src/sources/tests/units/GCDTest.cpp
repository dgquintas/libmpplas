/*
 * $Id $
 */

#include <string>
#include "GCDTest.h"
#include "MethodsFactory.h"
#include "MiVec.h"
#include "aux.h"
#include "Z.h"
#include "Primos.h"

using namespace com_uwyn_qtunit;
using namespace std;


GCDTest::GCDTest() {
  addTest(GCDTest, testGCDLehmer);
  addTest(GCDTest, testGCDExtBinario);
  addTest(GCDTest, testGCDList);
  MethodsFactory::getReference().getFunc(rnd);
}
void GCDTest::setUp(){
  z1 = rnd->getInteger(brand(2000,5000));
  z2 = rnd->getInteger(brand(2000,5000));
 
  x = gp_read_str(const_cast<char*>(z1.toString().c_str()));
  y = gp_read_str(const_cast<char*>(z2.toString().c_str()));
  
}
void GCDTest::tearDown(){
//empty. new is not used
}

void GCDTest::testGCDLehmer(){

  GCDLehmer gcd;
  GEN resP = ggcd(x,y);
  const Z res( gcd.gcd(z1,z2) );

  string pariStr(GENtostr( resP ));
  string thisStr = res.toString();

  qassertEquals( pariStr, thisStr );
}
void GCDTest::testGCDExtBinario(){
  GCDExtBinario gcd;
 
  Z u,v;
  GEN resP = ggcd(x,y);
  const Z res( gcd.gcdext(z1,z2,&u,&v) );

  string pariStr(GENtostr( resP ));

  string thisStr = res.toString();
  string thisStrU = u.toString();
  string thisStrV = v.toString();

  const Z shouldBeRes(z1*u + z2*v);

  qassertTrue( res == shouldBeRes );
  qassertTrue( pariStr == thisStr );

}

void GCDTest::testGCDList(){
  MiVec<Z> list(brand(100,150));
  PrimeGen *primes; MethodsFactory::getReference().getFunc(primes);
  const Z aPrime( primes->getPrime(50) );
  const Z anotherPrime( primes->getPrime(25) );
  int i ;
  for(i = 0; i < list.size()/2; i++){
    list[i] = rnd->getInteger(brand(100,200)) * aPrime;
  }
  for(; i < list.size(); i++){
    list[i] = rnd->getInteger(brand(100,200)) * anotherPrime;
  }


  GCD<Z>* gcd; MethodsFactory::getReference().getFunc(gcd);
  const Z d(gcd->gcd(list));

  GEN u,v,z;
  u = gp_read_str(const_cast<char*>(list[0].toString().c_str()));
  v = gp_read_str(const_cast<char*>(list[1].toString().c_str()));
  z = ggcd(u,v);
  for( int i = 2 ; i < list.size(); i++){
    v = gp_read_str(const_cast<char*>(list[i].toString().c_str()));
    z = ggcd(z, v);
  }

  const std::string pariStr(GENtostr( z ));

  qassertEquals( d.toString(), pariStr );

}



