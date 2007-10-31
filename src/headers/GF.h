/*
 * $Id$
 */

#ifndef __GF_H
#define __GF_H

#include "Field.h"
#include "Z.h"
#include "Z_px.h"

namespace mpplas{

  class GF : public Z_px /*, public Field< GF >*/ {
    public:
//      GF(const Z& p, const Digit n = 1);
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

      static bool _isIrreducible(const Z_px& fx, const Z& p);
      static Z_px _genIrreducible(const int degree, const Z& p);

    protected:
      Z_px _fx;

      Z _p;
      Digit _n;

//      static Z_px _genPrimitivePolynomial(const int degree);

  }; /* class GF */




  inline Z GF::getOrder() const{
    return (_p ^ _n);
  }
  inline const Z_px& GF::getMod() const{
    return _fx;
  }




} /* namespace mpplas */


#endif
