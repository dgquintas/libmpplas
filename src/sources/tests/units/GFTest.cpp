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
  const int n(brand(1,8));

  gfIrred = new GF(p,n,false);

}
void GFTest::tearDown(){
  delete gfIrred;
}


void GFTest::testGeneratorFromPrimitivePoly(){
  const Z p(primes->getPrime(brand(1,4)));
  const int n(brand(1,4));
 
  std::cout << p << " " << n << std::endl;

  GF gfPrim(p,n,true);

  std::cout << gfPrim.toHRString() << std::endl;

  std::set<GFx> elems;
  const GFx x( gfPrim.getElement("[(1,1)]") );
  for( int i = 0; i < gfPrim.getOrder(); i++){
    GFx xi(x);
    xi ^= i;
    elems.insert(xi);
  }

  std::cout << elems.size() << std::endl;

  qassertTrue((gfPrim.getOrder()-1) == elems.size());

}
void GFTest::testGetElement(){}

void GFTest::testAddition(){
  const Z charact(gfIrred->getCharacteristic());
  GFx one = gfIrred->getElement(Z::ONE);
  GFx accum(one);

  for(Z i = 0 ; i < charact-1 ; i++){
    accum += one;
  }

  qassertTrue( accum.getIntegerValue() == Z::ZERO );
}
void GFTest::testSubstraction(){}
void GFTest::testMultiplication(){
  const GFx lhs(gfIrred->getElement( Z(rnd->getDigit()) ));
  const GFx rhs(gfIrred->getElement( Z(rnd->getDigit()) ));
  GFx accum = GFx(rhs);

  const GFx expected( lhs*rhs );

  const Digit times( lhs.getIntegerValue()[0] );
  std::cout << times << std::endl;
  for(Digit i = 1; i < times ; i++){
    accum += rhs;
    if( (i % 10000) == 0 ){
      std::cout << i << std::endl;
    }
  }

  std::cout << accum << "\n" << expected << std::endl;

  qassertTrue( accum == expected );

}
void GFTest::testSquare(){}
void GFTest::testDivision(){}

void GFTest::testInversion(){
  const GFx e(gfIrred->getElement( Z(rnd->getDigit()) ));
  const GFx eInv( e.getInverse() );

  const GFx shouldBeOne ( e*eInv );

  qassertTrue( shouldBeOne == gfIrred->getElement( Z::ONE ) );

}
void GFTest::testExponentiation(){}

void GFTest::testConversions(){}

void GFTest::testInput(){}
  

