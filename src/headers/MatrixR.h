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
      MatrixR(const int nAndm);
      MatrixR(const int n, const int m);
      MatrixR(const Dimensions& dims);
      MatrixR(const MatrixR& m);
      MatrixR(const Matrix<R>& m);
      MatrixR(const std::string& str);

      MatrixR& operator=(const MatrixR& src);

  };


}


#endif

