#include "MatrixFloat.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){

  MatrixFloat mat("[13.24 2.1 3;" 
                    "4     5   6;" 
                    "-75.3442 8.0 9]");

  MatrixFloat mat2("[3.24 2 -1;" 
                    "6.6     1.5   26;" 
                    "-735.3442 81.10 39]");


  cout << mat << endl;
  cout << mat2 << endl;
  cout << mat + mat2  << endl;
  cout << mat - mat2  << endl;
  cout << mat * mat2  << endl;

//  mat + mat2;

  return 0;
}
