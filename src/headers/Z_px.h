/*
 * $Id$
 */

#ifndef __Z_PX_H
#define __Z_PX_H

#include "Polynomial.h"
#include "Z_p.h"

#include <iostream>



namespace mpplas{

  class GF;

  class Z_px : public Polynomial<Z_p> , public Field<Z_px> {
    public:
      Z_px(const Z& p);
      Z_px(const Z_px& src);
      Z_px(const Polynomial<Z_p>& src);
      Z_px(const std::string& str, const Z& p);
      Z_px(const std::vector<Z_p>& coeffs, const Z& p);
      Z_px(const Z_p& coeff, const int exp, const Z& p);
      Z_px(const Z& coeff, const int exp, const Z& p);
  
      /** Assignment operator */
      Z_px& operator=(const Z_px& src);

      /** Greatest common divisor.
       *
       * Convenience shortcut for the calculation of the greatest common
       * divisor. It relies on the implementations of 
       * @a GCDExt< Polynomial<Z_p> > and @a GCD< Polynomial<Z_p> > given
       * by @a mpplas::MethodsFactory.
       *
       * The optional output parameters @a s and @a t are only used for the
       * extended version, that is, they represent the Bézout coefficients.
       *
       * @note 
       * If either @a s or @a t is @e not NULL, the other one must also be
       * @e not NULL. That is to say, it must not be the case that only of 
       * of them is not NULL. 
       *
       * @param u first operator
       * @param v second operator
       * @param[out] s if not null, it will contain the Bézout coefficient for @a u.
       * @param[out] t if not null, it will contain the Bézout coefficient for @a v. 
       *
       * @return the greatest common divisor of @a u and @a v. */
      static Z_px gcd(Z_px u, Z_px v, Z_px* const s = NULL, Z_px* const t = NULL);


      typedef mpplas::GF GF;

      virtual inline Z_px& makeZero(){ Polynomial<Z_p>::makeZero(); return *this;} 
      virtual inline Z_px& makeOne() { Polynomial<Z_p>::makeOne();  return *this;}

      virtual bool isZero() const { return Polynomial<Z_p>::isZero(); }
      virtual bool isOne() const {  return Polynomial<Z_p>::isOne(); }
      virtual inline Z_px& invertSign(){ Polynomial<Z_p>::changeSign(); return *this; }

      /* Ring, Group and Field methods */
      static const Z_px ZERO;
      static const Z_px ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;

      static const Z_px& getMultIdentity() {
        return Z_px::ONE ;
      };
      static const Z_px& getAddIdentity() {
        return Z_px::ZERO;
      };
      Z_px getAddInverse() const{
        Z_px addInv(*this);
        const Z& p( this->_data[0].getMod() );
        for( int i = 0 ; i < addInv._data.size(); i++){
          addInv._data[i] = p - addInv._data[i];
        }
        return addInv;
      };
      static const Z_px& getGroupGenerator() {
        return Z_px::ONE;
      }
      Z_px getMultInverse() const {
        Z_px tmp(ONE);
        tmp /= (*this);
        return tmp;
      }
      Z getCharacteristic() const {
        return this->_data[0].getMod();
      }

  }; /* class Z_px */

} /* namespace mpplas */

#endif
