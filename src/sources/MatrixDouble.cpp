#include "MatrixDouble.h"

namespace mpplas
{
  MatrixDouble::MatrixDouble()
    : Matrix<double>()
  {}

  MatrixDouble::MatrixDouble(const MatrixDouble& m)
    : Matrix<double>(m)
  {}
  MatrixDouble::MatrixDouble(const Matrix<double>& m)
    : Matrix<double>(m)
  {}



  MatrixDouble::MatrixDouble(const size_t nAndm)
    : Matrix<double>(nAndm) {}
  MatrixDouble::MatrixDouble(const size_t n, const size_t m)
    : Matrix<double>(n,m) {}

  //////////////////////////////////////////////
  
  
  
  //////////////////////////////////////////////

  MatrixDouble operator-(MatrixDouble m){
//    m *= ((SignedDigit)-1);
    return m;
  }


  MatrixDouble::MatrixDouble(const std::string& str){
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

}
  

