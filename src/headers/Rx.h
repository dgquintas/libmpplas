/*
 * $Id$
 */

#ifndef __RX_H
#define __RX_H

#include "Polynomial.h"
#include "Field.h"
#include "R.h"
#include "Z.h"

namespace mpplas{
  class Rx : public Polynomial<R>, Field< Rx > {
    public:
      Rx();
      Rx(const Rx& src);
      Rx(const Polynomial<R>& src);
      Rx(const std::string& str);
      Rx(const std::vector<R>& coeffs);
      Rx(const R& coeff, const int exp);

      Rx& operator=(const Rx& src);

      /* Ring, Group and Field methods */
      static const Rx ZERO;
      static const Rx ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;

      static const Rx& getMultIdentity() {
        return Rx::ONE ;
      };
      static const Rx& getAddIdentity() {
        return Rx::ZERO;
      };
      Rx getAddInverse() const{
        return -(*this);
      };
      static const Rx& getGroupGenerator() {
        return Rx::ONE;
      }
      Rx getMultInverse() const {
        Rx tmp(ONE);
        tmp /= (*this);
        return tmp;
      }
      Z getCharacteristic() const {
        return Z::ZERO;
      }


  }; /* class Rx */

} /* namespace mpplas */

#endif
