/*
 * $Id$
 */

#include "Z_px.h"
#include "MethodsFactory.h"
#include "GCD.h"


namespace mpplas{

  Z_px Z_px::ZERO( Z_px( Z_p((Digit)0, (Digit)0, false, false), 0, 0) );
  Z_px Z_px::ONE ( Z_px( Z_p((Digit)1, (Digit)0, false, false), 0, 0) );

  const bool Z_px::groupCyclic(true);
  const bool Z_px::addCommutative(true); 

  const bool Z_px::multAssociative(true);
  const bool Z_px::multCommutative(true);
  const bool Z_px::unitaryRing(true);
  const bool Z_px::divisionRing(true);

  Z_px::Z_px(const Z& p)
    : Polynomial<Z_p>( Z_p(p) ), _p(p) {}

  Z_px::Z_px(const Z_px& src)
    : Polynomial<Z_p>(src) {}

  Z_px::Z_px(const Polynomial<Z_p>& src)
    : Polynomial<Z_p>(src) {}

  Z_px::Z_px(const std::string& str, const Z& p)
    : Polynomial<Z_p>(str, Z_p(p) ), _p(p) {}
 
  Z_px::Z_px(const std::vector<Z_p>& coeffs, const Z& p)
    : Polynomial<Z_p>(coeffs, Z_p(p) ), _p(p) {}

  Z_px::Z_px(const Z_p& coeff, const int exp, const Z& p)
    : Polynomial<Z_p>(coeff, exp, Z_p(p) ), _p(p) {}

  Z_px::Z_px(const Z& coeff, const int exp, const Z& p)
    : Polynomial<Z_p>( Z_p(coeff,p), exp, Z_p(p) ), _p(p) {}



  Z_px Z_px::gcd(Z_px u, Z_px v, Z_px* const s, Z_px* const t){
    assert(u.getCharacteristic() == v.getCharacteristic());
    if( s && t ){
      mpplas::GCDExt< Polynomial<mpplas::Z_p> >* gcdext;
      MethodsFactory::getReference().getFunc(gcdext);
      return gcdext->gcdext(u,v,s,t);
    }
    else{
      mpplas::GCD< Polynomial<mpplas::Z_p> >* gcd;
      MethodsFactory::getReference().getFunc(gcd);
      return gcd->gcd(u,v);
    }
  }



}
