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
      MatrixR(const size_t nAndm);
      MatrixR(const size_t n, const size_t m);
      MatrixR(const Dimensions& dims);
      MatrixR(const MatrixR& m);
//      MatrixR(const MatrixZ& m);
      MatrixR(const Matrix<R>& m);
      MatrixR(const std::string& str);

      


  };


}


#endif

