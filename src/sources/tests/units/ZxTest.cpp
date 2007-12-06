/*
 * $Id$
 */

#include "ZxTest.h"
#include "aux.h"
#include "MethodsFactory.h"

#include <sstream>
#include <algorithm>


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;


ZxTest::ZxTest() {
  addTest(ZxTest, testAddition);
  addTest(ZxTest, testDifference);
  addTest(ZxTest, testProduct);
  addTest(ZxTest, testPseudoDivision);
  addTest(ZxTest, testGCDKnuth);
  addTest(ZxTest, testGCDCollins);
  addTest(ZxTest, testEvaluation);
}

void ZxTest::setUp(){
  MethodsFactory::getReference().getFunc(rnd);

  const int degA = brand(20,30);
  const int degB = brand(20,30);
  const int degC = brand(5,19);
  std::vector<Z> coeffsA(degA);
  std::vector<Z> coeffsB(degB);
  std::vector<Z> coeffsC(degC);

  for(int i = 0 ; i < degA; i += brand(3,6)){
    coeffsA[i] = rnd->getInteger(brand(100,200));
  }
  for(int i = 0 ; i < degB; i += brand(3,6)){
    coeffsB[i] = rnd->getInteger(brand(100,200));
  }
  for(int i = 0 ; i < degC; i += brand(1,2)){
    coeffsC[i] = rnd->getInteger(brand(100,200));
  }

  polA = Zx(coeffsA);
  polB = Zx(coeffsB);
  polC = Zx(coeffsC);

  std::ostringstream oss;
  oss << polA;
  polPariA = gp_read_str( (char*)oss.str().c_str() );
  oss.str("");
  oss << polB;
  polPariB = gp_read_str( (char*)oss.str().c_str() );
  oss.str("");
  oss << polC;
  polPariC = gp_read_str( (char*)oss.str().c_str() );

  
}
void ZxTest::tearDown(){
//empty. new is not used
}



void ZxTest::testAddition(){

  polA += polB;
  GEN polPariC = gadd(polPariA, polPariB);

  qassertEquals( polA.getDegree(), (int)degpol(polPariC) );

  for( int i = 0; i <= degpol(polPariC); i++){
    qassertTrue( polA[i].toString() == std::string(GENtostr((GEN)polPariC[i+2])) );
  }

}

void ZxTest::testDifference(){

  polA -= polB;
  GEN polPariC = gsub(polPariA, polPariB);

  qassertEquals( polA.getDegree(), (int)degpol(polPariC) );

  for( int i = 0; i <= degpol(polPariC); i++){
    qassertEquals( polA[i].toString(), std::string(GENtostr((GEN)polPariC[i+2])) );
  }

}

void ZxTest::testProduct(){
  polA *= polB;
  GEN polPariC = gmul(polPariA, polPariB);

  qassertEquals( polA.getDegree(), (int)degpol(polPariC) );

  for( int i = 0; i <= degpol(polPariC); i++){
    qassertEquals( polA[i].toString(), std::string(GENtostr((GEN)polPariC[i+2])) );
  }
}

void ZxTest::testPseudoDivision(){
  int m = polA.getDegree();
  int n = polB.getDegree();

  if( m < n ){
    std::swap(polA, polB);
    m = polA.getDegree();
    n = polB.getDegree();
  }
  Z lv = polB.getLeadingCoefficient();
  lv ^= (Digit)(m-n+1);
  Zx q,r;
  Zx::divAndMod(polA, polB, &q,&r);

  const Zx rhsres( q*polB + r );
  const Zx lhsres( polA * lv ); 

  qassertEquals( rhsres.toString(), lhsres.toString());

}


void ZxTest::testGCDKnuth(){
  mpplas::GCDPolyKnuth<mpplas::Z> gcd;
  Zx d( gcd.gcd(polA, polB) );
  Zx q,r;
  Zx::divAndMod(polA, d, &q, &r);
  qassertTrue( r.isZero() ); 
  Zx::divAndMod(polB, d, &q, &r);
  qassertTrue( r.isZero() );

  polC *= polA;
  d = gcd.gcd(polA, polC);
  qassertTrue( d == polA );

}
void ZxTest::testGCDCollins(){
  mpplas::GCDPolyCollins<mpplas::Z> gcd;
  Zx d( gcd.gcd(polA, polB) );
  Zx q,r;
  Zx::divAndMod(polA, d, &q, &r);
  qassertTrue( r.isZero() ); 
  Zx::divAndMod(polB, d, &q, &r);
  qassertTrue( r.isZero() );

  polC *= polA;
  d = gcd.gcd(polA, polC);
  qassertTrue( d == polA );


}


void ZxTest::testEvaluation(){
  const Z x0(rnd->getInteger(brand(100,200)));
  const Z res( polA.evaluate(x0) );
  
  GEN x0Pari = gp_read_str( (char*)x0.toString().c_str() );
  GEN risEveni = poleval(polPariA, x0Pari);

  qassertEquals( res.toString(), std::string( GENtostr(risEveni) ) );
}


