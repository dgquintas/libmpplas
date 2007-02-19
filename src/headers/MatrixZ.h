/*
 * $Id$
 */

#ifndef __MATRIXZ_H
#define __MATRIXZ_H

#include "Matrix.h"
#include "Z.h"

namespace numth
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
      MatrixZ& operator+=(const Cifra);
      MatrixZ& operator+=(const CifraSigno);

      MatrixZ& operator-=(const MatrixZ&);
      MatrixZ& operator-=(const Z&);
      MatrixZ& operator-=(const Cifra);
      MatrixZ& operator-=(const CifraSigno);

      MatrixZ& operator*=(const MatrixZ&);
      MatrixZ& operator*=(const Z&);
      MatrixZ& operator*=(const Cifra);
      MatrixZ& operator*=(const CifraSigno);

      MatrixZ& operator/=(const MatrixZ&);
      MatrixZ& operator/=(const Z&);
      MatrixZ& operator/=(const Cifra);
      MatrixZ& operator/=(const CifraSigno);

      MatrixZ& operator^=(const MatrixZ&);
      MatrixZ& operator^=(const Z&);
      MatrixZ& operator^=(const Cifra);
      MatrixZ& operator^=(const CifraSigno);


      MatrixZ& diagonalize();
      MatrixZ& invert();

      Z getDeterminant();

      


  };

  //MatrixZ operator-(MatrixZ); /**< Unary negation, sign inversion */

}


#endif

