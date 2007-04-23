/*
 * $Id$
 */

#ifndef __Z_N_H
#define __Z_N_H

#include "Z.h"

namespace mpplas{
  
  
  /** Clase para la representación de enteros modulares */
  class Z_n : public Z
  {

    public:
      /** Constructor de \f$Z_n\f$ dado \f$n\f$.
       *
       * @param mod Entero representando el módulo reductor.
       */
      explicit Z_n( const Z& mod);
       /** Constructor de \f$Z_n\f$ dado \f$n\f$.
       *
       * @param mod Digit representando el módulo reductor.
       */
     explicit Z_n( Digit mod);
       /** Constructor de \f$Z_n\f$ dado \f$n\f$.
       *
       * @param mod SignedDigit representando el módulo reductor.
       */
     explicit Z_n( SignedDigit mod);
      
       /** Constructor de \f$Z_n\f$ a partir de un entero y \f$n\f$.
       *
       * @param num Entero a introducir, tras reducirlo módulo \f$n\f$
       * en el entero modular a construir.
       * @param mod Entero representando el módulo reductor.
       * @param reducir Variable booleana que indica si realizar el
       * paso de reducción. Por omisión se considera "true".
       *
       */
     Z_n( const Z& num, const Z& mod, bool reducir=true);
        /** Constructor de \f$Z_n\f$ a partir de un entero y \f$n\f$.
       *
       * @param num Entero a introducir, tras reducirlo módulo \f$n\f$
       * en el entero modular a construir.
       * @param mod Digit representando el módulo reductor.
       * @param reducir Variable booleana que indica si realizar el
       * paso de reducción. Por omisión se considera "true".
       *
       */
     Z_n( const Z& num, Digit mod, bool reducir=true);
        /** Constructor de \f$Z_n\f$ a partir de un entero y \f$n\f$.
       *
       * @param num Entero a introducir, tras reducirlo módulo \f$n\f$
       * en el entero modular a construir.
       * @param mod SignedDigit representando el módulo reductor.
       * @param reducir Variable booleana que indica si realizar el
       * paso de reducción. Por omisión se considera "true".
       *
       */
     Z_n( const Z& num, SignedDigit mod, bool reducir=true);
      
       /** Constructor de copia de \f$Z_n\f$.
       *
       * @param otro Entero modular a copiar en *this.
       *
       */
      Z_n( const Z_n&  otro);

      
      Z_n& operator=(const Z&);
      Z_n& operator=(const Z_n&);
      
      
      Z_n& operator+=(const Z&);
      Z_n& operator-=(const Z&);
      Z_n& operator*=(const Z&);
      Z_n& operator/=(const Z&);

      Z_n& operator+=(const SignedDigit);
      Z_n& operator-=(const SignedDigit);
      Z_n& operator*=(const SignedDigit);
      Z_n& operator/=(const SignedDigit);

      Z_n& operator+=(const Digit);
      Z_n& operator-=(const Digit);
      Z_n& operator*=(const Digit);
      Z_n& operator/=(const Digit);

      Z_n& operator^=(const Digit e);
      Z_n& operator^=(const SignedDigit e);
      Z_n& operator^=(const Z& e);
   
      
      Z_n& cuadrado(void);
      
      //funciones de informacion
      inline const Z& modulo(void) const { return n_; }

      ~Z_n(){};

    private:
      Z n_; //el modulo reductor
    
    /** Operador obtencion del número */
    friend std::istream& operator>>(std::istream&, Z_n&);
    
  };

 
//  Z_n operator+(Z_n, const Z_n&);
//  Z_n operator-(Z_n, const Z_n&);
//  Z_n operator*(Z_n, const Z_n&);
//  Z_n operator/(Z_n, const Z_n&);

  Z_n operator+(Z_n, const Z&);
  Z_n operator-(Z_n, const Z&);
  Z_n operator*(Z_n, const Z&);
  Z_n operator/(Z_n, const Z&);


  Z_n operator+(const SignedDigit, Z_n);
  Z_n operator-(const SignedDigit, Z_n);
  Z_n operator*(const SignedDigit, Z_n);
  Z_n operator/(const SignedDigit, const Z_n&);

  Z_n operator+(Z_n, const SignedDigit);
  Z_n operator-(Z_n, const SignedDigit);
  Z_n operator*(Z_n, const SignedDigit);
  Z_n operator/(Z_n, const SignedDigit);

  Z_n operator+(const Digit, Z_n);
  Z_n operator-(const Digit, Z_n);
  Z_n operator*(const Digit, Z_n);
  Z_n operator/(const Digit, const Z_n&);

  Z_n operator+(Z_n, const Digit);
  Z_n operator-(Z_n, const Digit);
  Z_n operator*(Z_n, const Digit);
  Z_n operator/(Z_n, const Digit);

  Z_n operator^(Z_n base, const Z& exp); 
  Z_n operator^(Z_n base, const Digit exp); 
  Z_n operator^(Z_n base, const SignedDigit exp); 


}

#endif
