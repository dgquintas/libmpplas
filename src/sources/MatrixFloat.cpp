#include "MatrixFloat.h"

#include <cmath>

namespace mpplas
{
  MatrixFloat::MatrixFloat()
    : Matrix< SIMDDigit< float4xSIMD_t> , 
              SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 >   
            >()
  {}
  MatrixFloat::MatrixFloat(const MatrixFloat& mat)
    : Matrix< SIMDDigit< float4xSIMD_t> , 
              SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 >   
            >(mat)
  {}

  MatrixFloat::MatrixFloat(const size_t nAndm) {
    _realNumOfCols = 
      (size_t)ceil(((double)nAndm)/SIMDCPU::getElementsPerSIMDDigit< float4xSIMD_t >());
    _data.resize( nAndm * _realNumOfCols );
    _dims.setBoth(nAndm,nAndm);
  }
  MatrixFloat::MatrixFloat(const size_t n, const size_t m) {
    _realNumOfCols = 
      (size_t)ceil(((double)m)/SIMDCPU::getElementsPerSIMDDigit< float4xSIMD_t >());
    _data.resize( n * _realNumOfCols );
    _dims.setBoth(n,m);
  }

  MatrixFloat::MatrixFloat(const std::string& str) {
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

  
  //////////////////////////////////////////////

  MatrixFloat operator-(MatrixFloat m){
//    m *= ((SignedDigit)-1);
    return m;
  }

  std::istream& operator>>(std::istream& in, MatrixFloat& m){

    m._parseMatrixInput(in, 4);
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const MatrixFloat& m){
    Matrix<float,SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > >* 
      mf( (Matrix<float,SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > >*)(&m));

    out << (*mf);

    return out;
  }

}
  

