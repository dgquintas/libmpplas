#include "MatrixZ.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){
  Matrix<int> mat("[1 2 3 4 ; 5 6 7 8; 9 10 11 12 ; 13 14 15 16 ]");
  Matrix<int> mat2(mat);

  mat *= mat2;
  cout << mat << endl;


  return 0;
}
