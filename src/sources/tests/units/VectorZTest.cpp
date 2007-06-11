/*
 * $Id$
 */

#include "VectorZTest.h"
#include "err.h"
#include <iostream>


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;


VectorZTest::VectorZTest()
{
  addTest(VectorZTest, testInput);
  addTest(VectorZTest, testOperatorAsign);
  addTest(VectorZTest, testCopyConstructor);
  addTest(VectorZTest, testToString);
  
  addTest(VectorZTest, testOperatorAddition);
  addTest(VectorZTest, testOperatorProductWithZ);
  addTest(VectorZTest, testOperatorProductWithVectorZ);

  addTest( VectorZTest, testDot );
  addTest( VectorZTest, testDotNonMember );

  addTest( VectorZTest, testCross );


}

void VectorZTest::setUp(){
  vecA = VectorZ("[1 2 3 4 5 6 7 8 9]");
  vecB = VectorZ("[423 12 54 621 356 31 0 -124 -1]");
  
}
void VectorZTest::tearDown(){
//empty. new is not used
}

void VectorZTest::testInput(){
  VectorZ vec2("[1 2 3 4 5 6 7 8 9]");
  qassertTrue(vecA == vec2);
}
void VectorZTest::testOperatorAsign(){
  VectorZ vec2;
  vec2 = vecA;
  qassertTrue( vec2 == vecA );

}
void VectorZTest::testCopyConstructor(){
  VectorZ vec2(vecA);
  qassertTrue( vec2 == vecA );
}


void VectorZTest::testToString(){
  VectorZ n( vecA.toString() );
  qassertTrue(vecA == n);
}

void VectorZTest::testOperatorAddition(){
  VectorZ res("[424 14 57 625 361 37 7 -116 8]");
  vecA += vecB;
  qassertTrue(vecA == res);
}

void VectorZTest::testOperatorProductWithZ(){
  VectorZ res("[5221935 148140 666630 7666245 4394820 382695 0 -1530780 -12345]");


  vecB *= Z("12345");

  qassertTrue(vecB == res);
}

void VectorZTest::testOperatorProductWithVectorZ(){
  VectorZ res("[423 24 162 2484 1780 186 0 -992 -9]");

  vecA.byElementProd(vecB);

  qassertTrue(vecA == res);
}

void VectorZTest::testDot(){
  Z dotProd(vecA.dot(vecB));

  qassertEquals ( dotProd.toString() , "4058" );

  try{
    VectorZ("[1 2 3]").dot( VectorZ("[1 2]") );
  }
  catch( Errors::NonConformantDimensions& e){
    return;
  }
  qassertTrue(false);

}

void VectorZTest::testDotNonMember(){
  Z dotProd(dot(vecA,vecB));

  qassertEquals ( dotProd.toString() , "4058" );

  try{
    dot( VectorZ("[1 2 3]") ,  VectorZ("[1 2]") );
  }
  catch( Errors::NonConformantDimensions& e){
    return;
  }
  qassertTrue(false);

}

void VectorZTest::testCross(){

  VectorZ a("[ 123 456 789 ]");
  VectorZ b("[ 314 159 265 ]");

  VectorZ res("[-4611 215151 -123627]");

  a.cross(b);

  qassertTrue( a == res );

  return ;
}

