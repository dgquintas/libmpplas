#include "Matrix.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){

  Matrix<int> mat("[1324 21 3; 4 5 6; -753442 8 9]");

  cout << mat;

  cout << endl;
  mat.transpose();

  cout << mat;


  return 0;
}
