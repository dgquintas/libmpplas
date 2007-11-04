/*
 * $Id$
 */

#ifndef __Z_N_H
#define __Z_N_H

#include "Z.h"

namespace mpplas{
  /** Clase para la representación de enteros modulares */
  class Z_n : public Z, public Ring<Z_n> {

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
      
      Z_n& operator+=(const Z_n& rhs);
      Z_n& operator-=(const Z_n& rhs);
      Z_n& operator*=(const Z_n& rhs);
      Z_n& operator/=(const Z_n& rhs);


      
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

      Z_n& operator^=(const Z& e);
   
      Z_n& inverse();
      
      Z_n& cuadrado(void);
      
      //funciones de informacion
      inline const Z& getMod() const { return n_; }


//      virtual std::string toString() const;

     
    /* Ring and Group methods */
      static const Z_n ZERO;
      static const Z_n ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;


      static const Z_n& getMultIdentity() {
        return Z_n::ONE ;
      };
      static const Z_n& getAddIdentity() {
        return Z_n::ZERO;
      };
      Z_n getAddInverse() const{
        return Z_n((n_ - (*this),this->getMod()) );
      };
      static const Z_n& getGroupGenerator() {
        return Z_n::ONE;
      }
      Z getCharacteristic() const {
        return n_;
      }


      virtual ~Z_n(){};

    protected:
      Z n_; //el modulo reductor

    private:
      Z _exponentiationPrecompts;
    
    /** Operador obtencion del número */
    friend std::istream& operator>>(std::istream&, Z_n&);
    
  };

  Z_n operator-(const Z_n& rhs);
 
  Z_n operator+(Z_n, const Z_n&);
  Z_n operator-(Z_n, const Z_n&);
  Z_n operator*(Z_n, const Z_n&);
  Z_n operator/(Z_n, const Z_n&);

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
