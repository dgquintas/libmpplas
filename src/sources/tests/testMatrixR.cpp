#include "MatrixR.h"
#include <iostream>


using namespace mpplas;
using namespace std;


int main(){

  MatrixR mat("[1324.1 21 3.35236; 4.111 5.222 0.6; -75345.3253232522342 82325232235626234.1 9.122]");

  cout << mat << endl;

  MatrixR mat2(mat);

  cout << mat2 << endl;

  mat2.transpose();
  mat2.transpose();

  cout << (mat == mat2) << endl;

//  MatrixR mat3( mat.toString() );
//  MatrixR mat3( "[1324.1 21 3.35236; 4.111 5.222 0.6; -75345.3253232522342 82325232235626234.1 9.122]");

//"[1324.1 21 3.35236; 4.111 5.222 0.6; -75345.3253232522342 82325232235626234.1 9.122]"

  cout << mat.toString() << endl;

//  cout << mat3 << endl;

//  cout << (mat == mat3) << endl;



  return 0;
}
