/*
 * $Id$
 */
#include <algorithm>
#include <cassert>
#include <sstream>

#include "Z_n.h"
#include "MethodsFactory.h"
#include "Potencia.h"


namespace mpplas{

  Z_n Z_n::ZERO( (Digit)0, (Digit)0, false); 
  Z_n Z_n::ONE ( (Digit)1, (Digit)0, false);

  const bool Z_n::addCommutative(true); 
  const bool Z_n::groupCyclic(true);

  const bool Z_n::divisionRing(false);
  const bool Z_n::multAssociative(true);
  const bool Z_n::multCommutative(true);
  const bool Z_n::unitaryRing(true);



  Z_n::Z_n(const Z& mod)
    : Z(), n_(mod)  {
      // equivalence classes modulo n and -n are the same
      if( n_.isNegative() ){
        n_.cambiarSigno();
      }
    }

  Z_n::Z_n(Digit mod)
    : Z(), n_(mod)  {
//      n_ = Z::convertir(mod);
    }


  Z_n::Z_n(SignedDigit mod)
    : Z()
    {
      if( mod < 0 ){
        mod *= -1;
      }
      n_ = Z(mod);
    }

  Z_n::Z_n(const Z& num, const Z& mod, bool reducir)
    : Z(num)
    {
      n_ = mod; 
      if( n_.isNegative() ){
        n_.cambiarSigno();
      }

      if( reducir){
        this->operator%=(n_);
      }
    }

  Z_n::Z_n(const Z& num, Digit mod, bool reducir)
    : Z(num), n_(mod)
    {

      if( reducir ){
        Z::operator%=(n_);
      }
    }


  Z_n::Z_n(const Z& num, SignedDigit mod, bool reducir)
    : Z(num), n_(mod)  {
      if( n_.isNegative() ){
        n_.cambiarSigno();
      }

      if( reducir ){
        Z::operator%=(n_);
      }
    }

  Z_n::Z_n(const Z_n& otro)
    : Z(otro), n_(otro.n_), _exponentiationPrecompts(otro._exponentiationPrecompts) {
      // the modulus (n_) should already be positive
      //assert( otro.n_ > 0 ); //the only cases with mod == 0 are the special cases ZERO and ONE
                             //but those should NOT be copied, thus avoiding having them as a lhs-value
    }


  Z_n& Z_n::operator=(const Z& entero) {
    Z::operator=(entero);
    this->operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator=(const Z_n& enteroModular) {
    Z::operator=(enteroModular);
    if( this->n_.esCero() ){
      this->n_ = enteroModular.n_;
    }
    else if( enteroModular.n_ > n_ ){
      this->operator%=(n_);
    }

    return *this;
  }

 
 
 
  Z_n& Z_n::operator+=(const Z_n& der) {
    if( n_.esCero() ){
      n_ = der.n_;
    }
    Z::operator+=(der);
    if( *this >= n_ ){
      Z::operator%=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator-=(const Z_n& der){
    if( n_.esCero() ){
      n_ = der.n_;
    }
    Z::operator-=(der);

    if( *this < (Digit)0 ){
      Z::operator%=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator*=(const Z_n& der)  {
    if( n_.esCero() ){
      n_ = der.n_;
      if( this->esUno() ){
        Z::operator=(der);
      }
      else{ // must be zero
        this->hacerCero();
      }
    }
    else{
      Z::operator*=(der);
      Z::operator%=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator/=(const Z_n& der)  {
    if( n_.esCero() ){
      n_ = der.n_;
      if( this->esUno() ){
        Exponentiation<Z_n> *potMod; MethodsFactory::getReference().getFunc(potMod);
        (*this) = der;
        potMod->invert(this);
      }
      else{ // must be zero
        throw Errors::DivisionPorCero();  
      }
    }
    else{
      Exponentiation<Z_n> *potMod; MethodsFactory::getReference().getFunc(potMod);
      Z_n inv(der);
      potMod->invert(&inv);
      operator*=(inv);
    }

    return *this;
  }

 
 
 
  Z_n& Z_n::operator+=(const Z& der) {
    assert( !this->n_.esCero() );
    Z::operator+=(der);
    if( *this >= n_ ){
      Z::operator%=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator-=(const Z& der){
    assert( !this->n_.esCero() );
    Z::operator-=(der);

    if( *this < (Digit)0 ){
      Z::operator%=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator*=(const Z& der)  {
    assert( !n_.esCero() );
    Z::operator*=(der);
    Z::operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator/=(const Z& der)  {
    assert( !n_.esCero() );
    Z_n inv(der, n_);
    Exponentiation<Z_n> *potMod; MethodsFactory::getReference().getFunc(potMod);
    potMod->invert(&inv);
    operator*=(inv);

    return *this;
  }


  /* simple prec */
  Z_n& Z_n::operator+=(const SignedDigit derC) {
    assert( !n_.esCero() );
    Z::operator+=(derC);

    //substraction is less expensive than division.
    //Besides, given the fact that derC is a basic type,
    //we can't have gone very far away from the modulus n_
    while( *this >= n_ ){
      Z::operator-=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator-=(const SignedDigit derC) {
    assert( !n_.esCero() );

    Z::operator-=(derC);

    //substraction is less expensive than division.
    //Besides, given the fact that derC is a basic type,
    //we can't have gone very far away from the modulus n_
    while( *this < (Digit)0 ){
      Z::operator+=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator*=(const SignedDigit derC)  {
    assert( !n_.esCero() );

    Z::operator*=(derC);
    Z::operator%=(n_);


    return *this;
  }

  Z_n& Z_n::operator/=(const SignedDigit derC) {
    assert( !n_.esCero() );
    Z_n derEntero(Z(derC), n_);
    
    operator/=(derEntero);
    return *this;
  }


  Z_n& Z_n::operator+=(const Digit derC) {
    assert( !n_.esCero() );
    Digit der = (derC % n_).toDigit();

    Z::operator+=(der);

    if( *this >= n_ )
      Z::operator-=(n_);

    return *this;
  }

  Z_n& Z_n::operator-=(const Digit derC) { 
    assert( !n_.esCero() );
    Digit der = (derC % n_).toDigit();

    Z::operator-=(der);

    if( *this < (Digit)0 )
      Z::operator+=(n_);

    return *this;
  }

  Z_n& Z_n::operator*=(const Digit derC) {
    assert( !n_.esCero() );
    Digit der = (derC % n_).toDigit();

    Z::operator*=(der);
    Z::operator%=(n_);


    return *this;
  }

  Z_n& Z_n::operator/=(const Digit derC) {
    assert( !n_.esCero() );
    Z_n derEntero(Z(derC), n_);
    
    operator/=(derEntero);
    return *this;

    return *this;

  }


  Z_n& Z_n::operator^=(const Z& e) {
    if( n_.esCero() && e.isPositive() ){
      return Z_n::ONE;
    }
    ClasicoConBarrett potMod;
    RedBarrett rb; 
    if( _exponentiationPrecompts.esCero() ){
      _exponentiationPrecompts = rb.precomputaciones( n_ );
    }
    potMod.barrettStep(this, e, n_, _exponentiationPrecompts);
    return *this;
  }

  Z_n& Z_n::inverse(){
    this->operator^=((SignedDigit)-1);
    return *this;
  }


  std::istream& 
    operator>>(std::istream& is, Z_n& numero) {
      operator>>(is, (Z&)numero);
      numero %= numero.n_;

      return is;
    }


  Z_n operator+(Z_n izq, const Z_n& der) {
    izq += der;

    return izq;
  }

  Z_n operator-(Z_n izq, const Z_n& der) {
    izq -= der;

    return izq;
  } 

  Z_n operator*(Z_n izq, const Z_n& der) {
    izq *= der;

    return izq;
  }

  Z_n operator/(Z_n izq, const Z_n& der)
  {
    if( der.esCero() ){
      throw Errors::DivisionPorCero();  
    }

    izq /= der;

    return izq;
  }









  Z_n operator+(Z_n izq, const Z& der){
    izq += der;

    return izq;
  }

  Z_n operator-(Z_n izq, const Z& der){
    izq -= der;

    return izq;
  } 

  Z_n operator*(Z_n izq, const Z& der) {
    izq *= der;

    return izq;
  }

  Z_n operator/(Z_n izq, const Z& der) {
    if( der.esCero() )
      throw Errors::DivisionPorCero();  

    izq /= der;

    return izq;
  }


  Z_n operator+(const SignedDigit corto, Z_n largo) {
    largo += corto;
    return largo;
  }

  Z_n operator-(const SignedDigit corto, Z_n largo) {
    Z temp(corto);
    temp %= largo.getMod();
    temp -= largo;
    //largo.cambiarSigno();
    // en Z_n_n el cambio de signo es equivalente a restar el n� a cambiar
    // de signo al modulo
    if(temp.isNegative() ){
      temp += largo.getMod();
    }

    return Z_n(temp, largo.getMod(), false);
  }

  Z_n operator*(const SignedDigit corto, Z_n largo) {
    largo *= corto;
    return largo;
  }

  Z_n operator/(const SignedDigit corto, const Z_n& largo) {
    Z_n cortoZn(Z(corto), largo.getMod() );

    cortoZn /= largo;

    return cortoZn;

  }



  Z_n operator+(Z_n largo, const SignedDigit corto) {
    largo += corto;
    return largo;
  }
  Z_n operator-(Z_n largo, const SignedDigit corto) {
    largo -= corto;
    return largo;
  }
  Z_n operator*(Z_n largo, const SignedDigit corto) {
    largo *= corto;
    return largo;
  }
  Z_n operator/(Z_n largo, const SignedDigit corto) {
    if( corto == 0 )
      throw Errors::DivisionPorCero(); 

    largo /= corto;
    return largo;
  }










  Z_n operator+(const Digit corto, Z_n largo)
  {
    largo += corto;
    return largo;
  }

  Z_n operator-(const Digit corto, Z_n largo)
  {
    Z temp(corto);
    temp %= largo.getMod();
    temp -= largo;
    //largo.cambiarSigno();
    // en Z_n_n el cambio de signo es equivalente a restar el n� a cambiar
    // de signo al modulo
    if(temp.isNegative())
      temp += largo.getMod();

    return Z_n(temp, largo.getMod(),false) ;
  }

  Z_n operator*(const Digit corto, Z_n largo)
  {
    largo *= corto;
    return largo;
  }

  Z_n operator/(const Digit corto, const Z_n& largo)
  {
    if( largo.esCero() )
      throw Errors::DivisionPorCero();

    Z_n cortoZ_n(Z_n(corto), largo.getMod() );

    cortoZ_n /= largo;

    return cortoZ_n;

  }



  Z_n operator+(Z_n largo, const Digit corto)
  {
    largo += corto;
    return largo;
  }
  Z_n operator-(Z_n largo, const Digit corto)
  {
    largo -= corto;
    return largo;
  }
  Z_n operator*(Z_n largo, const Digit corto)
  {
    largo *= corto;
    return largo;
  }

  Z_n operator/(Z_n largo, const Digit corto)
  {
    if( corto == 0 )
      throw Errors::DivisionPorCero();

    largo /= corto;
    return largo;
  }









  Z_n operator^(Z_n base, const Z& exp) {
    base ^= exp;
    return base;
  }

  Z_n operator^(Z_n base, const Digit exp) {
    base ^= Z(exp);
    return base;
  }

  Z_n operator^(Z_n base, const SignedDigit exp) {
    base ^= Z(exp);
    return base;
  }

  Z_n& Z_n::cuadrado(void) {
    Z::cuadradoModular(n_);
    return *this;
  }
 

//  std::string Z_n::toString(void) const {
//    // presents the polynomial as [(coeff_n, exp_n)...(coeff_0, 0)]
//    std::ostringstream oss;
//    oss << "(" << (*this) << ", " << n_<< ")";
//    return oss.str();
//  }







}
