#include "VectorInt.h"

#include <cmath>

namespace mpplas
{
  VectorInt::VectorInt()
    : Vector< SIMDDigit< int8xSIMD_t> , 
              SSEAlloc< SIMDDigit< int8xSIMD_t >, 16 >   
            >()
  {}
  VectorInt::VectorInt(const VectorInt& mat)
    : Vector< SIMDDigit< int8xSIMD_t> , 
              SSEAlloc< SIMDDigit< int8xSIMD_t >, 16 >   
            >(mat)
  {}

  VectorInt::VectorInt(const int n) {
    _realNumOfCols = 
      (int)ceil(((int)n)/SIMDCPU::getElementsPerSIMDDigit< int8xSIMD_t >());
    _data.resize( _realNumOfCols );
    _dims.setBoth(1,n);
  }

  VectorInt::VectorInt(const std::string& str) {
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

  VectorInt& VectorInt::operator*=(const VectorInt& rhs){
    this->byElementProd(rhs);
    return *this;
  }

  VectorInt& VectorInt::operator/=(const VectorInt& rhs){
    this->byElementDiv(rhs);
    return *this;
  }

  
  //////////////////////////////////////////////

  VectorInt operator-(VectorInt m){
//    m *= ((SignedDigit)-1);
    return m;
  }

  std::istream& operator>>(std::istream& in, VectorInt& m){
    Vector<int16_t,SSEAlloc< SIMDDigit< int8xSIMD_t >, 16 > >* 
      mf( (Vector<int16_t,SSEAlloc< SIMDDigit< int8xSIMD_t >, 16 > >*)(&m));

    _parseMatrixInput<int16_t,
      SSEAlloc< SIMDDigit< int8xSIMD_t >, 16 >, 
      SIMDDigit< int8xSIMD_t > >
        (in, *mf);
      
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const VectorInt& m){
    Vector<int16_t,SSEAlloc< SIMDDigit< int8xSIMD_t >, 16 > >* 
      mf( (Vector<int16_t,SSEAlloc< SIMDDigit< int8xSIMD_t >, 16 > >*)(&m));

    out << (*mf);

    return out;
  }

  VectorInt operator+(VectorInt lhs, const VectorInt& rhs){
    lhs += rhs;
    return lhs;
  }
  VectorInt operator-(VectorInt lhs, const VectorInt& rhs){
    lhs -= rhs;
    return lhs;
  }
  VectorInt operator*(VectorInt lhs, const VectorInt& rhs){
    lhs.byElementProd(rhs);
    return lhs;
  }
  VectorInt operator/(VectorInt lhs, const VectorInt& rhs){
    lhs.byElementDiv(rhs);
    return lhs;
  }

  SIMDtoBasicTypes<int8xSIMD_t>::BasicType VectorInt::dot( const VectorInt& rhs) {
  //both vectors should have the same length
  const size_t length = this->getSize();
  if( length != rhs.getSize() ){
    std::ostringstream oss;
    oss << "for the dot product.";
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(), oss.str());
  }
  SIMDDigit< int8xSIMD_t >* const thisVec = &(this->operator[](0));
  const SIMDDigit< int8xSIMD_t >* const rhsVec  = &(rhs[0]);
#pragma omp parallel for 
  for(int i=0; i < length; i++){
    thisVec[i] *= rhsVec[i];
  }

  SIMDtoBasicTypes<int8xSIMD_t>::BasicType sum;
  sum = 0;
  for(int i=0; i < length; i++){
    sum += (thisVec[i].sum());
  }

  return sum;
}


}
  

