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
  R::precisionSalida(6);

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
  MatrixR br(SIZEAR, 1);

  for(int i=0; i < m1.getRows(); i++){
    for(int j =0 ; j < m1.getColumns(); j ++){
      m1(i,j) = rnd->getInteger(3); 
      mr(i,j)=R(m1(i,j))/R("3.14");
   }
    br(i,0) = R(rnd->getInteger(3));
 }
 for(int i=0; i < m2.getRows(); i++){
    for(int j =0 ; j < m2.getColumns(); j ++){
      m2(i,j) = rnd->getInteger(3); 
   }
 }



//  MatrixZ b("[4.5; 6.7; 8.9; 7.8]");
  //MatrixZ mat( "[1 2 3; 0 7 5; 0 4 10]");
  MatrixZ mat( "[0 2 3; 0 5 6; 0 8 9]");
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
  //std::cout << mat * MatrixR(mat).invert() << std::endl;
  //std::cout << mat * MatrixZ(mat).invert() << std::endl;
//  std::cout << mat.invert() << std::endl;
//  cout << m1.toString() << " * " << m2.toString() << endl;
//  MatrixZ m3(m1*m2);
//  cout << m3.toString() << endl;
//  cout << m3 << endl;
//  cout << m3 * MatrixZ(m3).invert() << endl;
//  m3.fromString("[5 6 1 2 3; 6 4 1 9 1; 3 1 2 3 4; 8 9 2 1 1 ; 3 5 6 7 9]");
//  cout << m1 << endl;
//  cout << m1.toString() << endl;
//  cout << mr.toString() << endl;
  std::cout << m1.getDeterminant() << std::endl;
//  cout << m3 << endl;
//  cout << m3.toString() << endl;
//  cout << mr.toString() << endl;
//  cout << br.toString() << endl;
//  cout << mr.solveFor( br) << endl;
//  cout << mr* MatrixR(mr).invert() << endl;
//  const MatrixR l(MatrixHelpers::_getL(mr));
//  const MatrixR u(MatrixHelpers::_getU(mr));
//
//  cout << l*u << endl;



//  cout << m1.getDeterminant() << endl;
//  cout << mr << endl;
//  cout << mr.toString() << endl;
//  cout << mr.getDeterminant() << endl;
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
