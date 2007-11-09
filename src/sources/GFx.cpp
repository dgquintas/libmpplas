/*
 * $Id$
 */

#include "GFx.h"
#include "Potencia.h"
#include "Errors.h"

namespace mpplas {


  const GFx GFx::ZERO( Z_px::ZERO, GF::NULL_GF );
  const GFx GFx::ONE ( Z_px::ONE, GF::NULL_GF );

  const bool GFx::groupCyclic(true);
  const bool GFx::addCommutative(true); 

  const bool GFx::multAssociative(true);
  const bool GFx::multCommutative(true);
  const bool GFx::unitaryRing(true);
  const bool GFx::divisionRing(true);

  GFx::GFx(const Z_px& poly, const GF& generator)
    : Z_px(poly), _gfGenerator(generator), _fx(generator.getMod()), _p(poly.getCharacteristic())  {
      if( !_fx.isZero() ){
        this->operator%=( _fx );
      }
  }
  GFx::GFx(const Z& value, const GF& generator)
    : Z_px(generator.getCharacteristic()), _gfGenerator(generator), _fx(generator.getMod()), _p(generator.getCharacteristic())
  {}
  GFx::GFx(const GF& generator)
    : Z_px(generator.getCharacteristic()), _gfGenerator(generator), _fx(generator.getMod()), _p(generator.getCharacteristic())
  {}

  GFx::GFx(const GFx& src)
    : Z_px(src), _gfGenerator(src._gfGenerator), _fx(src._fx), _p(src._p)
  {}

  GFx& GFx::operator=(const GFx& src){
    if( this->_gfGenerator != src._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator=");
    }
    //TODO: comprobar que src tiene el mismo generador que *this
    Z_px::operator=(src);
    return *this;
  }

  GFx& GFx::operator+=(const GFx& rhs){
    if( this->_gfGenerator != rhs._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator+=");
    }
    Z_px::operator+=(rhs);
    return *this;
  }
  GFx& GFx::operator-=(const GFx& rhs){ 
    if( this->_gfGenerator != rhs._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator-=");
    }

    Z_px::operator-=(rhs);
    return *this;
  }




  GFx& GFx::operator*=(const GFx& rhs){
    if( this->_fx.isZero() ){
      this->_fx = rhs._fx;
    }
    if( this->_gfGenerator != rhs._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator*=");
    }

    ((Z_px*)this)->operator*=(rhs);
    this->operator%=(_fx);

    return *this;
  }

  GFx& GFx::square(){ 
    if( !this->_fx.isZero() ){
      Z_px::square();
      this->operator%=(_fx);
    }
    return *this;
  }
  GFx& GFx::operator/=(const GFx& rhs){
//    if( this->_fx.isZero() ){
//      this->_fx = rhs._fx;
//    }
    if( this->_gfGenerator != rhs._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator/=");
    }
    GFx inv(rhs);
    inv.invert();
    this->operator*=(inv);

    return *this;
  }

  GFx& GFx::invert(){
    Z_px dummy(_p);
    Z_px::gcd(*this,_fx, this, &dummy);
    return *this;
  }
  GFx GFx::getInverse() const {
    GFx inv(*this);
    inv.invert();
    return inv;
  }

  GFx& GFx::operator^=(const Z& exp){
    if( !this->_fx.isZero() ){
      Exponentiation< GFx > *potMod; 
      MethodsFactory::getReference().getFunc(potMod);
      potMod->exponentiation(this,exp);
    }
    return *this;
  }


  GFx& GFx::fromString(const std::string& str){
    Z_px::fromString(str);
    if( !_fx.isZero() ){
      this->operator%=(_fx);
    }
    return *this;
  }

  Z GFx::toZ() const{
    return this->evaluate(_p);
  }

  GFx& GFx::fromZ(const Z& src) {
    if( src >= this->_gfGenerator.getOrder() ){
      std::ostringstream oss;
      oss << "Integer '" << src << "' too big for a GFx with order '" << this->_gfGenerator.getOrder() << "'";
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
    

  GFx operator^(GFx lhs, const Z& rhs){
    lhs ^= rhs;
    return lhs;
  }

  GFx operator+(GFx lhs, const GFx& rhs){
    lhs += rhs;
    return lhs;
  }
  GFx operator-(GFx lhs, const GFx& rhs){ 
    lhs -= rhs;
    return lhs;
  }

  GFx operator*(GFx lhs, const GFx& rhs){  
    lhs *= rhs;
    return lhs;
  }

  GFx operator/(GFx lhs, const GFx& rhs){  
    lhs /= rhs;
    return lhs;
  }

}

