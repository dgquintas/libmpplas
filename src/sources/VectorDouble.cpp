#include "VectorDouble.h"

#include <cmath>

namespace mpplas
{
  VectorDouble::VectorDouble()
    : Vector< SIMDDigit< double2xSIMD_t> , 
              SSEAlloc< SIMDDigit< double2xSIMD_t >, 16 >   
            >()
  {}
  VectorDouble::VectorDouble(const VectorDouble& mat)
    : Vector< SIMDDigit< double2xSIMD_t> , 
              SSEAlloc< SIMDDigit< double2xSIMD_t >, 16 >   
            >(mat)
  {}

  VectorDouble::VectorDouble(const int n) {
    _realNumOfCols = 
      (int)ceil(((double)n)/SIMDCPU::getElementsPerSIMDDigit< double2xSIMD_t >());
    _data.resize( _realNumOfCols );
    _dims.setBoth(1,n);
  }

  VectorDouble::VectorDouble(const std::string& str) {
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

  VectorDouble& VectorDouble::operator*=(const VectorDouble& rhs){
    this->byElementProd(rhs);
    return *this;
  }

  VectorDouble& VectorDouble::operator/=(const VectorDouble& rhs){
    this->byElementDiv(rhs);
    return *this;
  }

  
  //////////////////////////////////////////////

  VectorDouble operator-(VectorDouble m){
//    m *= ((SignedDigit)-1);
    return m;
  }

  std::istream& operator>>(std::istream& in, VectorDouble& m){
    Vector<double,SSEAlloc< SIMDDigit< double2xSIMD_t >, 16 > >* 
      mf( (Vector<double,SSEAlloc< SIMDDigit< double2xSIMD_t >, 16 > >*)(&m));

    _parseMatrixInput<double,
      SSEAlloc< SIMDDigit< double2xSIMD_t >, 16 >, 
      SIMDDigit< double2xSIMD_t > >
        (in, *mf);
      
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const VectorDouble& m){
    Vector<double,SSEAlloc< SIMDDigit< double2xSIMD_t >, 16 > >* 
      mf( (Vector<double,SSEAlloc< SIMDDigit< double2xSIMD_t >, 16 > >*)(&m));

    out << (*mf);

    return out;
  }

  VectorDouble operator+(VectorDouble lhs, const VectorDouble& rhs){
    lhs += rhs;
    return lhs;
  }
  VectorDouble operator-(VectorDouble lhs, const VectorDouble& rhs){
    lhs -= rhs;
    return lhs;
  }
  VectorDouble operator*(VectorDouble lhs, const VectorDouble& rhs){
    lhs.byElementProd(rhs);
    return lhs;
  }
  VectorDouble operator/(VectorDouble lhs, const VectorDouble& rhs){
    lhs.byElementDiv(rhs);
    return lhs;
  }

double VectorDouble::dot( const VectorDouble& rhs) {
  //both vectors should have the same length
  const int length = this->getSize();
  if( length != rhs.getSize() ){
    std::ostringstream oss;
    oss << "for the dot product.";
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(), oss.str());
  }
  SIMDDigit< double2xSIMD_t >* const thisVec = &(this->operator[](0));
  const SIMDDigit< double2xSIMD_t >* const rhsVec  = &(rhs[0]);
#pragma omp parallel for 
  for(int i=0; i < length; i++){
    thisVec[i] *= rhsVec[i];
  }

  SIMDtoBasicTypes<double2xSIMD_t>::BasicType
  sum = 0.0;
  for(int i=0; i < length; i++){
    sum += (thisVec[i].sum());
  }

  return sum;
}


}
  

