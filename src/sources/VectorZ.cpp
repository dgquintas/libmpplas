/*
 * $Id$
 */

#include <sstream>

#include "VectorZ.h"

namespace mpplas{

  VectorZ::VectorZ()
    : Vector<Z>()
  {}

  VectorZ::VectorZ(const size_t n)
    : Vector<Z>(n)
  {}

  VectorZ::VectorZ(const size_t n, const Z& ini)
    : Vector<Z>(n, ini)
  {}


  VectorZ::VectorZ(const VectorZ& rhs)
    : Vector<Z>(rhs)
  {}

  VectorZ::VectorZ(const std::vector<Z>& rhs)
    : Vector<Z>(rhs)
  {} 

  VectorZ::VectorZ(const std::string& str)
    : Vector<Z>(str)
  {}




}
