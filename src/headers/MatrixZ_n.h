/*
 * $Id$
 */

#ifndef __MATRIXZ_N_H
#define __MATRIXZ_N_H

#include "Matrix.h"
#include "Z_n.h"


namespace mpplas {
  class MatrixZ_n : public Matrix<Z_n> {
    public:
      MatrixZ_n(const Z& mod);
      MatrixZ_n(const int nAndm, const Z& mod);
      MatrixZ_n(const int n, const int m, const Z& mod);
      MatrixZ_n(const Dimensions& dims, const Z& mod);
      MatrixZ_n(const MatrixZ_n& m);
      MatrixZ_n(const Matrix<Z_n>& m);
      MatrixZ_n(const std::string& str, const Z& mod);

      MatrixZ_n& operator=(const MatrixZ_n& src);

    protected:
      Z _mod;

  };
}





#endif

