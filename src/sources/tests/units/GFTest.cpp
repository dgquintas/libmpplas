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
  addTest( GFTest, testInversionThrows);

  addTest( GFTest, testExponentiation);

  addTest( GFTest, testConversions);

  addTest( GFTest, testInput);

}

void GFTest::setUp(){
  const Z p(primes->getPrime(brand(1,5)));
  const int n(brand(1,6));

  gfIrred = new GF(p,n,false);

}
void GFTest::tearDown(){
  delete gfIrred;
}


void GFTest::testGeneratorFromPrimitivePoly(){
  const Z p(primes->getPrime(brand(1,3)));
  const int n(brand(1,4));

  GF gfPrim(p,n,true);

  std::set<GFx> elems;
  const GFx x( gfPrim.getElement("[(1,1)]") );
  for( SignedDigit i = 0; i < gfPrim.getOrder(); i++){
    GFx xi(x);
    xi ^= i;
    elems.insert(xi);
  }

  qassertTrue((gfPrim.getOrder()-Z::ONE) == elems.size());

}
void GFTest::testGetElement(){}

void GFTest::testAddition(){
  const Z charact(gfIrred->getCharacteristic());
  GFx one = gfIrred->getElement(Z::ONE);
  GFx accum(one);

  for(Z i = Z::ZERO ; i < charact-Z::ONE ; i++){
    accum += one;
  }

  qassertTrue( accum.getIntegerValue() == Z::ZERO );
}
void GFTest::testSubstraction(){}
void GFTest::testMultiplication(){
//  const GFx lhs(gfIrred->getElement( Z(rnd->getDigit()) ));
//  const GFx rhs(gfIrred->getElement( Z(rnd->getDigit()) ));
//  GFx accum = GFx(rhs);
//
//  const GFx expected( lhs*rhs );
//
//  const Digit times( lhs.getIntegerValue()[0] );
//  std::cout << times << std::endl;
//  for(Digit i = 1; i < times ; i++){
//    accum += rhs;
//    if( (i % 10000) == 0 ){
//      std::cout << i << std::endl;
//    }
//  }
//
//  std::cout << accum << "\n" << expected << std::endl;
//
//  qassertTrue( accum == expected );

}
void GFTest::testSquare(){}
void GFTest::testDivision(){}

void GFTest::testInversion(){
  const Z srcInt( rnd->getDigit() );
  GFx e;
  do{ 
    e = gfIrred->getElement( srcInt );
  } while( e.isZero() );

  const GFx eInv( e.getInverse() );

  const GFx shouldBeOne ( e*eInv );

  const bool res = shouldBeOne == gfIrred->getElement( Z::ONE );
  if( !res ){
    std::cout << gfIrred->toHRString() << std::endl;
    std::cout << srcInt << " " << e << " " << eInv << std::endl;
    std::cout << shouldBeOne << std::endl;
  }
  qassertTrue( res );

}


void GFTest::testInversionThrows(){
  const GFx e( gfIrred->getElement() ); //zero
  try {
    e.getInverse();
  }
  catch( Errors::NonInvertibleElement ){
    return;
  }

  //this point shouldn't be reached 
  qassertTrue(false);
    
}
void GFTest::testExponentiation(){}

void GFTest::testConversions(){}

void GFTest::testInput(){}
  

