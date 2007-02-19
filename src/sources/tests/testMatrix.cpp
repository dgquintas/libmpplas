#include "Matrix.h"
#include "R.h"
#include <iostream>


using namespace numth;
using namespace std;


int main(){

  Matrix<R> mat("[1.324 2.1 3; 4 5 6; -753453253232522.342 8 9]");

  cout << mat;

  cout << endl;
  mat.transpose();

  cout << mat;


  return 0;
}
