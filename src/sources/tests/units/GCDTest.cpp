/*
 * $Id $
 */

#include <string>
#include "GCDTest.h"
#include "MethodsFactory.h"
#include "aux.h"

using namespace com_uwyn_qtunit;
using namespace std;


GCDTest::GCDTest() {
  addTest(GCDTest, testGCDLehmer);
  addTest(GCDTest, testGCDExtBinario);
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
  const Z res( gcd.gcdext(z1,z2,u,v) );

  string pariStr(GENtostr( resP ));

  string thisStr = res.toString();
  string thisStrU = u.toString();
  string thisStrV = v.toString();

  const Z shouldBeRes(z1*u + z2*v);

  qassertTrue( res == shouldBeRes );
  qassertTrue( pariStr == thisStr );

}
