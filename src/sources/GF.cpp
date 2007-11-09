/*
 * $Id$
 */



#include "GF.h"
#include "Potencia.h"
#include "MethodsFactory.h"
#include "PolynomialUtils.h"
#include "Errors.h"
#include "GFx.h"

namespace mpplas {


  const GF GF::NULL_GF( GF(Z(0),Z_px::ZERO ) );

 GF::GF(const Z& p, const int n, const bool usePrimitiveMod)
    : _p(p), _n(n), _fx(p), _primitiveMod(usePrimitiveMod)  {
      if( usePrimitiveMod ){
        _fx = PolynomialUtils::generatePrimitive<mpplas::Z_px>(n,p);
      }
      else{
        _fx = PolynomialUtils::generateIrreducible<mpplas::Z_px>(n,p);
      }
  }

  GF::GF(const Z& p, const Z_px& fx)
    : _n( fx.getDegree() ), _p(p), _fx(fx), _primitiveMod(false) {
    if( fx.getCharacteristic() != p ){
      throw Errors::InvalidArgument("Invalid characteristic for f(x) constructing GF");
    }
  }

//  GF::GF(const Z_px& poly, const Z_px& fx)
//    : Z_px(poly), _n( poly.getDegree() ), _fx(fx), _p( poly.getCharacteristic() ), _primitiveMod(false)
//  {
//    if( fx.getCharacteristic() != poly.getCharacteristic() ){
//      throw Errors::InvalidArgument("Invalid characteristic for f(x) constructing GF");
//    }
//    if( !fx.isZero() ){
//      this->operator%=(fx);
//    }
//  }


  GF::GF(const GF& src)
    : _fx(src._fx), _p(src._p), _n(src._n), _primitiveMod(src._primitiveMod)
  {}

  GFx GF::getElement(const Z_px& poly) const{
    assert( poly.getCharacteristic() == this->_p );
    const GFx elem(poly, *this);
    return elem;
  }
  GFx GF::getElement(const std::string& poly) const{
    const GFx elem(Z_px(poly, this->_p), *this);
    return elem;
  }
  GFx GF::getElement(const Z& value) const { 
    const GFx elem(value, *this);
    return elem;
  }
  GFx GF::getElement() const{
    const GFx elem(*this);
    return elem;
  }


  bool GF::operator==(const GF& rhs){
    //it's convenient to start comparing by 
    //the less expensive to compare data types
    if( (this->_primitiveMod == rhs._primitiveMod) &&
        (this->_n == rhs._n) &&
        (this->_p == rhs._p) &&
        (this->_fx== rhs._fx) ){
      return true;
    }
    else{
      return false;
    }
  }

  bool GF::operator!=(const GF& rhs){
    return !(this->operator==(rhs));
  }

}
