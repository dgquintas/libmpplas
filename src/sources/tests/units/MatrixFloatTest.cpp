/*
 * $Id$
 */

#include "MatrixDoubleTest.h"
#include <iostream>


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;


MatrixDoubleTest::MatrixDoubleTest()
{
  addTest(MatrixDoubleTest, testTranspose);
  addTest(MatrixDoubleTest, testOperatorAsign);
  addTest(MatrixDoubleTest, testCopyConstructor);
  addTest(MatrixDoubleTest, testToString);
  addTest(MatrixDoubleTest, testSetDiagonal);

}

void MatrixDoubleTest::setUp(){
  mat = MatrixDouble("[1.347643 2 0.3; 43523.21 5.84765 6.12352352; 7.1 8.2 9.3]");
  
}
void MatrixDoubleTest::tearDown(){
//empty. new is not used
}

void MatrixDoubleTest::testTranspose(){
  MatrixDouble matT("[1.347643 43523.21 7.1; 2 5.84765 8.2; 0.3 6.12352352 9.3]");
  mat.transpose();
  qassertTrue(mat == matT);
}
void MatrixDoubleTest::testOperatorAsign(){
  MatrixDouble mat2;
  mat2 = mat;
  qassertTrue( mat2 == mat );

}
void MatrixDoubleTest::testCopyConstructor(){
  MatrixDouble mat2(mat);
  qassertTrue( mat2 == mat );
}


void MatrixDoubleTest::testToString(){
  MatrixDouble n( mat.toString() );
  qassertTrue(mat == n);
}


void MatrixDoubleTest::testSetDiagonal(){
  MatrixDouble id(3,3);
  id.setDiagonal(1.2345);
  
  MatrixDouble realId("[1.2345 0 0; 0 1.2345 0; 0 0 1.2345]");
  qassertTrue(id == realId);

}
