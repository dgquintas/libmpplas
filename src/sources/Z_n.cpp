/*
 * $Id$
 */

#include "Z_n.h"
#include "MethodsFactory.h"
#include "Potencia.h"
#include <algorithm>


namespace mpplas{

  Z_n::Z_n(const Z& mod)
    : Z(), n_(mod)
    {
      // equivalence classes modulo n and -n are the same
      if( n_.esNegativo() ){
        n_.cambiarSigno();
      }
    }

  Z_n::Z_n(Digit mod)
    : Z(), n_(mod)
    {
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
      if( n_.esNegativo() ){
        n_.cambiarSigno();
      }

      if( reducir)
        this->operator%=(n_);
    }

  Z_n::Z_n(const Z& num, Digit mod, bool reducir)
    : Z(num), n_(mod)
    {

      if( reducir ){
        Z::operator%=(n_);
      }
    }


  Z_n::Z_n(const Z& num, SignedDigit mod, bool reducir)
    : Z(num), n_(mod)
    {
      if( n_.esNegativo() ){
        n_.cambiarSigno();
      }

      if( reducir )
        Z::operator%=(n_);
    }

  Z_n::Z_n(const Z_n& otro)
    : Z(otro), n_(otro.n_)
    {
      // the modulus (n_) should already be positive
    }


  Z_n& Z_n::operator=(const Z& entero)
  {
    Z::operator=(entero);
    this->operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator=(const Z_n& enteroModular) {
    Z::operator=(enteroModular);
    if( enteroModular.n_ > n_ )
      this->operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator+=(const Z& der) {
    Z::operator+=(der);

    if( *this >= n_ ){
      Z::operator%=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator-=(const Z& der){
    Z::operator-=(der);

    if( *this < (Digit)0 )
      Z::operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator*=(const Z& der)  {
    Z::operator*=(der);
    Z::operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator/=(const Z& der)  {
    Z_n inv(n_);
    PotModular *potMod; MethodsFactory::getReference().getFunc(potMod);
    inv = Z_n(potMod->inversa(der, n_), n_, false);
    operator*=(inv);

    return *this;
  }


  /* simple prec */
  Z_n& Z_n::operator+=(const SignedDigit derC) {
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

    Z::operator-=(derC);

    //substraction is less expensive than division.
    //Besides, given the fact that derC is a basic type,
    //we can't have gone very far away from the modulus n_
    while( *this < (Digit)0 ){
      Z::operator+=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator*=(const SignedDigit derC)
  {

    Z::operator*=(derC);
    Z::operator%=(n_);


    return *this;
  }

  Z_n& Z_n::operator/=(const SignedDigit derC)
  {
    Z_n derEntero(Z(derC), n_);

    PotModular *potMod; MethodsFactory::getReference().getFunc(potMod);
    Z_n inv(potMod->inversa(derEntero, n_), n_, false);

    operator*=(inv);

    return *this;
  }


  Z_n& Z_n::operator+=(const Digit derC)
  {
    Digit der = (derC % n_).toDigit();

    Z::operator+=(der);

    if( *this >= n_ )
      Z::operator-=(n_);

    return *this;
  }

  Z_n& Z_n::operator-=(const Digit derC)
  { 
    Digit der = (derC % n_).toDigit();

    Z::operator-=(der);

    if( *this < (Digit)0 )
      Z::operator+=(n_);

    return *this;
  }

  Z_n& Z_n::operator*=(const Digit derC)
  {
    Digit der = (derC % n_).toDigit();

    Z::operator*=(der);
    Z::operator%=(n_);


    return *this;
  }

  Z_n& Z_n::operator/=(const Digit derC)
  {
    Digit der = (derC % n_).toDigit();

    Z_n inv(n_);
    Z derEntero(der);

    PotModular *potMod; MethodsFactory::getReference().getFunc(potMod);
    inv = Z_n(potMod->inversa(Z(der), n_), n_, false);
    operator*=(inv);

    return *this;

  }


  Z_n& Z_n::operator^=(const Digit e)
  {
    const Z eZ(e);
    PotModular *potMod; MethodsFactory::getReference().getFunc(potMod);
    potMod->potModular(this, eZ, n_);
    return *this;
  }

  Z_n& Z_n::operator^=(const SignedDigit e) 
  {
    PotModular *potMod; MethodsFactory::getReference().getFunc(potMod);
    Z eZ(e);
    potMod->potModular(this, eZ, n_);
    return *this;
  }

  Z_n& Z_n::operator^=(const Z& e)
  {
    PotModular *potMod; MethodsFactory::getReference().getFunc(potMod);
    potMod->potModular(this, e, n_);
    return *this;
  }

  Z_n& Z_n::inverse(){
    this->operator^=((SignedDigit)-1);
    return *this;
  }


  std::istream& 
    operator>>(std::istream& is, Z_n& numero)
    {
      operator>>(is, (Z&)numero);
      numero %= numero.n_;

      return is;
    }


//  Z_n operator+(Z_n izq, const Z_n& der)
//  {
//    izq += der;
//
//    return izq;
//  }
//
//  Z_n operator-(Z_n izq, const Z_n& der)
//  {
//    izq -= der;
//
//    return izq;
//  } 
//
//  Z_n operator*(Z_n izq, const Z_n& der)
//  {
//    izq *= der;
//
//    return izq;
//  }
//
//  Z_n operator/(Z_n izq, const Z_n& der)
//  {
//    if( der.esCero() )
//      throw Errors::DivisionPorCero();  
//
//    izq /= der;
//
//    return izq;
//  }


  Z_n operator+(Z_n izq, const Z& der)
  {
    izq += der;

    return izq;
  }

  Z_n operator-(Z_n izq, const Z& der)
  {
    izq -= der;

    return izq;
  } 

  Z_n operator*(Z_n izq, const Z& der)
  {
    izq *= der;

    return izq;
  }

  Z_n operator/(Z_n izq, const Z& der)
  {
    if( der.esCero() )
      throw Errors::DivisionPorCero();  

    izq /= der;

    return izq;
  }


  Z_n operator+(const SignedDigit corto, Z_n largo)
  {
    largo += corto;
    return largo;
  }

  Z_n operator-(const SignedDigit corto, Z_n largo)
  {
    Z temp(corto);
    temp %= largo.modulo();
    temp -= largo;
    //largo.cambiarSigno();
    // en Z_n_n el cambio de signo es equivalente a restar el n� a cambiar
    // de signo al modulo
    if(temp.esNegativo() ){
      temp += largo.modulo();
    }

    return Z_n(temp, largo.modulo(), false);
  }

  Z_n operator*(const SignedDigit corto, Z_n largo)
  {
    largo *= corto;
    return largo;
  }

  Z_n operator/(const SignedDigit corto, const Z_n& largo)
  {
    Z_n cortoZn(Z(corto), largo.modulo() );

    cortoZn /= largo;

    return cortoZn;

  }



  Z_n operator+(Z_n largo, const SignedDigit corto)
  {
    largo += corto;
    return largo;
  }
  Z_n operator-(Z_n largo, const SignedDigit corto)
  {
    largo -= corto;
    return largo;
  }
  Z_n operator*(Z_n largo, const SignedDigit corto)
  {
    largo *= corto;
    return largo;
  }
  Z_n operator/(Z_n largo, const SignedDigit corto)
  {
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
    temp %= largo.modulo();
    temp -= largo;
    //largo.cambiarSigno();
    // en Z_n_n el cambio de signo es equivalente a restar el n� a cambiar
    // de signo al modulo
    if(temp.esNegativo())
      temp += largo.modulo();

    return Z_n(temp, largo.modulo(),false) ;
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

    Z_n cortoZ_n(Z_n(corto), largo.modulo() );

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









  Z_n operator^(Z_n base, const Z& exp)
  {
    base ^= exp;
    return base;
  }

  Z_n operator^(Z_n base, const Digit exp)
  {
    base ^= exp;
    return base;
  }

  Z_n operator^(Z_n base, const SignedDigit exp)
  {
    base ^= exp;
    return base;
  }

  Z_n& Z_n::cuadrado(void)
  {
    Z::cuadradoModular(n_);
    return *this;
  }
  
}
