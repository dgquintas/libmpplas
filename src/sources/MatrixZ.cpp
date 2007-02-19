#include "MatrixZ.h"

namespace numth
{
  MatrixZ::MatrixZ()
    : Matrix<Z>()
  {}

  MatrixZ::MatrixZ(const MatrixZ& m)
    : Matrix<Z>(m)
  {}

  MatrixZ::MatrixZ(const Matrix<Z>& m)
    : Matrix<Z>(m)
  {}


  MatrixZ::MatrixZ(const size_t nAndm)
    : Matrix<Z>(nAndm) {}
  MatrixZ::MatrixZ(const size_t n, const size_t m)
    : Matrix<Z>(n,m) {}


  MatrixZ::MatrixZ(const std::string& str){
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

}
  

