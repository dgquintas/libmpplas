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
 
      MatrixFloat(const size_t nAndm);
      MatrixFloat(const size_t n, const size_t m);

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

     size_t _realNumOfCols;

      friend std::istream& operator>>(std::istream& in, MatrixFloat& m);
      friend std::ostream& operator<<(std::ostream& out, const MatrixFloat& m);



  };

  MatrixFloat operator-(MatrixFloat m); /**< Unary negation, sign inversion */


}


#endif

