/*
 * $Id$
 */

#ifndef __Z_P_H
#define __Z_P_H

#include "Z_n.h"
#include "Field.h"
#include "Errors.h"


namespace mpplas{
  class Z_p : public Z_n, public Field<Z_p> {
    public:
      explicit Z_p(const Z& mod, const bool checkPrimality = true) throw(Errors::PrimeRequired);
      Z_p( const Z& num, const Z& mod, const bool reduce = true, const bool checkPrimality = true) throw(Errors::PrimeRequired) ;
      Z_p(const Z_p& src);
      Z_p(const Z_n& src) throw(Errors::PrimeRequired) ;

      Z_p& operator=(const Z& integer);
      Z_p& operator=(const Z_n& integer);

      virtual ~Z_p(){};

      /* Ring, Group and Field methods */
      static const Z_p ZERO;
      static const Z_p ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;


      Z_p getMultInverse() const {
        Z_p tmp(*this);
        tmp.inverse();
        return tmp;
      }
      static const Z_p& getMultIdentity() {
        return Z_p::ONE ;
      };
      static const Z_p& getAddIdentity() {
        return Z_p::ZERO;
      };
      Z_p getAddInverse() const{
        return Z_n::getAddInverse();
      };
      static const Z_p& getGroupGenerator() {
        return Z_p::ONE;
      }


  };

}

#endif
