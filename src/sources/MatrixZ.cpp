#include "MatrixZ.h"

namespace mpplas
{
  MatrixZ::MatrixZ()
    : Matrix<Z>()
  {}
  MatrixZ::MatrixZ(const size_t nAndm)
    : Matrix<Z>(nAndm) 
  {}
  MatrixZ::MatrixZ(const size_t n, const size_t m)
    : Matrix<Z>(n,m) 
  {}
  MatrixZ::MatrixZ(const Dimensions& dims)
    : Matrix<Z>(dims)
  {}
  MatrixZ::MatrixZ(const MatrixZ& m)
    : Matrix<Z>(m)
  {}
  MatrixZ::MatrixZ(const Matrix<Z>& m)
    : Matrix<Z>(m)
  {}
  MatrixZ::MatrixZ(const std::string& str)
    : Matrix<Z>(str)
  {}




  ////////////////////////////////////////////////
  
  
  
  
  
  
  
  
  
  ////////////////////////////////////////////////
  



}
  

