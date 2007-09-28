#include "MatrixZ.h"
#include "omp_mock.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){

  cout << omp_get_max_threads() << endl;

  MatrixZ mat(
  "[ 1    2    3    4 ;" 
  "  8    9   10   11 ;"
  " 15   16   17   18 ;"
  " 22   23   24   25 ;"
  " 29   30   31   32 ;"
  " 36   37   38   39 ;"
  " 43   44   45   46  ]"
  );

  cout << mat << endl;
 
  mat.transpose();
  cout << mat << endl;
  mat.transpose();
  cout << mat << endl;

  MatrixZ sqr( "[1 2 3; 4 5 6; 7 8 9]" );
  cout << sqr << endl;
  cout << transpose(sqr) << endl;
  sqr.transpose();
  cout << sqr << endl;




  return 0;
}
