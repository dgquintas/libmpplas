/*
 * $Id$
 */


#include "GF.h"

namespace mpplas {

//  GF::GF(const Z& p, const Digit n)
//    : Z_px(p), _p(p), _n(n)
//  {}

  GF::GF(const Z& p, const Z_px& fx)
    : Z_px(p), _n( fx.getDegree() ), _p(p), _fx(fx) {
    assert( fx.getCharacteristic() == p ); //FIXME: raise exception
  }

  GF::GF(const Z_px& poly, const Z_px& fx)
    : Z_px(poly), _n( poly.getDegree() ), _fx(fx), _p( poly.getCharacteristic() )
  {
    assert( fx.getCharacteristic() == poly.getCharacteristic() ); //FIXME: raise exception
    this->operator%=(fx);
  }

  GF& GF::operator*=(const GF& rhs){
    ((Z_px*)this)->operator*=(rhs);
    this->operator%=(_fx);

    return *this;
  }
  GF& GF::square(){
    ((Z_px*)this)->square();
    this->operator%=(_fx);
    return *this;
  }
  GF& GF::operator/=(const GF& rhs){
    GF inv(rhs);
    inv.invert();
    this->operator*=(inv);

    return *this;
  }

  GF& GF::invert(){
    Z_px dummy(_p);
    Z_px::gcd(*this,_fx, this, &dummy);
    return *this;
  }
  GF GF::getInverse() const {
    GF inv(*this);
    inv.invert();
    return inv;
  }

  GF& GF::operator=(const GF& src){
    Z_px::operator=(src);
    this->_fx = src._fx;
    this->_p = src._p;
    this->_n = src._n;
    return *this;
  }

//  Z_px GF::_testForIrreducibility(const Z& p, const Z_px& fx){
//    Z_px u(1, 1, p);
//  }
//  Z_px GF::_genIrreduciblePolynomial(const int degree){
//    
//  }
//  Z_px GF::_genPrimitivePolynomial(const int degree){
//  }



}
