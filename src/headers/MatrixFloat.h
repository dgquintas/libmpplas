/*
 * $Id$
 */

#ifndef __MATRIXFLOAT_H
#define __MATRIXFLOAT_H

#include "Matrix.h"
#include "kernel.h"

namespace mpplas 
{
  class MatrixFloat : 
    public Matrix< SIMDDigit< float4xSIMD_t >, 
                   SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > 
                 >
  {
    public:
      MatrixFloat();  
      MatrixFloat(const MatrixFloat& m); 
 
      MatrixFloat(const int nAndm);
      MatrixFloat(const int n, const int m);

      MatrixFloat(const std::string& str);

//      MatrixFloat& operator+=(const MatrixFloat&);
//      MatrixFloat& operator+=(const float&);
//
//      MatrixFloat& operator-=(const MatrixFloat&);
//      MatrixFloat& operator-=(const float&);
//
//      MatrixFloat& operator*=(const MatrixFloat&);
//      MatrixFloat& operator*=(const float&);
//
//      MatrixFloat& operator/=(const MatrixFloat&);
//      MatrixFloat& operator/=(const float&);
//
//      MatrixFloat& operator^=(const float&);

      MatrixFloat& diagonalize();
      MatrixFloat& invert();

      float getDeterminant();


    private:

     int _realNumOfCols;

      friend std::istream& operator>>(std::istream& in, MatrixFloat& m);
      friend std::ostream& operator<<(std::ostream& out, const MatrixFloat& m);



  };

  MatrixFloat operator-(MatrixFloat m); /**< Unary negation, sign inversion */

  MatrixFloat operator+(MatrixFloat lhs, const MatrixFloat& rhs);
  MatrixFloat operator-(MatrixFloat lhs, const MatrixFloat& rhs);
  MatrixFloat operator*(MatrixFloat lhs, const MatrixFloat& rhs);
  MatrixFloat operator/(MatrixFloat lhs, const MatrixFloat& rhs);


}


#endif

