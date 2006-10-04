/*
 * $Id$
 */

#ifndef __Z_N_H
#define __Z_N_H

#include "Z.h"

namespace numth{
  
  
  /** Clase para la representación de enteros modulares */
  class Z_n : public Z
  {

    public:
      /** Constructor de \f$Z_n\f$ dado \f$n\f$.
       *
       * @param mod Entero representando el módulo reductor.
       */
      Z_n( const Z& mod);
       /** Constructor de \f$Z_n\f$ dado \f$n\f$.
       *
       * @param mod Cifra representando el módulo reductor.
       */
     Z_n( const Cifra mod);
       /** Constructor de \f$Z_n\f$ dado \f$n\f$.
       *
       * @param mod CifraSigno representando el módulo reductor.
       */
     Z_n( const CifraSigno mod);
      
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
       * @param mod Cifra representando el módulo reductor.
       * @param reducir Variable booleana que indica si realizar el
       * paso de reducción. Por omisión se considera "true".
       *
       */
     Z_n( const Z& num, const Cifra mod, bool reducir=true);
        /** Constructor de \f$Z_n\f$ a partir de un entero y \f$n\f$.
       *
       * @param num Entero a introducir, tras reducirlo módulo \f$n\f$
       * en el entero modular a construir.
       * @param mod CifraSigno representando el módulo reductor.
       * @param reducir Variable booleana que indica si realizar el
       * paso de reducción. Por omisión se considera "true".
       *
       */
     Z_n( const Z& num, const CifraSigno mod, bool reducir=true);
      
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

      Z_n& operator+=(const CifraSigno);
      Z_n& operator-=(const CifraSigno);
      Z_n& operator*=(const CifraSigno);
      Z_n& operator/=(const CifraSigno);

      Z_n& operator+=(const Cifra);
      Z_n& operator-=(const Cifra);
      Z_n& operator*=(const Cifra);
      Z_n& operator/=(const Cifra);

      Z_n& operator^=(const Cifra e);
      Z_n& operator^=(const CifraSigno e);
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

 
  Z_n operator+(Z_n, const Z_n&);
  Z_n operator-(Z_n, const Z_n&);
  Z_n operator*(Z_n, const Z_n&);
  Z_n operator/(Z_n, const Z_n&);

  Z_n operator+(const CifraSigno, Z_n);
  Z_n operator-(const CifraSigno, Z_n);
  Z_n operator*(const CifraSigno, Z_n);
  Z_n operator/(const CifraSigno, const Z_n&);

  Z_n operator+(Z_n, const CifraSigno);
  Z_n operator-(Z_n, const CifraSigno);
  Z_n operator*(Z_n, const CifraSigno);
  Z_n operator/(Z_n, const CifraSigno);

  Z_n operator+(const Cifra, Z_n);
  Z_n operator-(const Cifra, Z_n);
  Z_n operator*(const Cifra, Z_n);
  Z_n operator/(const Cifra, const Z_n&);

  Z_n operator+(Z_n, const Cifra);
  Z_n operator-(Z_n, const Cifra);
  Z_n operator*(Z_n, const Cifra);
  Z_n operator/(Z_n, const Cifra);

  Z_n operator^(Z_n base, const Z& exp); 
  Z_n operator^(Z_n base, const Cifra exp); 
  Z_n operator^(Z_n base, const CifraSigno exp); 


}

#endif
