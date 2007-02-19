/*
 * $Id$
 */

#include <sstream>

#include "VectorZ.h"

namespace numth{

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

  VectorZ& VectorZ::operator+=(const VectorZ& rhs) throw (Errores::NonConformantDimensions)
  {
    //both vectors should have the same length
    if( this->size() != rhs.size() ){
      std::ostringstream oss;
      oss << "Right-hand-side operator size = " << rhs.size();
      throw Errores::NonConformantDimensions(oss.str());
    }
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));
    const Z* const rhsVec  = &(rhs[0]);

#pragma omp parallel for
    for(size_t i=0; i < length; i++){
      thisVec[i] += rhsVec[i];
    }

    return *this;
  }

  VectorZ& VectorZ::operator*=(const Z& rhs){
    const size_t length = this->size();
    Z* const thisVec = &(this->operator[](0));
#pragma omp parallel for
    for(size_t i=0; i < length; i++){
      thisVec[i] *= rhs;
    }
  }



}
