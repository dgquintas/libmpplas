#include "MatrixR.h"

namespace mpplas
{
  MatrixR::MatrixR()
    : Matrix<R>()
  {}

  MatrixR::MatrixR(const MatrixR& m)
    : Matrix<R>(m)
  {}
  MatrixR::MatrixR(const Matrix<R>& m)
    : Matrix<R>(m)
  {}



//TODO
//  MatrixR::MatrixR(const Matrix<Z>& m)
//    : Matrix<R>(m)
//  {}



  MatrixR::MatrixR(const size_t nAndm)
    : Matrix<R>(nAndm) {}
  MatrixR::MatrixR(const size_t n, const size_t m)
    : Matrix<R>(n,m) {}

  //////////////////////////////////////////////
  
  
  
  //////////////////////////////////////////////


}
  

