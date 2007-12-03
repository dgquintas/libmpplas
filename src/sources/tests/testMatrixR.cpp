#include "MatrixZ.h"
#include "MatrixR.h"
#include <iostream>
#include "Profiling.h"
#include "Random.h"
#include "MethodsFactory.h"
#include "omp_mock.h"
#include <cstdlib>


using namespace mpplas;
using namespace std;


int main(int argc, char** argv){


  Profiling& prof( Profiling::getReference() );
//  R::precisionSalida(3);

  RandomFast* rnd;
  MethodsFactory::getReference().getFunc(rnd);
  rnd->setSeed(Z::ZERO);
  const int SIZEAR = atoi(argv[1]);
  const int SIZEAC = atoi(argv[2]);
  const int SIZEBR = atoi(argv[3]);
  const int SIZEBC = atoi(argv[4]);

//  MatrixZ m1("[ 29 20 15 5 ; 21 0 24 21 ; 10 17 10 6 ; 29 30 1 10 ; 16 18 30 7 ; 28 17 19 27  ]");
//  MatrixZ m2("[ 20 20 16 21 18 ; 19 13 31 23 23 ; 20 2 1 12 12 ; 5 8 9 7 29  ]");
 
  MatrixZ m1(SIZEAR, SIZEAC);
  MatrixZ m2(SIZEBR, SIZEBC);
  MatrixR mr(SIZEAR, SIZEAC);

  for(int i=0; i < m1.getRows(); i++){
    for(int j =0 ; j < m1.getColumns(); j ++){
      m1(i,j) = rnd->getInteger(3); 
      mr(i,j)=R(rnd->getInteger(3));
   }
 }
 for(int i=0; i < m2.getRows(); i++){
    for(int j =0 ; j < m2.getColumns(); j ++){
      m2(i,j) = rnd->getInteger(3); 
   }
 }



//  MatrixZ b("[4.5; 6.7; 8.9; 7.8]");
//  MatrixZ mat3( "[1324.1 21 3.35236; 4.111 5.222 0.6; -75345.3253232522342 82325232235626234.1 9.122]");
//  MatrixZ foo;
//
//  cout << (mat * mat3) << endl;
//
//  foo = mat;
//  cout << foo << endl;
//


 //  std::cout << b << std::endl;
//  prof.reset();
//  std::cout << MatrixHelpers::solve(mat,b) << std::endl;

//  cout <<  prof.getResults() << endl;
  prof.startClock();
  //std::cout << mat * MatrixZ(mat).invert() << std::endl;
//  mat.invert();
  cout << m1.toString() << " * " << m2.toString() << endl;
  MatrixZ m3(m1*m2);
  cout << m3.toString() << endl;
  cout << m3 << endl;
//  cout << m3 * MatrixZ(m3).invert() << endl;
//  m3.fromString("[5 6 1 2 3; 6 4 1 9 1; 3 1 2 3 4; 8 9 2 1 1 ; 3 5 6 7 9]");
  cout << m1 << endl;
  cout << m1.toString() << endl;
//  cout << MatrixHelpers::DodgsonCondensation::getDodgsonDeterminant(m3) << endl;
//  MatrixHelpers::DodgsonCondensation::_pivot(m3, m3.getRows());
//  cout << m3 << endl;
//  cout << m3.toString() << endl;
  cout << m1.getDeterminant() << endl;
  cout << mr.toString() << endl;
  cout << mr.getDeterminant() << endl;
//  cout <<  prof.getResults().getTotalOps() << endl;
  cout <<  prof.stopClock()  << endl;
  //
  //
  //
  //  cout << mat << endl;
//  MatrixHelpers::makeCroutsCombinedMatrix(mat);
//  cout << mat << endl;
//
//
//

//  for(int i = 0; i < 3 ; i++){
//    for(int j=0; j < i; j++){
//      l(i,j) = M(i,j);
//    }
//    l(i,i) = R::ONE;
//  }
//  for(int i = 0; i < 3 ; i++){
//    for(int j=i; j < 3; j++){
//      u(i,j) = M(i,j);
//    }
//  }
////
//  std::cout << l << std::endl;
//  std::cout << u << std::endl;
//  std::cout << ((l*u)-Morig) << std::endl;

//  MatrixHelpers::forwardSubstitution(l, b);
//  MatrixHelpers::backwardSubstitution(r, b);




  return 0;
}
