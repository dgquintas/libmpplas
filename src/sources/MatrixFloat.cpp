#include "MatrixFloat.h"
#include "kernelSIMD.h"

namespace mpplas
{
  MatrixFloat::MatrixFloat()
    : Matrix<__m128>()
  {}

  MatrixFloat::MatrixFloat(const MatrixFloat& m)
    : Matrix<__m128>(m)
  {}
  MatrixFloat::MatrixFloat(const Matrix<__m128>& m)
    : Matrix<__m128>(m)
  {}



  MatrixFloat::MatrixFloat(const size_t nAndm)
    : Matrix<__m128>(nAndm) {}
  MatrixFloat::MatrixFloat(const size_t n, const size_t m)
    : Matrix<__m128>(n,m) {}

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
  

