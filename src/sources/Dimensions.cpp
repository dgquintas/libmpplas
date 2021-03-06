#include "Dimensions.h"
#include <sstream>

namespace mpplas{

  Dimensions::Dimensions()
    : _n(0), _m(0)
  {}

  Dimensions::Dimensions(int n, int m)
    : _n(n), _m(m)
  {}

  Dimensions::Dimensions(const Dimensions& rhs)
    : _n(rhs._n), _m(rhs._m)
  {}

  std::string Dimensions::toString() const{
    std::ostringstream oss;
    oss << "(" << _n << ", " << _m << ")";
    return oss.str();
  }
}

