#include "VectorFloat.h"

#include <cmath>

namespace mpplas
{
  VectorFloat::VectorFloat()
    : Vector< SIMDDigit< float4xSIMD_t> , 
              SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 >   
            >()
  {}
  VectorFloat::VectorFloat(const VectorFloat& mat)
    : Vector< SIMDDigit< float4xSIMD_t> , 
              SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 >   
            >(mat)
  {}

  VectorFloat::VectorFloat(const int n) {
    _realNumOfCols = 
      (int)ceil(((double)n)/SIMDCPU::getElementsPerSIMDDigit< float4xSIMD_t >());
    _data.resize(  _realNumOfCols );
    _dims.setBoth(1,n);
  }

  VectorFloat::VectorFloat(const std::string& str) {
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

  VectorFloat& VectorFloat::operator*=(const VectorFloat& rhs){
    this->byElementProd(rhs);
    return *this;
  }

  VectorFloat& VectorFloat::operator/=(const VectorFloat& rhs){
    this->byElementDiv(rhs);
    return *this;
  }

  
  //////////////////////////////////////////////

  VectorFloat operator-(VectorFloat m){
//    m *= ((SignedDigit)-1);
    return m;
  }

  std::istream& operator>>(std::istream& in, VectorFloat& m){
    Vector<float,SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > >* 
      mf( (Vector<float,SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > >*)(&m));

    _parseMatrixInput<float,
      SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 >, 
      SIMDDigit< float4xSIMD_t > >
        (in, *mf);
      
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const VectorFloat& m){
    Vector<float,SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > >* 
      mf( (Vector<float,SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > >*)(&m));

    out << (*mf);

    return out;
  }

  VectorFloat operator+(VectorFloat lhs, const VectorFloat& rhs){
    lhs += rhs;
    return lhs;
  }
  VectorFloat operator-(VectorFloat lhs, const VectorFloat& rhs){
    lhs -= rhs;
    return lhs;
  }
  VectorFloat operator*(VectorFloat lhs, const VectorFloat& rhs){
    lhs.byElementProd(rhs);
    return lhs;
  }
  VectorFloat operator/(VectorFloat lhs, const VectorFloat& rhs){
    lhs.byElementDiv(rhs);
    return lhs;
  }

float VectorFloat::dot( const VectorFloat& rhs) {
  //both vectors should have the same length
  const int length = this->getSize();
  if( length != rhs.getSize() ){
    std::ostringstream oss;
    oss << "for the dot product.";
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(), oss.str());
  }
  SIMDDigit< float4xSIMD_t >* const thisVec = &(this->operator[](0));
  const SIMDDigit< float4xSIMD_t >* const rhsVec  = &(rhs[0]);
#pragma omp parallel for 
  for(int i=0; i < length; i++){
    thisVec[i] *= rhsVec[i];
  }

  SIMDtoBasicTypes<float4xSIMD_t>::BasicType sum;
  sum = 0.0f;
  for(int i=0; i < length-1; i++){
    sum += (thisVec[i].sum());
  }
  for(int i=0; i < length % 4; i++){
    sum += (thisVec[i].sum());
  }


  return sum;
}


}
  

