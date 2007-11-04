/*
 * $Id$
 */

#ifndef __DIGIT_PX_H
#define __DIGIT_PX_H

#include "Polynomial.h"
#include "Digit_p.h"

#include <iostream>

namespace mpplas{
  class Digit_px : public Polynomial<Digit_p> , public Field<Digit_px> {
    public:
      Digit_px(const Digit p);
      Digit_px(const Digit_px& src);
      Digit_px(const Polynomial<Digit_p>& src);
      Digit_px(const std::string& str, const Digit p);
      Digit_px(const std::vector<Digit_p>& coeffs, const Digit p);
      Digit_px(const Digit_p& coeff, const int exp, const Digit p);
      Digit_px(const Digit coeff, const int exp, const Digit p);
  
      Digit_px& operator=(const Digit_px& src);

      static Digit_px gcd(Digit_px u, Digit_px v, Digit_px* const s = NULL, Digit_px* const t = NULL);

      /* Ring, Group and Field methods */
      static const Digit_px ZERO;
      static const Digit_px ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;



      static const Digit_px& getMultIdentity() {
        return Digit_px::ONE ;
      };
      static const Digit_px& getAddIdentity() {
        return Digit_px::ZERO;
      };
      Digit_px getAddInverse() const{
        Digit_px addInv(*this);
        const Digit& p( this->_data[0].getMod() );
        for( int i = 0 ; i < addInv._data.size(); i++){
          addInv._data[i] = p - addInv._data[i].value;
          //XXX: es necesario reducir?
        }
        return addInv;
      };
      static const Digit_px& getGroupGenerator() {
        return Digit_px::ONE;
      }
      Digit_px getMultInverse() const {
        Digit_px tmp(ONE);
        tmp /= (*this);
        return tmp;
      }
      Z getCharacteristic() const {
        return this->_data[0].getMod();
      }

  }; /* class Digit_px */

} /* namespace mpplas */

#endif
