#include "MatrixZ.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){
  MatrixZ mat("[1 -235; 2 -34; 5 6]");
  MatrixZ mat2("[1 2 3; 4 64 -12]");

  mat *= mat2;
  cout << mat << endl;

  return 0;
}
