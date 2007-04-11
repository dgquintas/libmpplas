#include "MatrixFloat.h"

namespace mpplas
{
  MatrixFloat::MatrixFloat()
    : Matrix<float>()
  {}

  MatrixFloat::MatrixFloat(const MatrixFloat& m)
    : Matrix<float>(m)
  {}
  MatrixFloat::MatrixFloat(const Matrix<float>& m)
    : Matrix<float>(m)
  {}



  MatrixFloat::MatrixFloat(const size_t nAndm)
    : Matrix<float>(nAndm) {}
  MatrixFloat::MatrixFloat(const size_t n, const size_t m)
    : Matrix<float>(n,m) {}

  //////////////////////////////////////////////
  
  
  
  //////////////////////////////////////////////

  MatrixFloat operator-(MatrixFloat m){
//    m *= ((CifraSigno)-1);
    return m;
  }


  MatrixFloat::MatrixFloat(const std::string& str){
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

}
  

