/*
 * $Id$
 */

#include <sstream>

#include "VectorZ.h"

namespace mpplas{

  VectorZ::VectorZ()
    : Vector<Z>()
  {}

  VectorZ::VectorZ(size_t n)
    : Vector<Z>(n)
  {}

  VectorZ::VectorZ(const VectorZ& rhs)
    : Vector<Z>(rhs)
  {}

  VectorZ::VectorZ(const std::vector<Z>& rhs)
    : Vector<Z>(rhs)
  {} 

  VectorZ::VectorZ(const std::string& str)
    : Vector<Z>(str)
  {}

//////////////////////////////////////////////////////

  VectorZ& VectorZ::operator+=(const VectorZ& rhs) 
  {
    //both vectors should have the same length
    if( this->size() != rhs.size() ){
      std::ostringstream oss;
      oss << "Right-hand-side operator size = " << rhs.size();
      throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(),  oss.str());
    }
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));
    const Z* const rhsVec  = &(rhs[0]);

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] += rhsVec[i];
    }

    return *this;
  }
 
  VectorZ& VectorZ::operator+=(const Z& rhs) 
  {
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] += rhs;
    }

    return *this;
  }
  VectorZ& VectorZ::operator+=(const Cifra rhs) 
  {
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] += rhs;
    }

    return *this;
  }
  VectorZ& VectorZ::operator+=(const CifraSigno rhs) 
  {
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] += rhs;
    }

    return *this;
  }









  VectorZ& VectorZ::operator-=(const VectorZ& rhs) 
  {
    //both vectors should have the same length
    if( this->size() != rhs.size() ){
      throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
    }
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));
    const Z* const rhsVec  = &(rhs[0]);

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] -= rhsVec[i];
    }

    return *this;
  }
  VectorZ& VectorZ::operator-=(const Z& rhs) 
  {
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] -= rhs;
    }

    return *this;
  }
  VectorZ& VectorZ::operator-=(const Cifra rhs) 
  {
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] -= rhs;
    }

    return *this;
  }
  VectorZ& VectorZ::operator-=(const CifraSigno rhs) 
  {
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] -= rhs;
    }

    return *this;
  }




  VectorZ& VectorZ::operator*=(const VectorZ& rhs) 
  {
    //both vectors should have the same length
    if( this->size() != rhs.size() ){
      throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
    }
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));
    const Z* const rhsVec  = &(rhs[0]);

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] *= rhsVec[i];
    }

    return *this;
  }
  VectorZ& VectorZ::operator*=(const Z& rhs){
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));
#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] *= rhs;
    }
    return *this;
  } 
  VectorZ& VectorZ::operator*=(const Cifra rhs){
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));
#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] *= rhs;
    }
    return *this;
  }
  VectorZ& VectorZ::operator*=(const CifraSigno rhs){
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));
#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisVec[i] *= rhs;
    }
    return *this;
  }







  VectorZ& VectorZ::cross(const VectorZ& rhs){
    //both vectors should have three dimensions
    if( this->size() != 3 || rhs.size() != 3 ){
      std::ostringstream oss;
      oss << "Cross product operators should have three dimensions" << rhs.size();
      throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(), oss.str());
    }

    


    return *this;
  }




  /////////////////////////////////////////
  
  Z dot(const VectorZ& lhs, const VectorZ& rhs) {
    //both vectors should have the same length
    const size_t length = lhs.size();
    if( length != rhs.size() ){
      std::ostringstream oss;
      oss << "for the dot product.";
      throw Errors::NonConformantDimensions(lhs.getDimensions(), rhs.getDimensions(), oss.str());
    }
    VectorZ thisCopy(lhs);
    Z* const thisVec = &(thisCopy.operator[](0));
    const Z* const rhsVec  = &(rhs[0]);
#pragma omp parallel for 
    for(int i=0; i < length; i++){
      thisVec[i] *= rhsVec[i];
    }
  
    Z sum;
    sum.hacerCero();
    for(int i=0; i < length; i++){
      sum += thisVec[i];
    }

    return sum;
  }



}
