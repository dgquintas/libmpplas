/*
 * $Id$
 */

#ifndef __ZM_N_H
#define __ZM_N_H

#include "Z.h"
#include "Z_n.h"

namespace mpplas{


  /** "Montgomery modular integers" class 
   *
   * The idea is to have integers in Z/nZ which are internally
   * stored in the so called "Montgomery domain" (ie. xR \pmod n).
   *
   * Based on the paper: The Montgomery Modular Inverse - Revisited by
   * E. Savas and C. K. Koc
   *
   * @Warning This type can only be used with odd modulus.
   *
   * */
  class ZM_n : public Z {
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
      ZM_n( const Z_n& src);
      ZM_n( const ZM_n& src);


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

      /** Montgomery squaring.
       *
       * Converts the current Montgomery integer into its square in the
       * Montgomery domain. */
      ZM_n& square(void);

      /** Montgomery inverse.
       *
       * Converts the current Montgomery integer into its inverse in the 
       * Montgomery domain. */
      ZM_n& inverse(void);

      /** Convert from the Montgomery domain into the integer domain.
       *  @par Complexity:
       *       \f$O(n^{2})\f$
       * */
      Z toZ() const ;

      /** Returns the the reduction module for this Montgomery integer. */
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
      void _precomputations();
      /** Montgomery product */
      static ZM_n _montgomeryProd(const ZM_n& lhs, const Z& rhs);

      /** The @a AlmostMontgomeryInverse defined in the Koç paper.
       *
       * @pre \f$ a \in [1, m-1] \f$ with \f$m\f$ @a a's reduction modulus.
       * @post \f$ r \in [1, m-1] \f$, \f$ r = a^{-1}2^{k} \pmod m \f$ and 
       *       \f$ n \leq k \leq 2n \f$. */
      static void _almostMontgomeryInverse(const ZM_n& a, Z& r, Digit& k);

      /** The @a NewMontgomeryInverse defined in the Koç paper.
       *
       * @pre \f$ a2^{m} \pmod m \f$ with \f$m\f$ @a a's reduction modulus.
       * @post \f$ x = a^{-1}2^{m} \f$,  where \f$ x \in [1,m-1] \f$. */
      static ZM_n _newMontgomeryInverse(const ZM_n& a);
     

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
