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
      MatrixZ(const size_t nAndm);
      MatrixZ(const size_t n, const size_t m);
      MatrixZ(const Dimensions& dims);
      MatrixZ(const MatrixZ& m);
      MatrixZ(const Matrix<Z>& m);
      MatrixZ(const std::string& str);



      


  };


}


#endif

