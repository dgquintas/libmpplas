/*
 * $Id$
 */

#include <sstream>

#include "VectorR.h"

namespace mpplas{

  VectorR::VectorR()
    : Vector<R>()
  {}

  VectorR::VectorR(const size_t n)
    : Vector<R>(n)
  {}

  VectorR::VectorR(const size_t n, const R& ini)
    : Vector<R>(n, ini)
  {}


  VectorR::VectorR(const VectorR& rhs)
    : Vector<R>(rhs)
  {}

  VectorR::VectorR(const std::vector<R>& rhs)
    : Vector<R>(rhs)
  {} 

  VectorR::VectorR(const std::string& str)
    : Vector<R>(str)
  {}




}
