/*
 * $Id$
 */

#include "MatrixRTest.h"
#include <iostream>


using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;


MatrixRTest::MatrixRTest()
{
  addTest(MatrixRTest, testTranspose);
  addTest(MatrixRTest, testOperatorAsign);
  addTest(MatrixRTest, testCopyConstructor);
  addTest(MatrixRTest, testToString);
  addTest(MatrixRTest, testSetDiagonal);

}

void MatrixRTest::setUp(){
  mat = MatrixR("[1.347643 2 0.3; 43523.21 5.8476598734658746937593483534 6.12352352; 7.1 8.2 9.3]");
  
}
void MatrixRTest::tearDown(){
//empty. new is not used
}

void MatrixRTest::testTranspose(){
  MatrixR matT("[1.347643 43523.21 7.1; 2 5.8476598734658746937593483534 8.2; 0.3 6.12352352 9.3]");
  mat.transpose();
  qassertTrue(mat == matT);
}
void MatrixRTest::testOperatorAsign(){
  MatrixR mat2;
  mat2 = mat;
  qassertTrue( mat2 == mat );

}
void MatrixRTest::testCopyConstructor(){
  MatrixR mat2(mat);
  qassertTrue( mat2 == mat );
}


void MatrixRTest::testToString(){
  MatrixR n( mat.toString() );
  qassertTrue(mat == n);
}


void MatrixRTest::testSetDiagonal(){
  MatrixR id(3,3);
  id.setDiagonal((Cifra)1.2345);
  
  MatrixR realId("[1.2345 0 0; 0 1.2345 0; 0 0 1.2345]");
  qassertTrue(id == realId);

}
