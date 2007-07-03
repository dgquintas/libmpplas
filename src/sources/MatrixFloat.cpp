#include "MatrixFloat.h"
#include "kernel.h"

namespace mpplas
{
  MatrixFloat::MatrixFloat()
    : Matrix<SIMDDigit>()
  {}

  MatrixFloat::MatrixFloat(const MatrixFloat& m)
    : Matrix<SIMDDigit>(m)
  {}
  MatrixFloat::MatrixFloat(const Matrix<SIMDDigit>& m)
    : Matrix<SIMDDigit>(m)
  {}



  MatrixFloat::MatrixFloat(const size_t nAndm)
    : Matrix<SIMDDigit>(nAndm) {}
  MatrixFloat::MatrixFloat(const size_t n, const size_t m)
    : Matrix<SIMDDigit>(n,m) {}

  //////////////////////////////////////////////
  
  
  
  //////////////////////////////////////////////

  MatrixFloat operator-(MatrixFloat m){
//    m *= ((SignedDigit)-1);
    return m;
  }

  std::istream& operator>>(std::istream& is, MatrixFloat& m){
    std::cout << "bla" << std::endl;
    return is;
  }


  MatrixFloat::MatrixFloat(const std::string& str){
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

}
  

