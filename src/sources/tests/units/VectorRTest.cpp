/*
 * $Id: VectorRTest.cpp 254 2007-04-11 18:37:15Z dgquintas $
 */

#include "VectorRTest.h"
#include <iostream>


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;


VectorRTest::VectorRTest()
{
  addTest(VectorRTest, testInput);
  addTest(VectorRTest, testOperatorAsign);
  addTest(VectorRTest, testCopyConstructor);
  addTest(VectorRTest, testToString);
  
  addTest(VectorRTest, testOperatorAddition);
  addTest(VectorRTest, testOperatorProductWithR);
//  addTest(VectorRTest, testOperatorProductWithVectorR);

  addTest( VectorRTest, testDot );
  addTest( VectorRTest, testCross );

}

void VectorRTest::setUp(){
  vecA = VectorR("[1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9]");
  vecB = VectorR("[423.235253232 12.1513 54.3252 621.43422435 356.4642134 31.3652 0.352 -124.43663452343 -1.0]");
  
}
void VectorRTest::tearDown(){
//empty. new is not used
}

void VectorRTest::testInput(){
  VectorR vec2("[1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9]");
  qassertTrue(vecA == vec2);
}
void VectorRTest::testOperatorAsign(){
  VectorR vec2;
  vec2 = vecA;
  qassertTrue( vec2 == vecA );

}
void VectorRTest::testCopyConstructor(){
  VectorR vec2(vecA);
  qassertTrue( vec2 == vecA );
}


void VectorRTest::testToString(){
  VectorR n( vecA.toString() );
  qassertTrue(vecA == n);
}

void VectorRTest::testOperatorAddition(){
  VectorR res("[424.3352532320000    14.35130000000000    57.62520000000000   625.83422435000000 "
      "361.9642134000000    37.96520000000000     8.05200000000000  -115.63663452343000     8.90000000000000  ]");
  vecA += vecB;

  for( int i = 0; i < vecB.getSize() ; i++ ){
    qassertEquals(res(i).toString(5) , vecA(i).toString(5));
  }

}

void VectorRTest::testOperatorProductWithR(){
  VectorR res("[5225121.07582769170    150015.89126579999    670680.77458319999   7672019.37479416654 "
      "4400788.11958912387    387224.28322320001 "
      "4345.67443200000  -1536253.12799033592    -12345.66600000000]");

  vecB *= R("12345.666");

  for( int i = 0; i < vecB.getSize() ; i++ ){
    qassertEquals(res(i).toString(5),vecB(i).toString(5) );
  }
}

void VectorRTest::testOperatorProductWithVectorR(){
  VectorR res("[423       24      162       2484     1780     186     0    -992        -9]");

//  VectorR res("[5221935 148140 666630 7666245 4394820 382695 0 -1530780 -12345]");
  vecA *= vecB;

  qassertTrue(vecA == res);
}

void VectorRTest::testDot(){
  R dotProd(vecA.dot(vecB));

  qassertEquals( "4471.2068955890",dotProd.toString(10) );

  try{
    VectorR("[1 2 3]").dot( VectorR("[1 2]") );
  }
  catch( Errors::NonConformantDimensions& e){
    return;
  }
  qassertTrue(false);

}

void VectorRTest::testCross(){

  VectorR a("[ 1.23 4.56 78.9435 ]");
  VectorR b("[ 3.1325321134 1.59 2.65 ]");

  VectorR res("[ -113.4361650000000   244.0335488941929   -12.3286464371040 ] ");

  a.cross(b);
 
  for( int i = 0; i < a.getSize() ; i++ ){
    qassertEquals(res(i).toString(10),a(i).toString(10) );
  }

  return ;
}
