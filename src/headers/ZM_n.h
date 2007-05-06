/*
 * $Id$
 */

#ifndef __ZM_N_H
#define __ZM_N_H

#include "Z.h"

namespace mpplas{


  /** "Montgomery modular integers" class 
   *
   * The idea is to have integers in Z/nZ which are internally
   * stored in the so called "Montgomery domain" (ie. xR (mod n)).
   *
   * @note This type can only be used with odd modulus.
   *
   * */
  class ZM_n : public Z
  {
    public: 


      /** Constructor given the modulus \f$n\f$.
       *
       * @param mod Integer representing the modulus. It must be
       * odd. 
       *
       * @throw Errors::ModuloParEnMontgomery The @a mod parameter 
       * is even when it should have been odd.
       */
      explicit ZM_n( const Z& mod);


      ZM_n( const Z& num, const Z& mod);
      ZM_n( const ZM_n& otro);


      ZM_n& operator=(const Z&);
      ZM_n& operator=(const ZM_n&);


      ZM_n& operator+=(const Z&);
      ZM_n& operator-=(const Z&);
      ZM_n& operator*=(const Z&);
      ZM_n& operator/=(const Z&);

      ZM_n& operator+=(const ZM_n&);
      ZM_n& operator-=(const ZM_n&);
      ZM_n& operator*=(const ZM_n&);
      ZM_n& operator/=(const ZM_n&);

      ZM_n& operator^=(const Z& e);
      ZM_n& operator^=(const SignedDigit e);

      ZM_n& square(void);
      ZM_n& inverse(void);

      Z toZ();

      inline const Z& getMod(void) const { return _mod; }

      ~ZM_n(){};



    private:
      Z _mod; /**< The modulus considered */
      Z _r; /**< The Montgomery R value for the modulus considered */
      Z _rSqr; /**< The Montgomery \f$ R^2 \f$ value for the modulus considered */
      Z _mPrime; /**< Precomputed (once per instance) value for the Montgomery methods */


      explicit ZM_n();

      /** Copies all except the actual value */
      void _clone(const ZM_n& src);

      /** Reducción de Montgomery. */
      void _montgomeryRed(Z& toReduce);
      /**  Realiza las precomputaciones del método. */
      void _precomputations(Z& mPrime);
      /** Montgomery product */
      ZM_n _montgomeryProd(const ZM_n& lhs, const Z& rhs);

      void _almostMontgomeryInverse(const ZM_n& a, Z& r, Digit& k);
      ZM_n _newMontgomeryInverse(const ZM_n& a);
     

      /** Input operator.  */
      friend std::istream& operator>>(std::istream&, ZM_n&);

  };

  ZM_n operator+(ZM_n, const Z&);
  ZM_n operator-(ZM_n, const Z&);
  ZM_n operator*(ZM_n, const Z&);
  ZM_n operator/(ZM_n, const Z&);
 
  ZM_n operator+(ZM_n, const ZM_n&);
  ZM_n operator-(ZM_n, const ZM_n&);
  ZM_n operator*(ZM_n, const ZM_n&);
  ZM_n operator/(ZM_n, const ZM_n&);


  ZM_n operator^(ZM_n base, const Z& exp); 
  ZM_n operator^(ZM_n base, const SignedDigit exp);


}



#endif
