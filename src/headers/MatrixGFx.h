/*
 * $Id$
 */

#ifndef __MATRIXGF_H
#define __MATRIXGF_H

#include "Matrix.h"
#include "GFx.h"

namespace mpplas {
  class MatrixGFx : public Matrix<GFx>
  {
    public:
      MatrixGFx();
      MatrixGFx(const int nAndm);
      MatrixGFx(const int n, const int m);
      MatrixGFx(const Dimensions& dims);
      MatrixGFx(const MatrixGFx& m);
      MatrixGFx(const Matrix<GFx>& m);
      MatrixGFx(const std::string& str);

      MatrixGFx& operator=(const MatrixGFx& src);

  };
}


#endif

