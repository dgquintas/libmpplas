/*
 * $Id$
 */

#include "Digit_px.h"
#include "MethodsFactory.h"
#include "GCD.h"


namespace mpplas{

  const Digit_px Digit_px::ZERO( Digit_px( Digit_p(0, 0), 0, 0) );
  const Digit_px Digit_px::ONE ( Digit_px( Digit_p(1, 0), 0, 0) );

  const bool Digit_px::groupCyclic(true);
  const bool Digit_px::addCommutative(true); 

  const bool Digit_px::multAssociative(true);
  const bool Digit_px::multCommutative(true);
  const bool Digit_px::unitaryRing(true);
  const bool Digit_px::divisionRing(true);

  Digit_px::Digit_px(const Digit p)
    : Polynomial<Digit_p>( Digit_p(p) ) {}

  Digit_px::Digit_px(const Digit_px& src)
    : Polynomial<Digit_p>(src) {}

  Digit_px::Digit_px(const Polynomial<Digit_p>& src)
    : Polynomial<Digit_p>(src) {}

  Digit_px::Digit_px(const std::string& str, const Digit p)
    : Polynomial<Digit_p>(str, Digit_p(p) ) {}
 
  Digit_px::Digit_px(const std::vector<Digit_p>& coeffs, const Digit p)
    : Polynomial<Digit_p>(coeffs, Digit_p(p) ) {}

  Digit_px::Digit_px(const Digit_p& coeff, const int exp, const Digit p)
    : Polynomial<Digit_p>(coeff, exp, Digit_p(p) ) {}

  Digit_px::Digit_px(const Digit coeff, const int exp, const Digit p)
    : Polynomial<Digit_p>( Digit_p(coeff,p), exp, Digit_p(p) ) {}


  Digit_px& Digit_px::operator=(const Digit_px& src){
    Polynomial<Digit_p>::operator=(src);
    return *this;
  }


  Digit_px Digit_px::gcd(Digit_px u, Digit_px v, Digit_px* const s, Digit_px* const t){
    assert(u.getCharacteristic() == v.getCharacteristic());
    if( s && t ){
      GCDExt< Polynomial<Digit_p> >* gcdext;
      MethodsFactory::getReference().getFunc(gcdext);
      return gcdext->gcdext(u,v,s,t);
    }
    else{
      GCD< Polynomial<Digit_p> >* gcd;
      MethodsFactory::getReference().getFunc(gcd);
      return gcd->gcd(u,v);
    }
  }



}
