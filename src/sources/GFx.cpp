/*
 * $Id$
 */

#include <cctype>
#include "GFx.h"
#include "Potencia.h"
#include "Errors.h"

namespace mpplas {


  const GFx GFx::ZERO( Z_px::ZERO, GF::NULL_GF );
  const GFx GFx::ONE ( Z_px::ONE, GF::NULL_GF );
  
  bool GFx::_showPBR(false);

  const bool GFx::groupCyclic(true);
  const bool GFx::addCommutative(true); 

  const bool GFx::multAssociative(true);
  const bool GFx::multCommutative(true);
  const bool GFx::unitaryRing(true);
  const bool GFx::divisionRing(true);


  void GFx::setShowPBR(const bool printPBR){
    GFx::_showPBR = printPBR;
    return;
  }
  bool GFx::isShowPBR(){
    return GFx::_showPBR;
  }

  GFx::GFx()
    : Z_px(Z_px::ZERO), _gfGenerator(GF::NULL_GF)
  {}


  GFx::GFx(const Z_px& poly, const GF& generator)
    : Z_px(poly), _gfGenerator(generator)   {
      if( !_gfGenerator.getMod().isZero() ){
        this->operator%=( _gfGenerator.getMod() );
      }
  }
  GFx::GFx(const Z& value, const GF& generator)
    : Z_px(generator.getCharacteristic()), _gfGenerator(generator) {
    this->setIntegerValue(value);
  }
  GFx::GFx(const GF& generator)
    : Z_px(generator.getCharacteristic()), _gfGenerator(generator) 
  {}

  GFx::GFx(const GFx& src)
    :  Z_px(src), Field< GFx >(), _gfGenerator(src._gfGenerator)
  {}

  GFx& GFx::operator=(const GFx& src){
    if( this->_gfGenerator == GF::NULL_GF ){
      this->_gfGenerator = src._gfGenerator;
    } 
//    else if( this->_gfGenerator != src._gfGenerator ){
//      throw Errors::InconsistentGFGenerator("In GFx::operator=");
//    }
    Z_px::operator=(src);
    return *this;
  }



  GFx& GFx::operator+=(const GFx& rhs){
    if( this->_gfGenerator == GF::NULL_GF ){
      this->_gfGenerator = rhs._gfGenerator;
    } 
    else if( this->_gfGenerator != rhs._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator+=");
    }
    Z_px::operator+=(rhs);
    return *this;
  }
  GFx& GFx::operator-=(const GFx& rhs){ 
    if( this->_gfGenerator == GF::NULL_GF ){
      this->_gfGenerator = rhs._gfGenerator;
    } 
    else if( this->_gfGenerator != rhs._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator-=");
    }

    Z_px::operator-=(rhs);
    return *this;
  }




  GFx& GFx::operator*=(const GFx& rhs){
    if( this->_gfGenerator == GF::NULL_GF ){
      this->_gfGenerator = rhs._gfGenerator;
    } 
    if( this->_gfGenerator != rhs._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator*=");
    }

    ((Z_px*)this)->operator*=(rhs);

    this->operator%=(_gfGenerator.getMod());

    return *this;
  }

  GFx& GFx::square(){ 
    if( !this->_gfGenerator.getMod().isZero() ){
      Z_px::square();
      this->operator%=(_gfGenerator.getMod());
    }
    return *this;
  }
  GFx& GFx::operator/=(const GFx& rhs){
    if( this->_gfGenerator == GF::NULL_GF ){
      this->_gfGenerator = rhs._gfGenerator;
    } 
    else if( this->_gfGenerator != rhs._gfGenerator ){
      throw Errors::InconsistentGFGenerator("In GFx::operator/=");
    }
    GFx inv(rhs);
    inv.invert();
    this->operator*=(inv);

    return *this;
  }

  GFx& GFx::invert(){
    if( this->isZero() ){
      std::ostringstream oss;
      oss << "Zero element cannot be inverted; ";
      GEN_TRACE_INFO_OSS(oss);
      throw Errors::NonInvertibleElement(oss.str());
    }
    else{
      Z_px dummy(_gfGenerator.getCharacteristic());
      Z_px::gcd(*this, _gfGenerator.getMod(), this, &dummy);
    }
    return *this;
  }
  GFx GFx::getInverse() const {
    GFx inv(*this);
    inv.invert();
    return inv;
  }

  GFx& GFx::operator^=(const Z& exp){
    if( !this->_gfGenerator.getMod().isZero() ){
      Exponentiation< GFx > *potMod; 
      MethodsFactory::getReference().getFunc(potMod);
      potMod->exponentiation(this,exp);
    }
    return *this;
  }


//  GFx& GFx::fromString(const std::string& str){
//    Z_px::fromString(str);
//    if( !_gfGenerator.getMod().isZero() ){
//      this->operator%=(_gfGenerator.getMod());
//    }
//    return *this;
//  }

  Z GFx::getIntegerValue() const{
    return this->evaluate(_gfGenerator.getCharacteristic());
  }

  GFx& GFx::setIntegerValue(const Z& src) {
//    if( src >= this->_gfGenerator.getOrder() ){
//      std::ostringstream oss;
//      oss << "Integer '" << src << "' too big for a GFx with order '" << this->_gfGenerator.getOrder() << "'";
//      throw Errors::TooBig( oss.str() );
//    }

    const Z& p(_gfGenerator.getCharacteristic());
    this->_data.clear();
    Z_p q(p,false),r(p,false); //don't check for the primality of p
    
    divMod(src % this->_gfGenerator.getOrder(), p, &q, &r);
    this->_data.push_back(r);
    while( q >= p ){
      divMod(Z(q), p, &q, &r);
      this->_data.push_back(r);
    }
    // q < p
    this->_data.push_back(q);

    this->_eraseLeadingZeros();
    return *this;
  }

  Z_px GFx::getPolynomialValue() const{
    return *this;
  }

  GFx& GFx::setPolynomialValue(const Z_px& src){
    Z_px::operator=(src);
    if( !_gfGenerator.getMod().isZero() ){
      this->operator%=( _gfGenerator.getMod() );
    }
    return *this;
  }

  std::string GFx::getPBRString() const{
    std::ostringstream oss;
    oss << (const Z_px&)*this; 
    return oss.str();
  }

  std::string GFx::toHRString() const {
    std::ostringstream oss;
    oss << *this;
    return oss.str();
  }

  std::ostream& operator<<(std::ostream& out, const GFx& elem){
    if( GFx::isShowPBR() ){
      out << (const Z_px&)elem; 
    }
    else{
      out << elem.getIntegerValue();
    }
    return out;
  }
  std::istream& operator>>(std::istream& in, GFx& elem){
    char c;
    in >> c;
    //if c == '[', it's assumed a polynomial rep is being fed
    //otherwise, if c == '0'..'9', it's a assumed it's an integer
    //else, error
    if( c == '[' ){
      in.putback(c);
      operator>>(in, (Z_px&)elem);
    }
    else if( std::isdigit(c) ){
      in.putback(c);
      Z tmp;
      operator>>(in, tmp);
      elem.setIntegerValue(tmp);
    }
    else{
      throw Errors::InvalidSymbol(std::string(1,c));
    }
    return in;
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

