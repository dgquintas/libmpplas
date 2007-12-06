/*
 * $Id$
 */


#include "MatrixRTest.h"
#include "aux.h"

using namespace mpplas;
using namespace com_uwyn_qtunit;


MatrixRTest::MatrixRTest()
  : funcs( MethodsFactory::getReference() )
{

  funcs.getFunc(rnd) ;

  addTest(MatrixRTest, testInverse);
  addTest(MatrixRTest, testSolve);

}

void MatrixRTest::setUp(){
  
  const int n = brand(10,20);
  const int m = n;

  const int elemsSize = brand(50, 100);

  _A = MatrixR( n,m );
  _b = MatrixR( n,1);

  for( int i = 0; i < _A.getSize(); i++ ){
    _A(i) = R(rnd->getInteger(elemsSize));
    _A(i) /= R(rnd->getInteger(elemsSize/brand(2,5)));
  }

  for( int i = 0; i < n; i++ ){
    _b(i) = R(rnd->getInteger((elemsSize)));
    _b(i) /= R(rnd->getInteger(elemsSize/brand(2,5)));
  }
}

void MatrixRTest::tearDown(){
//empty. new is not used
}

void MatrixRTest::testInverse(){
  const MatrixR id( _A * MatrixR(_A).invert());
  const R thr("0.00000000001");
  for(int i = 0; i < id.getRows(); i++){
    qassertTrue( mpplas::abs(R::ONE - id(i,i)) < thr );
  }

}

void MatrixRTest::testSolve(){

  const MatrixR y(MatrixHelpers::solve(_A,_b));
  std::cout << _b << std::endl;
  _A *= y;
  std::cout << _A << std::endl;

  for(int i=0; i < y.getSize(); i++){
    qassertEquals( _b(i).toString(),_A(i).toString() );
  }

}


