/*
 * $Id$
 */

#ifndef __Z_PX_H
#define __Z_PX_H

#include "Polynomial.h"
#include "Z_p.h"

#include <iostream>

namespace mpplas{
  class Z_px : public Polynomial<Z_p> , public Field<Z_px> {
    public:
      Z_px(const Z& p);
      Z_px(const Z_px& src);
      Z_px(const Polynomial<Z_p>& src);
      Z_px(const std::string& str, const Z& p);
      Z_px(const std::vector<Z_p>& coeffs, const Z& p);
      Z_px(const Z_p& coeff, const int exp, const Z& p);
      Z_px(const Z& coeff, const int exp, const Z& p);


      static Z_px gcd(Z_px u, Z_px v, Z_px* const s, Z_px* const t);

      /* Ring, Group and Field methods */
      static Z_px ZERO;
      static Z_px ONE;

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
        return -(*this);
      };
      static const Z_px& getGroupGenerator() {
        return Z_px::ONE;
      }
      Z_px getMultInverse() const {
        Z_px tmp(ONE);
        tmp /= (*this);
        return tmp;
      }
      const Z& getCharacteristic() const {
        return this->_p;
      }






    private:
      Z _p;

  }; /* class Z_px */

} /* namespace mpplas */

#endif