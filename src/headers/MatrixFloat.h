/*
 * $Id$
 */

#ifndef __MATRIXFLOAT_H
#define __MATRIXFLOAT_H

#include "Matrix.h"
#include "BasicTypedefs.h"

namespace mpplas 
{
  class MatrixFloat : public Matrix< SIMDDigit >
  {
    public:
      MatrixFloat();
      MatrixFloat(const MatrixFloat& m);
      MatrixFloat(const Matrix<SIMDDigit>& m);

      MatrixFloat(const size_t nAndm);
      MatrixFloat(const size_t n, const size_t m);

      MatrixFloat(const std::string& str);

      MatrixFloat& operator+=(const MatrixFloat&);
      MatrixFloat& operator+=(const float&);

      MatrixFloat& operator-=(const MatrixFloat&);
      MatrixFloat& operator-=(const float&);

      MatrixFloat& operator*=(const MatrixFloat&);
      MatrixFloat& operator*=(const float&);

      MatrixFloat& operator/=(const MatrixFloat&);
      MatrixFloat& operator/=(const float&);

      MatrixFloat& operator^=(const float&);

      MatrixFloat& diagonalize();
      MatrixFloat& invert();

      float getDeterminant();


    private:
      friend std::istream& operator>>(std::istream& is, MatrixFloat& m ) ;
  


  };

  MatrixFloat operator-(MatrixFloat m); /**< Unary negation, sign inversion */

  std::istream& operator>>(std::istream& is, MatrixFloat& m);

}


#endif

