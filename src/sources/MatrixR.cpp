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

  MatrixR operator-(MatrixR m){
//    m *= ((CifraSigno)-1);
    return m;
  }


  MatrixR::MatrixR(const std::string& str){
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

}
  

