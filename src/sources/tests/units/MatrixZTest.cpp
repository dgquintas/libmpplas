/*
 * $Id$
 */

#include "MatrixZTest.h"
#include <iostream>


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;


MatrixZTest::MatrixZTest()
{
  addTest(MatrixZTest, testTranspose);
  addTest(MatrixZTest, testInput);
  addTest(MatrixZTest, testOperatorAsign);
  addTest(MatrixZTest, testCopyConstructor);
  addTest(MatrixZTest, testToString);
  addTest(MatrixZTest, testSetDiagonal);

}

void MatrixZTest::setUp(){
  mat = MatrixZ("[1 2 3; 4 5 6; 7 8 9]");
  
}
void MatrixZTest::tearDown(){
//empty. new is not used
}

void MatrixZTest::testTranspose(){
  MatrixZ matT("[1 4 7; 2 5 8; 3 6 9]");
  mat.transpose();
  qassertTrue(mat == matT);
}
void MatrixZTest::testInput(){
  MatrixZ mat2("[1 2 3; 4 5 6; 7 8 9]");
  qassertTrue(mat == mat2);
}
void MatrixZTest::testOperatorAsign(){
  MatrixZ mat2;
  mat2 = mat;
  qassertTrue( mat2 == mat );

}
void MatrixZTest::testCopyConstructor(){
  MatrixZ mat2(mat);
  qassertTrue( mat2 == mat );
}


void MatrixZTest::testToString(){
  MatrixZ n( mat.toString() );
  qassertTrue(mat == n);
}


void MatrixZTest::testSetDiagonal(){
  MatrixZ id(3,3);
  id.setDiagonal((Cifra)1);
  
  MatrixZ realId("[1 0 0; 0 1 0; 0 0 1]");
  qassertTrue(id == realId);

}
