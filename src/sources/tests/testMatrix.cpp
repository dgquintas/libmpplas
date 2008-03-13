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


  MatrixZ mat2(
  "[ 1    2    3    4 ;" 
  "  8    9   10   11 ;"
  " 43   44   45   46  ]"
  );
 
  MatrixZ mat3(
  "[ 1    2   ;" 
  "  8    9   ;"
  " 15   16   ;"
  " 22   23   ;"
  " 29   30   ;"
  " 36   37   ;"
  " 43   44    ]"
  );



  cout << mat << endl;
  cout << mat(Range(2,2,4), Range(1,2)) << endl;

//  mat.appendByColumns(mat2);
  mat.appendByRows(mat3).appendByRows(mat3);

  cout << mat << endl;
 
  return 0;
}
