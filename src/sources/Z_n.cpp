/*
 * $Id$
 */

#include "Z_n.h"
#include "Funciones.h"
#include "Potencia.h"
#include <algorithm>


namespace numth{

  Z_n::Z_n(const Z& mod)
    : Z(), n_(mod)
    {
      // equivalence classes modulo n and -n are the same
      if( n_.esNegativo() ){
        n_.cambiarSigno();
      }
    }

  Z_n::Z_n(Cifra mod)
    : Z(), n_(mod)
    {
//      n_ = Z::convertir(mod);
    }


  Z_n::Z_n(CifraSigno mod)
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

  Z_n::Z_n(const Z& num, Cifra mod, bool reducir)
    : Z(num), n_(mod)
    {

      if( reducir ){
        Z::operator%=(n_);
      }
    }


  Z_n::Z_n(const Z& num, CifraSigno mod, bool reducir)
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

  Z_n& Z_n::operator=(const Z_n& enteroModular)
  {

    Z::operator=(enteroModular);
    if( enteroModular.n_ > n_ )
      this->operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator+=(const Z& der)
  {
    Z::operator+=(der);

    if( *this >= n_ )
      Z::operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator-=(const Z& der)
  {
    Z::operator-=(der);

    if( *this < (Cifra)0 )
      Z::operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator*=(const Z& der)
  {
    Z::operator*=(der);
    Z::operator%=(n_);

    return *this;
  }

  Z_n& Z_n::operator/=(const Z& der)
  {
    Z_n inv(n_);
    Funciones *funcs = Funciones::getInstance();
    PotModular *potMod; funcs->getFunc(potMod);
    inv = Z_n(potMod->inversa(der, n_), n_, false);
    operator*=(inv);

    return *this;
  }


  /* simple prec */
  Z_n& Z_n::operator+=(const CifraSigno derC)
  {
    Z::operator+=(derC);

    //substraction is less expensive than division.
    //Besides, given the fact that derC is a basic type,
    //we can't have gone very far away from the modulus n_
    while( *this >= n_ ){
      Z::operator-=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator-=(const CifraSigno derC)
  {

    Z::operator-=(derC);

    //substraction is less expensive than division.
    //Besides, given the fact that derC is a basic type,
    //we can't have gone very far away from the modulus n_
    while( *this < (Cifra)0 ){
      Z::operator+=(n_);
    }

    return *this;
  }

  Z_n& Z_n::operator*=(const CifraSigno derC)
  {

    Z::operator*=(derC);
    Z::operator%=(n_);


    return *this;
  }

  Z_n& Z_n::operator/=(const CifraSigno derC)
  {
    Z_n derEntero(Z(derC), n_);

    Funciones *funcs = Funciones::getInstance();

    PotModular *potMod; funcs->getFunc(potMod);
    Z_n inv(potMod->inversa(derEntero, n_), n_, false);

    operator*=(inv);

    return *this;
  }


  Z_n& Z_n::operator+=(const Cifra derC)
  {
    Cifra der = (derC % n_).toCifra();

    Z::operator+=(der);

    if( *this >= n_ )
      Z::operator-=(n_);

    return *this;
  }

  Z_n& Z_n::operator-=(const Cifra derC)
  { 
    Cifra der = (derC % n_).toCifra();

    Z::operator-=(der);

    if( *this < (Cifra)0 )
      Z::operator+=(n_);

    return *this;
  }

  Z_n& Z_n::operator*=(const Cifra derC)
  {
    Cifra der = (derC % n_).toCifra();

    Z::operator*=(der);
    Z::operator%=(n_);


    return *this;
  }

  Z_n& Z_n::operator/=(const Cifra derC)
  {
    Cifra der = (derC % n_).toCifra();

    Z_n inv(n_);
    Z derEntero(der);

    Funciones *funcs = Funciones::getInstance();
    PotModular *potMod; funcs->getFunc(potMod);
    inv = Z_n(potMod->inversa(Z(der), n_), n_, false);
    operator*=(inv);

    return *this;

  }


  Z_n& Z_n::operator^=(const Cifra e)
  {
    Funciones *funcs = Funciones::getInstance();

    Z eZ(e);
    PotModular *potMod; funcs->getFunc(potMod);
    potMod->potModular(this, eZ, n_);
    return *this;
  }

  Z_n& Z_n::operator^=(const CifraSigno e) 
  {
    Funciones *funcs = Funciones::getInstance();

    PotModular *potMod; funcs->getFunc(potMod);
    Z eZ(e);
    potMod->potModular(this, eZ, n_);
    return *this;
  }

  Z_n& Z_n::operator^=(const Z& e)
  {
    Funciones *funcs = Funciones::getInstance();

    PotModular *potMod; funcs->getFunc(potMod);
    potMod->potModular(this, e, n_);
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
//      throw Errores::DivisionPorCero();  
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
      throw Errores::DivisionPorCero();  

    izq /= der;

    return izq;
  }


  Z_n operator+(const CifraSigno corto, Z_n largo)
  {
    largo += corto;
    return largo;
  }

  Z_n operator-(const CifraSigno corto, Z_n largo)
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

  Z_n operator*(const CifraSigno corto, Z_n largo)
  {
    largo *= corto;
    return largo;
  }

  Z_n operator/(const CifraSigno corto, const Z_n& largo)
  {
    Z_n cortoZn(Z(corto), largo.modulo() );

    cortoZn /= largo;

    return cortoZn;

  }



  Z_n operator+(Z_n largo, const CifraSigno corto)
  {
    largo += corto;
    return largo;
  }
  Z_n operator-(Z_n largo, const CifraSigno corto)
  {
    largo -= corto;
    return largo;
  }
  Z_n operator*(Z_n largo, const CifraSigno corto)
  {
    largo *= corto;
    return largo;
  }
  Z_n operator/(Z_n largo, const CifraSigno corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero(); 

    largo /= corto;
    return largo;
  }










  Z_n operator+(const Cifra corto, Z_n largo)
  {
    largo += corto;
    return largo;
  }

  Z_n operator-(const Cifra corto, Z_n largo)
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

  Z_n operator*(const Cifra corto, Z_n largo)
  {
    largo *= corto;
    return largo;
  }

  Z_n operator/(const Cifra corto, const Z_n& largo)
  {
    if( largo.esCero() )
      throw Errores::DivisionPorCero();

    Z_n cortoZ_n(Z_n(corto), largo.modulo() );

    cortoZ_n /= largo;

    return cortoZ_n;

  }



  Z_n operator+(Z_n largo, const Cifra corto)
  {
    largo += corto;
    return largo;
  }
  Z_n operator-(Z_n largo, const Cifra corto)
  {
    largo -= corto;
    return largo;
  }
  Z_n operator*(Z_n largo, const Cifra corto)
  {
    largo *= corto;
    return largo;
  }

  Z_n operator/(Z_n largo, const Cifra corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();

    largo /= corto;
    return largo;
  }









  Z_n operator^(Z_n base, const Z& exp)
  {
    base ^= exp;
    return base;
  }

  Z_n operator^(Z_n base, const Cifra exp)
  {
    base ^= exp;
    return base;
  }

  Z_n operator^(Z_n base, const CifraSigno exp)
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
