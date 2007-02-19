/*
 * $Id$
 */

#include "VectorZTest.h"
#include <iostream>


using namespace std;
using namespace numth;
using namespace com_uwyn_qtunit;


VectorZTest::VectorZTest()
{
  addTest(VectorZTest, testInput);
  addTest(VectorZTest, testOperatorAsign);
  addTest(VectorZTest, testCopyConstructor);
  addTest(VectorZTest, testToString);
  
  addTest(VectorZTest, testOperatorAddition);
  addTest(VectorZTest, testOperatorProduct);

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

void VectorZTest::testOperatorProduct(){
  VectorZ res("[5221935 148140 666630 7666245 4394820 382695 0 -1530780 -12345]");


  vecB *= Z("12345");

  qassertTrue(vecB == res);
}


