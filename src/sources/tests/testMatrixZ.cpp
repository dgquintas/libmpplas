#include "MatrixZ.h"
#include <iostream>


using namespace numth;
using namespace std;


int main(){

  MatrixZ mat(3,3);

  cin >> mat;


  cout << mat;

  cout << endl;
  mat.setNumberColumns(2);

  cout << mat;


  return 0;
}
