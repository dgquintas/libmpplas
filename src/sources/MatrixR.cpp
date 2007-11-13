#include "MatrixR.h"

namespace mpplas
{



  MatrixR::MatrixR()
    : Matrix<R>()  {}

  MatrixR::MatrixR(const int nAndm)
    : Matrix<R>(nAndm)  {}

  MatrixR::MatrixR(const int n, const int m)
    : Matrix<R>(n,m)  {}

  MatrixR::MatrixR(const Dimensions& dims)
    : Matrix<R>(dims)  {}
  
  MatrixR::MatrixR(const MatrixR& m)
    : Matrix<R>(m)  {}
  
  MatrixR::MatrixR(const Matrix<R>& m)
    : Matrix<R>(m)  {}
  
  MatrixR::MatrixR(const std::string& str)
    : Matrix<R>(str)  {}
  

  MatrixR& MatrixR::operator=(const MatrixR& src){
    Matrix<R>::operator=(src);
    return *this;
  }


}
  

