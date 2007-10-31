/*
 * $Id$
 */


#include "GF.h"
#include "Potencia.h"
#include "MethodsFactory.h"
#include "Random.h"

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

  GF& GF::operator^=(const Z& exp){
    Exponentiation< GF > *potMod; 
    MethodsFactory::getReference().getFunc(potMod);
    potMod->exponentiation(this,exp);
    return *this;
  }

  GF& GF::operator=(const GF& src){
    Z_px::operator=(src);
    this->_fx = src._fx;
    this->_p = src._p;
    this->_n = src._n;
    return *this;
  }

  bool GF::_isIrreducible(const Z_px& fx, const Z& p ){
    assert( fx.getCharacteristic() == p );
    const int m = fx.getDegree();
    const Z_px x(Z_px(1, 1, p));
    GF u(x,fx); 
    Exponentiation< GF > *potMod; 
    MethodsFactory::getReference().getFunc(potMod);

    for(int i = 0; i < (m/2); i++){
      potMod->exponentiation(&u,p);
      if( !(Z_px::gcd(fx, u - x).isOne()) ){
        return false; //reducible
      }
    }
    return true; //irreducible

  }
  Z_px GF::_genIrreducible(const int m, const Z& p){
    RandomFast *rnd; MethodsFactory::getReference().getFunc(rnd);
    
    Z_px fx(Z::ONE, m, p);
    do{
      do {
        fx[0] = rnd->getIntegerBounded(p);
      } while(fx[0].esCero());

      for( int i = 1; i < m; i++){
        fx[i] = rnd->getIntegerBounded(p);
      }
    }
    while( !_isIrreducible(fx, p) );

    return fx;
    
  }
//  Z_px GF::_genPrimitivePolynomial(const int degree){
//  }



}
