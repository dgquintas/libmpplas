/*
 * $Id$
 */

#include <set>

#include "GFTest.h"
#include "MethodsFactory.h"
#include "aux.h"


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;

GFTest::GFTest(){
  MethodsFactory::getReference().getFunc(rnd);
  MethodsFactory::getReference().getFunc(primes);

  addTest( GFTest, testGeneratorFromPrimitivePoly);

  addTest( GFTest, testGetElement);

  addTest( GFTest, testAddition);
  addTest( GFTest, testSubstraction);
  addTest( GFTest, testMultiplication);
  addTest( GFTest, testSquare);
  addTest( GFTest, testDivision);

  addTest( GFTest, testInversion);
  addTest( GFTest, testExponentiation);

  addTest( GFTest, testConversions);

  addTest( GFTest, testInput);

}

void GFTest::setUp(){
  const Z p(primes->getPrime(brand(1,5)));
  const int n(brand(1,16));

  gfIrred = new GF(p,n,false);
  gfPrim = new GF(p,n,true);

}
void GFTest::tearDown(){
  delete gfIrred;
  delete gfPrim;
}


void GFTest::testGeneratorFromPrimitivePoly(){

  std::set<GFx> elems;
  const GFx x( gfPrim->getElement("[(1,1)]") );
  for( int i = 0; i < gfPrim->getOrder(); i++){
    elems.insert(x ^ i);
  }

  qassertTrue((gfPrim->getOrder()-1) == elems.size());
}
void GFTest::testGetElement(){}

void GFTest::testAddition(){}
void GFTest::testSubstraction(){}
void GFTest::testMultiplication(){}
void GFTest::testSquare(){}
void GFTest::testDivision(){}

void GFTest::testInversion(){}
void GFTest::testExponentiation(){}

void GFTest::testConversions(){}

void GFTest::testInput(){}
  

