#include "MatrixGFx.h"

namespace mpplas{

  MatrixGFx::MatrixGFx()
    : Matrix<GFx>()  {}

  MatrixGFx::MatrixGFx(const int nAndm)
    : Matrix<GFx>(nAndm)  {}

  MatrixGFx::MatrixGFx(const int n, const int m)
    : Matrix<GFx>(n,m)  {}

  MatrixGFx::MatrixGFx(const Dimensions& dims)
    : Matrix<GFx>(dims)  {}
  
  MatrixGFx::MatrixGFx(const MatrixGFx& m)
    : Matrix<GFx>(m)  {}
  
  MatrixGFx::MatrixGFx(const Matrix<GFx>& m)
    : Matrix<GFx>(m)  {}
  
  MatrixGFx::MatrixGFx(const std::string& str)
    : Matrix<GFx>(str)  {}
  

  MatrixGFx& MatrixGFx::operator=(const MatrixGFx& src){
    Matrix<GFx>::operator=(src);
    return *this;
  }



}
  

