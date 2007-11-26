#include "MatrixR.h"
#include <iostream>
#include "Profiling.h"
#include "Random.h"
#include "MethodsFactory.h"
#include "omp_mock.h"


using namespace mpplas;
using namespace std;


int main(){


  Profiling& prof( Profiling::getReference() );
  R::precisionSalida(6);

  //MatrixR mat("[1.31 12.2 43.35 331.1; 4 1.4 35.55 66.61; 7 3.74 18.18 19.9 ; 1 2 3 4]");
  RandomFast* rnd;
  MethodsFactory::getReference().getFunc(rnd);
  rnd->setSeed(Z::ZERO);
  MatrixR mat(100,100);

  for(int i=0; i < mat.getRows(); i++){
    for(int j =0 ; j < mat.getColumns(); j ++){
      mat(i,j) = R(rnd->getInteger(32)); 
      mat(i,j) /= R(rnd->getInteger(23));
    }
  }
//  MatrixR b("[4.5; 6.7; 8.9; 7.8]");
//  MatrixR mat3( "[1324.1 21 3.35236; 4.111 5.222 0.6; -75345.3253232522342 82325232235626234.1 9.122]");
//  MatrixR foo;
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
  prof.reset();
  prof.startClock();
  mat.invert();
  cout <<  prof.getResults() << endl;
  cout <<  prof.getResults().getTotalOps() << endl;
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
