#include "MatrixZ.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){
  Matrix<int> mat1("[1 2 3; 4 5 6; 7 8 9]");
  Matrix<int> mat2("[7 4 8 ; 5 9 2; 8 1 0]");

  Matrix<int> mat3("[1 2 3 4 ; 5 6 7 8; 9 10 11 12 ; 13 14 15 16; 17 18 19 20 ]");
  Matrix<int> mat4("[12 23 34 41 1; 45 66 71 83 2; 69 180 121 122 3; 1 41 5 116 4]");
//  Matrix<int> mat("[1 2 3 4 1 2 3 4; 5 6 7 8 1 2 3 4; 9 10 11 12 1 2 3 4; 13 14 15 16 1 2 3 4; 1 2 3 4 1 2 3 4; 5 6 7 8 1 2 3 4; 9 10 11 12 1 2 3 4;    13 14 15 16 1 2 3 4]");
//  Matrix<int> mat2("[12 23 34 41  45 66 71 83; 69 180 121 122 1 41 5 116 ;1 2 3 4  5 6 7 8; 9 10 11 12 13 14 15 16; 12 23 34 41  45 66 71 83; 69 180 121 122 1 41 5 116 ;1 2 3 4  5 6 7 8; 9 10 11 12 13 14 15 16]");


  std::cout << mat3 << std::endl;
  std::cout << mat3(0,3,1,2) << std::endl;

  cout << mat1 * mat2 << endl;
  cout << mat3 * mat4 << endl;

  cout << mat1.toString()  << endl;

  return 0;
}
