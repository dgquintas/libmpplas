/*
 * $Id$
 */


#include "GF.h"
#include "Potencia.h"
#include "MethodsFactory.h"
#include "PolynomialUtils.h"

namespace mpplas {


  const GF GF::ZERO( GF(Z_px(Z_p((Digit)0, (Digit)0, false, false), 0, 0), Z_px::ZERO ) );
  const GF GF::ONE ( GF(Z_px(Z_p((Digit)1, (Digit)0, false, false), 0, 0), Z_px::ZERO ) );

  const bool GF::groupCyclic(true);
  const bool GF::addCommutative(true); 

  const bool GF::multAssociative(true);
  const bool GF::multCommutative(true);
  const bool GF::unitaryRing(true);
  const bool GF::divisionRing(true);


  GF::GF(const Z& p, const int n)
    : Z_px(p), _p(p), _n(n),_fx(PolynomialUtils::generateIrreducible<mpplas::Z_px>(n,p)){
      this->operator%=(_fx);
  }

  GF::GF(const Z& p, const Z_px& fx)
    : Z_px(p), _n( fx.getDegree() ), _p(p), _fx(fx) {
    assert( fx.getCharacteristic() == p ); //FIXME: raise exception
  }

  GF::GF(const Z_px& poly, const Z_px& fx)
    : Z_px(poly), _n( poly.getDegree() ), _fx(fx), _p( poly.getCharacteristic() )
  {
    assert( fx.getCharacteristic() == poly.getCharacteristic() ); //FIXME: raise exception
    if( !fx.isZero() ){
      this->operator%=(fx);
    }
  }

  GF& GF::operator*=(const GF& rhs){
    if( this->_fx.isZero() ){
      this->_fx = rhs._fx;
    }
    ((Z_px*)this)->operator*=(rhs);
    this->operator%=(_fx);

    return *this;
  }
  GF& GF::square(){ 
    if( !this->_fx.isZero() ){
      ((Z_px*)this)->square();
      this->operator%=(_fx);
    }
    return *this;
  }
  GF& GF::operator/=(const GF& rhs){
    if( this->_fx.isZero() ){
      this->_fx = rhs._fx;
    }
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

  GF& GF::operator^=(const Z& exp){
    if( !this->_fx.isZero() ){
      Exponentiation< GF > *potMod; 
      MethodsFactory::getReference().getFunc(potMod);
      potMod->exponentiation(this,exp);
    }
    return *this;
  }

  GF& GF::operator=(const GF& src){
    Z_px::operator=(src);
    this->_fx = src._fx;
    this->_p = src._p;
    this->_n = src._n;
    return *this;
  }











  GF operator^(GF lhs, const Z& rhs){
    lhs ^= rhs;
    return lhs;
  }


}
