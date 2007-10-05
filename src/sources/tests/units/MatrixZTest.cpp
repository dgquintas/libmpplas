/*
 * $Id$
 */


#include "MatrixZTest.h"
#include "aux.h"

#include <pari/pari.h>

using namespace mpplas;
using namespace com_uwyn_qtunit;


MatrixZTest::MatrixZTest()
  : funcs( MethodsFactory::getReference() )
{

  funcs.getFunc(rnd) ;

  addTest(MatrixZTest, testTranspose);
  addTest(MatrixZTest, testInput);
  addTest(MatrixZTest, testOperatorAsign);
  addTest(MatrixZTest, testCopyConstructor);
  addTest(MatrixZTest, testToString);
  addTest(MatrixZTest, testSetDiagonal);
  addTest(MatrixZTest, testProduct);

}

void MatrixZTest::setUp(){
  
  const int n = brand(100,200);
  const int m = brand(100,200);
  const int k = brand(100,200);

  const int elemsSize = brand(50, 100);

  _A = MatrixZ( n,m );
  _B = MatrixZ( m,k );

  for( int i = 0; i < _A.getSize(); i++ ){
    _A(i) = rnd->getInteger(elemsSize);
  }
  for( int i = 0; i < _B.getSize(); i++ ){
    _B(i) = rnd->getInteger(elemsSize);
  }
}

void MatrixZTest::tearDown(){
//empty. new is not used
}

void MatrixZTest::testTranspose(){
  MatrixZ matT(_A);
  matT.transpose();

  for(int i=0; i < _A.getRows() ; i++){
    for(int j=0; j < _A.getColumns(); j++){
      qassertEquals(_A(i,j).toString(), matT(j,i).toString());
    }
  }
}
void MatrixZTest::testInput(){
  MatrixZ mat1(3,3);
  Z k(Z::ONE);
  for(int i=0; i < mat1.getRows(); i++){
    for(int j=0; j < mat1.getColumns(); j++){
      mat1(i,j) = k;
      k++;
    }
  }
  MatrixZ mat2("[1 2 3; 4 5 6; 7 8 9]");
  qassertTrue(mat1 == mat2);
}
void MatrixZTest::testOperatorAsign(){
  MatrixZ mat2;
  mat2 = _A;
  qassertTrue( mat2 == _A );

}
void MatrixZTest::testCopyConstructor(){
  MatrixZ mat2(_A);
  qassertTrue( mat2 == _A );
}


void MatrixZTest::testToString(){
  MatrixZ n( _A.toString() );
  qassertTrue(_A == n);
}


void MatrixZTest::testSetDiagonal(){
  _A.setAll(Z::ZERO);
  _A.setDiagonal(Z::ONE);
  
  const int sentry = _A.getRows() > _A.getColumns() ? _A.getColumns() : _A.getRows();

  for(int i=0; i < sentry ; i++){
    qassertTrue( _A(i,i) == Z::ONE );
  }
}

void MatrixZTest::testProduct(){
  GEN _Apari, _Bpari, Cpari;
  _Apari = zeromatcopy( _A.getRows(), _A.getColumns() );
  _Bpari = zeromatcopy( _B.getRows(), _B.getColumns() );

  for( int i = 0; i < _A.getRows() ; i++){
    for( int j = 0; j < _A.getColumns() ; j++){
      gcoeff( _Apari, i+1,j+1) = gp_read_str( (char*)_A(i,j).toString().c_str() );
    }
  }
  for( int i = 0; i < _B.getRows() ; i++){
    for( int j = 0; j < _B.getColumns() ; j++){
      gcoeff( _Bpari, i+1,j+1) = gp_read_str( (char*)_B(i,j).toString().c_str() );
    }
  }

  Cpari = gmul(_Apari, _Bpari); 
  const MatrixZ C( _A * _B );

  for( int i = 0; i < C.getRows() ; i++){
    for( int j = 0; j < C.getColumns() ; j++){
      qassertEquals( GENtostr( gcoeff( Cpari, i+1,j+1) ), C(i,j).toString());
    }
  }

}
