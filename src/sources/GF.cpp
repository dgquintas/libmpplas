/*
 * $Id$
 */



#include "GF.h"
#include "Potencia.h"
#include "MethodsFactory.h"
#include "PolynomialUtils.h"
#include "Errors.h"

namespace mpplas {


  const GF GF::ZERO( GF(Z_px(Z_p((Digit)0, (Digit)0, false, false), 0, 0), Z_px::ZERO ) );
  const GF GF::ONE ( GF(Z_px(Z_p((Digit)1, (Digit)0, false, false), 0, 0), Z_px::ZERO ) );

  const bool GF::groupCyclic(true);
  const bool GF::addCommutative(true); 

  const bool GF::multAssociative(true);
  const bool GF::multCommutative(true);
  const bool GF::unitaryRing(true);
  const bool GF::divisionRing(true);


  GF::GF(const Z& p, const int n, const bool usePrimitiveMod)
    : Z_px(p), _p(p), _n(n), _fx(p), _primitiveMod(usePrimitiveMod)  {
      if( usePrimitiveMod ){
        _fx = PolynomialUtils::generatePrimitive<mpplas::Z_px>(n,p);
      }
      else{
        _fx = PolynomialUtils::generateIrreducible<mpplas::Z_px>(n,p);
      }
  }

  GF::GF(const Z& p, const Z_px& fx)
    : Z_px(p), _n( fx.getDegree() ), _p(p), _fx(fx), _primitiveMod(false) {
    if( fx.getCharacteristic() != p ){
      throw Errors::InvalidArgument("Invalid characteristic for f(x) constructing GF");
    }
  }

  GF::GF(const Z_px& poly, const Z_px& fx)
    : Z_px(poly), _n( poly.getDegree() ), _fx(fx), _p( poly.getCharacteristic() ), _primitiveMod(false)
  {
    if( fx.getCharacteristic() != poly.getCharacteristic() ){
      throw Errors::InvalidArgument("Invalid characteristic for f(x) constructing GF");
    }
    if( !fx.isZero() ){
      this->operator%=(fx);
    }
  }


  GF& GF::operator+=(const GF& rhs){
    Z_px::operator+=(rhs);
    return *this;
  }
  GF& GF::operator-=(const GF& rhs){
    Z_px::operator-=(rhs);
    return *this;
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
      Z_px::square();
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
    this->_primitiveMod = src._primitiveMod;
    return *this;
  }

  GF& GF::fromString(const std::string& str){
    Z_px::fromString(str);
    if( !_fx.isZero() ){
      this->operator%=(_fx);
    }
    return *this;
  }

  Z GF::toZ() const{
    return this->evaluate(_p);
  }

  GF& GF::fromZ(const Z& src) {
    if( src >= this->getOrder() ){
      std::ostringstream oss;
      oss << "Integer '" << src << "' too big for a GF with order '" << this->getOrder() << "'";
      throw Errors::TooBig( oss.str() );
    }

    this->_data.clear();
    Z_p q(_p,false),r(_p,false); //don't check for the primality of _p
    divMod(src, _p, &q, &r);
    this->_data.push_back(r);
    while( q >= _p ){
      divMod(Z(q), _p, &q, &r);
      this->_data.push_back(r);
    }
    // q < _p
    this->_data.push_back(q);


    return *this;
  }
    

  GF operator^(GF lhs, const Z& rhs){
    lhs ^= rhs;
    return lhs;
  }

  GF operator+(GF lhs, const GF& rhs){
    lhs += rhs;
    return lhs;
  }
  GF operator-(GF lhs, const GF& rhs){ 
    lhs -= rhs;
    return lhs;
  }

  GF operator*(GF lhs, const GF& rhs){  
    lhs *= rhs;
    return lhs;
  }

  GF operator/(GF lhs, const GF& rhs){  
    lhs /= rhs;
    return lhs;
  }




}
