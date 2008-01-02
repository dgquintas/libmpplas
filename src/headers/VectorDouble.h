/*
 * $Id$
 */

#ifndef __VECTORDOUBLE_H
#define __VECTORDOUBLE_H

#include "Vector.h"
#include "kernel.h"

namespace mpplas {
  class VectorDouble : 
    public Vector< SIMDDigit< double2xSIMD_t >, 
                   SSEAlloc< SIMDDigit< double2xSIMD_t >, 16 > 
                 >
  {
    public:
      VectorDouble();  
      VectorDouble(const VectorDouble& m); 
 
      VectorDouble(const int n);

      VectorDouble(const std::string& str);

//      VectorDouble& operator+=(const VectorDouble&);
//      VectorDouble& operator+=(const double&);

//      VectorDouble& operator-=(const VectorDouble&);
//      VectorDouble& operator-=(const double&);

      VectorDouble& operator*=(const VectorDouble& rhs);
//    VectorDouble& operator*=(const double&);
//
      VectorDouble& operator/=(const VectorDouble& rhs);
//      VectorDouble& operator/=(const double&);

//      VectorDouble& operator^=(const double&);

      SIMDtoBasicTypes<double2xSIMD_t>::BasicType  dot(const VectorDouble& rhs);

    private:

     int _realNumOfCols;

      friend std::istream& operator>>(std::istream& in, VectorDouble& m);
      friend std::ostream& operator<<(std::ostream& out, const VectorDouble& m);



  };

  VectorDouble operator-(VectorDouble m); /**< Unary negation, sign inversion */

  VectorDouble operator+(VectorDouble lhs, const VectorDouble& rhs);
  VectorDouble operator-(VectorDouble lhs, const VectorDouble& rhs);
  VectorDouble operator*(VectorDouble lhs, const VectorDouble& rhs);
  VectorDouble operator/(VectorDouble lhs, const VectorDouble& rhs);


}


#endif

