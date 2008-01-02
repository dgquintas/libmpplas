/*
 * $Id$
 */

#ifndef __VECTORFLOAT_H
#define __VECTORFLOAT_H

#include "Vector.h"
#include "kernel.h"

namespace mpplas {
  class VectorFloat : 
    public Vector< SIMDDigit< float4xSIMD_t >, 
                   SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > 
                 >
  {
    public:
      VectorFloat();  
      VectorFloat(const VectorFloat& m); 
 
      VectorFloat(const int n);

      VectorFloat(const std::string& str);

//      VectorFloat& operator+=(const VectorFloat&);
//      VectorFloat& operator+=(const float&);

//      VectorFloat& operator-=(const VectorFloat&);
//      VectorFloat& operator-=(const float&);

      VectorFloat& operator*=(const VectorFloat& rhs);
//    VectorFloat& operator*=(const float&);
//
      VectorFloat& operator/=(const VectorFloat& rhs);
//      VectorFloat& operator/=(const float&);

//      VectorFloat& operator^=(const float&);

     SIMDtoBasicTypes<float4xSIMD_t>::BasicType  dot(const VectorFloat& rhs);

    private:

     int _realNumOfCols;

      friend std::istream& operator>>(std::istream& in, VectorFloat& m);
      friend std::ostream& operator<<(std::ostream& out, const VectorFloat& m);



  };

  VectorFloat operator-(VectorFloat m); /**< Unary negation, sign inversion */

  VectorFloat operator+(VectorFloat lhs, const VectorFloat& rhs);
  VectorFloat operator-(VectorFloat lhs, const VectorFloat& rhs);
  VectorFloat operator*(VectorFloat lhs, const VectorFloat& rhs);
  VectorFloat operator/(VectorFloat lhs, const VectorFloat& rhs);


}


#endif

