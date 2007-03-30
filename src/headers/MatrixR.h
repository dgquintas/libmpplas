/*
 * $Id$
 */

#ifndef __MATRIXR_H
#define __MATRIXR_H

#include "Matrix.h"
#include "R.h"

namespace mpplas 
{
  class MatrixR : public Matrix<R>
  {
    public:
      MatrixR();
      MatrixR(const MatrixR& m);
      MatrixR(const Matrix<Z>& m);
      MatrixR(const Matrix<R>& m);

      MatrixR(const size_t nAndm);
      MatrixR(const size_t n, const size_t m);

      MatrixR(const std::string& str);

      MatrixR& operator+=(const MatrixR&);
      MatrixR& operator+=(const R&);

      MatrixR& operator-=(const MatrixR&);
      MatrixR& operator-=(const R&);

      MatrixR& operator*=(const MatrixR&);
      MatrixR& operator*=(const R&);

      MatrixR& operator/=(const MatrixR&);
      MatrixR& operator/=(const R&);

      MatrixR& operator^=(const R&);

      MatrixR& diagonalize();
      MatrixR& invert();

      R getDeterminant();

      


  };

  MatrixR operator-(MatrixR m); /**< Unary negation, sign inversion */

}


#endif

