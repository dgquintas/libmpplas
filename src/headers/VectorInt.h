/*
 * $Id$
 */

#ifndef __VECTORDOUBLE_H
#define __VECTORDOUBLE_H

#include "Vector.h"
#include "kernel.h"

namespace mpplas {
  class VectorInt : 
    public Vector< SIMDDigit< int8xSIMD_t >, 
                   SSEAlloc< SIMDDigit< int8xSIMD_t >, 16 > 
                 >
  {
    public:
      VectorInt();  
      VectorInt(const VectorInt& m); 
 
      VectorInt(const int n);

      VectorInt(const std::string& str);

//      VectorInt& operator+=(const VectorInt&);
//      VectorInt& operator+=(const int&);

//      VectorInt& operator-=(const VectorInt&);
//      VectorInt& operator-=(const int&);

      VectorInt& operator*=(const VectorInt& rhs);
//    VectorInt& operator*=(const int&);
//
      VectorInt& operator/=(const VectorInt& rhs);
//      VectorInt& operator/=(const int&);

//      VectorInt& operator^=(const int&);

       SIMDtoBasicTypes<int8xSIMD_t>::BasicType dot(const VectorInt& rhs);

    private:

     int _realNumOfCols;

      friend std::istream& operator>>(std::istream& in, VectorInt& m);
      friend std::ostream& operator<<(std::ostream& out, const VectorInt& m);



  };

  VectorInt operator-(VectorInt m); /**< Unary negation, sign inversion */

  VectorInt operator+(VectorInt lhs, const VectorInt& rhs);
  VectorInt operator-(VectorInt lhs, const VectorInt& rhs);
  VectorInt operator*(VectorInt lhs, const VectorInt& rhs);
  VectorInt operator/(VectorInt lhs, const VectorInt& rhs);


}


#endif

