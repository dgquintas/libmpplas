/*
 * $Id$
 */

#include "Zx.h"
#include "MethodsFactory.h"

namespace mpplas{

  Zx Zx::ZERO(Z((Digit)0),0);
  Zx Zx::ONE(Z((Digit)1), 0);
  
  const bool Zx::addCommutative(true); 
  const bool Zx::groupCyclic(true);

  const bool Zx::divisionRing(false);
  const bool Zx::multAssociative(true);
  const bool Zx::multCommutative(true);
  const bool Zx::unitaryRing(true);

  Zx::Zx()
    : Polynomial<Z>() {}

  Zx::Zx(const Zx& src)
    : Polynomial<Z>(src) {}

  Zx::Zx(const Polynomial<Z>& src)
    : Polynomial<Z>(src) {}

  Zx::Zx(const std::string& str)
    : Polynomial<Z>(str) {}
 
  Zx::Zx(const std::vector<Z>& coeffs)
    : Polynomial<Z>(coeffs) {}

  Zx::Zx(const Z& coeff, const int exp)
    : Polynomial<Z>(coeff, exp) {}

  Zx Zx::gcd(Zx u, Zx v){
    GCD< Polynomial<Z> >* gcd;
    MethodsFactory::getReference().getFunc(gcd);
    return gcd->gcd(u,v);
  }



}