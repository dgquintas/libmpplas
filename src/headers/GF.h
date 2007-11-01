/*
 * $Id$
 */

#ifndef __GF_H
#define __GF_H

#include "Field.h"
#include "Z.h"
#include "Z_px.h"

namespace mpplas{

  class GF : public Z_px , public Field< GF > {
    public:
      GF(const Z& p, const int n = 1);
      GF(const Z& p, const Z_px& fx);
      GF(const Z_px& poly, const Z_px& fx);

      GF& operator=(const GF& src);

      /** Number of elements of the finite field */
      inline Z getOrder() const;
      inline const Z_px& getMod() const;


      GF& operator*=(const GF& rhs);
      GF& square();

      //inversion + product
      GF& operator/=(const GF& rhs);
      GF& invert();
      GF getInverse() const;

      GF& operator^=(const Z& exp);

      static bool isIrreducible(const Z_px& fx, const Z& p);
      static Z_px generateIrreducible(const int degree, const Z& p);
      static bool isPrimitive(const Z_px& fx, const MiVec<Z>& factors, const Z& p);
      static Z_px generatePrimitive(const int degree, const MiVec<Z>& factors, const Z& p);




      /* Ring, Group and Field methods */
      static const GF ZERO;
      static const GF ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;

      GF getMultInverse() const {
        return this->getInverse();
      }
      static const GF& getMultIdentity() {
        return GF::ONE ;
      };
      static const GF& getAddIdentity() {
        return GF::ZERO;
      };
      GF getAddInverse() const{
        return GF(Z_px::getAddInverse(), _fx);
      };
      static const GF& getGroupGenerator() {
        return GF::ONE;
      }


    protected:
      Z_px _fx;

      Z _p;
      int _n;


  }; /* class GF */

  inline Z GF::getOrder() const{
    return (_p ^ _n);
  }
  inline const Z_px& GF::getMod() const{
    return _fx;
  }


  GF operator^(GF lhs, const Z& rhs);



} /* namespace mpplas */


#endif
