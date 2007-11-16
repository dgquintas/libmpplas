/*
 * $Id$
 */

#ifndef __MATRIXGF_H
#define __MATRIXGF_H

#include "Matrix.h"
#include "GFx.h"
#include "GF.h"

namespace mpplas {
  class MatrixGFx : public Matrix<GFx> {
    public:
      MatrixGFx(const GF& generator);
      MatrixGFx(const int nAndm, const GF& generator);
      MatrixGFx(const int n, const int m, const GF& generator);
      MatrixGFx(const Dimensions& dims, const GF& generator);
      MatrixGFx(const MatrixGFx& m);
      MatrixGFx(const Matrix<GFx>& m);
      MatrixGFx(const std::string& str, const GF& generator);

      MatrixGFx& operator=(const MatrixGFx& src);

    protected:
      GF _gfGenerator;

  };
}


#endif

