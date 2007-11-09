/*
 * $Id$
 */

#ifndef __GFX_H
#define __GFX_H

#include "Field.h"
#include "Z.h"
#include "Z_px.h"
#include "GF.h"

namespace mpplas{

  class GFx : public Z_px , public Field< GFx >  {
  
    public:
      GFx(const GFx& src);

      GFx& operator=(const GFx& src);

      GFx& fromString(const std::string& str);

      GFx& operator+=(const GFx& rhs);
      GFx& operator-=(const GFx& rhs);

      GFx& operator*=(const GFx& rhs);
      virtual GFx& square();

      //inversion + product
      GFx& operator/=(const GFx& rhs);
      GFx& invert();
      GFx getInverse() const;

      GFx& operator^=(const Z& exp);

      Z toZ() const;
      GFx& fromZ(const Z& src);

      inline const GF& getGenerator() const;

      /* Ring, Group and Field methods */
      static const GFx ZERO;
      static const GFx ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;

      GFx getMultInverse() const {
        return this->getInverse();
      }
      static const GFx& getMultIdentity() {
        return GFx::ONE ;
      };
      static const GFx& getAddIdentity() {
        return GFx::ZERO;
      };
      GFx getAddInverse() const{
        return GFx(Z_px::getAddInverse(), _gfGenerator);
      };
      static const GFx& getGroupGenerator() {
        return GFx::ONE;
      }

    protected:
      GFx(const Z_px& poly, const GF& generator);
      GFx(const Z& value, const GF& generator);
      GFx(const GF& generator);

    private:
      GF _gfGenerator;
      Z_px _fx;
      Z _p;

      friend class mpplas::GF;

  };

  GFx operator+(GFx lhs, const GFx& rhs);
  GFx operator-(GFx lhs, const GFx& rhs);
  GFx operator*(GFx lhs, const GFx& rhs);
  GFx operator/(GFx lhs, const GFx& rhs);


  GFx operator^(GFx lhs, const Z& rhs);








  inline const GF& GFx::getGenerator() const{
    return this->_gfGenerator;
  }




}


#endif