/*
 * $Id$
 */

#include "VectorZ.h"

namespace numth{

  VectorZ::VectorZ()
  {}

  VectorZ::VectorZ(size_t n)
    : _data(n)
  {}

  VectorZ::VectorZ(const VectorZ& rhs)
    : _data(rhs._data)
  {}

  VectorZ::VectorZ(const std::vector<Z>& rhs)
    : _data(rhs)
  {} 

}
