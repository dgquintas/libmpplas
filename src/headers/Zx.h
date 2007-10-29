/*
 * $Id$
 */

#ifndef __ZX_H
#define __ZX_H

#include "Polynomial.h"
#include "Z.h"

namespace mpplas{
  class Zx : public Polynomial<Z>, public Ring< Zx > {
    public:
      Zx();
      Zx(const Zx& src);
      Zx(const Polynomial<Z>& src);
      Zx(const std::string& str);
      Zx(const std::vector<Z>& coeffs);
      Zx(const Z& coeff, const int exp);

      static Zx gcd( Zx u, Zx v );






      static Zx ZERO;
      static Zx ONE;

      /* Ring and Group methods */
        static const bool addCommutative;
        static const bool groupCyclic;

        static const bool unitaryRing;
        static const bool multCommutative;
        static const bool multAssociative;
        static const bool divisionRing;

        static const Zx& getAddIdentity() {
          return ZERO;
        };
        Zx getAddInverse()  const{
          return -(*this);
        };
        static const Zx& getGroupGenerator() {
          return ONE;
        }
        static const Zx& getMultIdentity() {
          return ONE ;
        }; 
        const Z& getCharacteristic() const {
          return Z::ZERO;
        }




  }; /* class Zx */


} /* namespace mpplas */

#endif
