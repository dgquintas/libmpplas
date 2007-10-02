#include "MatrixZ.h"

namespace mpplas
{
  MatrixZ::MatrixZ()
    : Matrix<Z>()
  {}
  MatrixZ::MatrixZ(const int nAndm)
    : Matrix<Z>(nAndm) 
  {}
  MatrixZ::MatrixZ(const int n, const int m)
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
  

