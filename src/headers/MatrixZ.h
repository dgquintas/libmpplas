/*
 * $Id$
 */

#ifndef __MATRIXZ_H
#define __MATRIXZ_H

#include "Matrix.h"
#include "Z.h"

namespace mpplas 
{
  class MatrixZ : public Matrix<Z>
  {
    public:
      MatrixZ();
      MatrixZ(const MatrixZ& m);
      MatrixZ(const Matrix<Z>& m);

      MatrixZ(const size_t nAndm);
      MatrixZ(const size_t n, const size_t m);

      MatrixZ(const std::string& str);

      MatrixZ& operator+=(const MatrixZ&);
      MatrixZ& operator+=(const Z&);

      MatrixZ& operator-=(const MatrixZ&);
      MatrixZ& operator-=(const Z&);

      MatrixZ& operator*=(const MatrixZ&);
      MatrixZ& operator*=(const Z&);

      MatrixZ& operator/=(const MatrixZ&);
      MatrixZ& operator/=(const Z&);

      MatrixZ& operator^=(const Z&);


      MatrixZ& diagonalize();

      MatrixZ& invert();

      Z getDeterminant();

      


  };

  MatrixZ operator-(MatrixZ m); /**< Unary negation, sign inversion */

}


#endif

