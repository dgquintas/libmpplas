/*
 * $Id$
 */

#include <sstream>
#include "Digit_p.h"
#include "MethodsFactory.h"
#include "Primos.h"
#include "Z.h"

namespace mpplas{

  const Digit_p Digit_p::ZERO( (Digit)0, (Digit)0); 
  const Digit_p Digit_p::ONE ( (Digit)1, (Digit)0);

  Digit_p::Digit_p( const Digit p )
    : _p(p), value(0)
  {
    if( p != 0){
      PrimeTest *testPrimes;
      MethodsFactory::getReference().getFunc(testPrimes);
      assert( testPrimes->isPrime(p) ); //TODO: throw exception
    }
  }

  Digit_p::Digit_p( const Digit n, const Digit p )
    : _p(p), value(n)
  {
    if( p != 0){
      PrimeTest *testPrimes;
      MethodsFactory::getReference().getFunc(testPrimes);
      assert( testPrimes->isPrime(p) ); //TODO: throw exception
      value %= p;
    }
  }

  Digit_p::Digit_p( const Digit_p& src)
    : value(src.value), _p(src._p)
  {}

  Digit_p& Digit_p::operator=(const Digit_p& src){
    this->value = src.value;
    this->_p = src._p;
    return *this;
  }

  std::string Digit_p::toString() const{
    std::ostringstream oss;
    oss << this->value;
    return oss.str();
  }

  Digit_p& Digit_p::invert(){
    Z inv, dummy;
    Z::gcd(this->value, this->_p, &inv, &dummy);
    if( inv.isNegative() ){
      inv += this->_p;
    }
    assert( inv.longitud() == 1 );
    this->value = inv[0];
    return *this;
  }

  Digit_p Digit_p::getInverse() const{
    Digit_p tmp(*this);
    tmp.invert();
    return tmp;
  }


  bool Digit_p::operator==(const Digit_p& rhs) const{
    return this->value == rhs.value; 
  }
  bool Digit_p::operator!=(const Digit_p& rhs) const{
    return this->value != rhs.value; 
  }
  Digit_p& Digit_p::operator+=(const Digit rhs){
    this->value += rhs;
    if( this->value >= _p ){
      this->value %= this->_p;
    }
    return *this;
  }
  Digit_p& Digit_p::operator-=(const Digit rhs){
    if( rhs> this->value){ // this = mod - (rhs - this)
      this->value += this->_p;
      this->value -= (rhs % this->_p);
    }
    else{
      this->value -= (rhs % this->_p);
    }
    return *this;

  }
  Digit_p& Digit_p::operator*=(const Digit rhs){
    this->value *= rhs;
    this->value %= this->_p;
    return *this;

  }
  Digit_p& Digit_p::operator/=(const Digit_p& rhs){
    this->operator*=( rhs.getInverse() );
    return *this;

  }
  Digit_p& Digit_p::operator/=(const Digit rhs){
    this->operator/=( Digit_p(rhs,_p) );
    return *this;
  }


  /////////////////////////////

  std::ostream& operator<<(std::ostream& out, const Digit_p& n){
    const std::ios_base::fmtflags ff(out.flags());
    if( ff & std::ios_base::showpos ){
      out << "+";
    }
    out << n.value;
    return out;
  }


  std::istream& operator>>(std::istream& in, Digit_p& n){
    in >> n.value;
    n.value %= n.getMod();
    return in;
  }

  Digit_p operator+(Digit_p lhs, const Digit rhs){
    lhs += rhs;
    return lhs;
  }
  Digit_p operator-(Digit_p lhs, const Digit rhs){
    lhs -= rhs;
    return lhs;
  }
  Digit_p operator*(Digit_p lhs, const Digit rhs){
    lhs *= rhs;
    return lhs;
  }
  Digit_p operator/(Digit_p lhs, const Digit rhs){
    lhs /= rhs;
    return lhs;
  }
  Digit_p operator/(Digit_p lhs, const Digit_p& rhs){
    lhs /= rhs;
    return lhs;
  }




} /* namespace mpplas */

