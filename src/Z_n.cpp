/*
 * $Id: Z_n.cpp,v 1.3 2006/09/06 14:16:24 dgquintas Exp $
 */

#include "Z_n.h"
#include "Funciones.h"
#include <algorithm>

namespace numth{

  Z_n::Z_n(const Z& mod)
    : Z(), n_(mod)
    {}

  Z_n::Z_n(const Cifra mod)
    : Z()
    {
      n_ = Z::convertir(mod);
    }


  Z_n::Z_n(const CifraSigno mod)
    : Z()
    {
      n_ = Z::convertir(mod);
    }

  Z_n::Z_n(const Z& num, const Z& mod, bool reducir)
    : Z(num)
    {
      n_ = mod;
      if( reducir)
        this->operator%=(n_);
    }

  Z_n::Z_n(const Z& num, const Cifra mod, bool reducir)
    : Z(num)
    {

      n_ = Z::convertir(mod);
      if( reducir )
        Z::operator%=(n_);
    }


  Z_n::Z_n(const Z& num, const CifraSigno mod, bool reducir)
    : Z(num)
    {
      n_ = Z::convertir(mod);
      if( reducir )
        Z::operator%=(n_);
    }

  Z_n::Z_n(const Z_n& otro)
    : Z(otro), n_(otro.n_)
    {
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
      Z::operator-=(n_);

    return *this;
  }

  Z_n& Z_n::operator-=(const Z& der)
  {
    Z::operator-=(der);

    if( *this < (Cifra)0 )
      Z::operator+=(n_);

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
    Funciones funcs;

    inv = Z_n(funcs.potModular()->inversa(der, n_), n_, false);
    operator*=(inv);

    return *this;
  }


  /* simple prec */
  Z_n& Z_n::operator+=(const CifraSigno derC)
  {
    CifraSigno der = (derC % n_)[0];
    if( n_.esNegativo() )
      der *= -1;

    Z::operator+=(der);

    if( *this >= n_ )
      Z::operator-=(n_);

    return *this;
  }

  Z_n& Z_n::operator-=(const CifraSigno derC)
  {

    CifraSigno der = (derC % n_)[0];
    if( n_.esNegativo() )
      der *= -1;

    Z::operator-=(der);

    if( *this < (Cifra)0 )
      Z::operator+=(n_);

    return *this;
  }

  Z_n& Z_n::operator*=(const CifraSigno derC)
  {

    CifraSigno der = (derC % n_)[0];
    if( n_.esNegativo() )
      der *= -1;

    Z::operator*=(der);
    Z::operator%=(n_);


    return *this;
  }

  Z_n& Z_n::operator/=(const CifraSigno derC)
  {

    CifraSigno der = (derC % n_)[0];
    if( n_.esNegativo() )
      der *= -1;

    Z_n inv(n_);

    Z derEntero = Z::convertir(der);

    Funciones funcs;

    inv = Z_n(funcs.potModular()->inversa(Z::convertir(der), n_), n_, false);

    operator*=(inv);

    return *this;
  }


  Z_n& Z_n::operator+=(const Cifra derC)
  {
    Cifra der = (derC % n_)[0];
    if( n_.esNegativo() )
      der *= -1;

    Z::operator+=(der);

    if( *this >= n_ )
      Z::operator-=(n_);

    return *this;
  }

  Z_n& Z_n::operator-=(const Cifra derC)
  { 
    Cifra der = (derC % n_)[0];
    if( n_.esNegativo() )
      der *= -1;

    Z::operator-=(der);

    if( *this < (Cifra)0 )
      Z::operator+=(n_);

    return *this;
  }

  Z_n& Z_n::operator*=(const Cifra derC)
  {
    Cifra der = (derC % n_)[0];
    if( n_.esNegativo() )
      der *= -1;

    Z::operator*=(der);
    Z::operator%=(n_);


    return *this;
  }

  Z_n& Z_n::operator/=(const Cifra derC)
  {

    CifraSigno der = (derC % n_)[0];
    if( n_.esNegativo() )
      der *= -1;

    Z_n inv(n_);
    Z derEntero = Z::convertir(der);

    Funciones funcs;
    inv = Z_n(funcs.potModular()->inversa(Z::convertir(der), n_), n_, false);
    operator*=(inv);

    return *this;

  }


  Z_n& Z_n::operator^=(const Cifra e)
  {
    Funciones funcs;

    Z eZ = Z::convertir(e);
    funcs.potModular()->potModular(this, eZ, n_);
    return *this;
  }

  Z_n& Z_n::operator^=(const CifraSigno e) 
  {
    Funciones funcs;

    Z eZ = Z::convertir(e);
    funcs.potModular()->potModular(this, eZ, n_);
    return *this;
  }

  Z_n& Z_n::operator^=(const Z& e)
  {
    Funciones funcs;

    funcs.potModular()->potModular(this, e, n_);
    return *this;
  }



  std::istream& 
    operator>>(std::istream& is, Z_n& numero)
    {
      operator>>(is, (Z&)numero);
      numero %= numero.n_;

      return is;
    }


  Z_n operator+(Z_n izq, const Z_n& der)
  {
    izq += der;

    return izq;
  }

  Z_n operator-(Z_n izq, const Z_n& der)
  {
    izq -= der;

    return izq;
  } 

  Z_n operator*(Z_n izq, const Z_n& der)
  {
    izq *= der;

    return izq;
  }

  Z_n operator/(Z_n izq, const Z_n& der)
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
    Z temp = Z::convertir(corto) % largo.modulo();
    temp -= largo;
    //largo.cambiarSigno();
    // en Z_n_n el cambio de signo es equivalente a restar el nº a cambiar
    // de signo al modulo
    if(temp.esNegativo() )
      temp += largo.modulo();

    return Z_n(temp, largo.modulo(), false);
  }

  Z_n operator*(const CifraSigno corto, Z_n largo)
  {
    largo *= corto;
    return largo;
  }

  Z_n operator/(const CifraSigno corto, const Z_n& largo)
  {
    Z_n cortoZn(Z::convertir(corto), largo.modulo() );

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
    Z temp = Z::convertir(corto) % largo.modulo();
    temp -= largo;
    //largo.cambiarSigno();
    // en Z_n_n el cambio de signo es equivalente a restar el nº a cambiar
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

    Z_n cortoZ_n(Z_n::convertir(corto), largo.modulo() );

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
