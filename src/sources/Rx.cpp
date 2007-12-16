/*
 * $Id$
 */

#include "Rx.h"
#include "MethodsFactory.h"

namespace mpplas{

  const Rx Rx::ZERO(R((Digit)0, false),0);
  const Rx Rx::ONE(R((Digit)1, false), 0);
  
  const bool Rx::addCommutative(true); 
  const bool Rx::groupCyclic(true);

  const bool Rx::divisionRing(true);
  const bool Rx::multAssociative(true);
  const bool Rx::multCommutative(true);
  const bool Rx::unitaryRing(true);

  Rx::Rx(const Rx& src)
    : Polynomial<R>(src) {}

  Rx::Rx(const Polynomial<R>& src)
    : Polynomial<R>(src) {}

  Rx::Rx(const std::string& str)
    : Polynomial<R>(str) {}
 
  Rx::Rx(const std::vector<R>& coeffs)
    : Polynomial<R>(coeffs) {}

  Rx::Rx(const R& coeff, const int exp)
    : Polynomial<R>(coeff, exp) {}
 
  Rx& Rx::operator=(const Rx& src){
    Polynomial<R>::operator=(src);
    return *this;
  }


}
