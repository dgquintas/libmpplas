#include "AlgebraUtils.h"
#include <sstream>

namespace mpplas{

  Dimensions::Dimensions()
    : _n(0), _m(0)
  {}

  Dimensions::Dimensions(size_t n, size_t m)
    : _n(n), _m(m)
  {}

  Dimensions::Dimensions(const Dimensions& rhs)
    : _n(rhs._n), _m(rhs._m)
  {}

  size_t Dimensions::getRows() const{
    return _n;
  }

  size_t Dimensions::getColumns() const{
    return _m;
  }

  void Dimensions::setRows(size_t n){
    _n = n;
  }
  void Dimensions::setColumns(size_t m){
    _m = m;
  }

  void Dimensions::setBoth(size_t n, size_t m){
    _n = n;
    _m = m;
  }

  size_t Dimensions::getProduct() const{
    return _n * _m;
  }
    

  inline bool Dimensions::operator==(const Dimensions& rhs) const{
    return (_n == rhs._n) && (_m == rhs._m);
  }
  inline bool Dimensions::operator!=(const Dimensions& rhs) const{
    return !(this->operator==(rhs));
  }

  std::string Dimensions::toString() const{
    std::ostringstream oss;
    oss << "(" << _n << ", " << _m << ")";
    return oss.str();
  }
}
