/*
 * $Id$
 */

#ifndef __DIGIT_P_H
#define __DIGIT_P_H

#include <iostream>

#include "Field.h"
#include "MPPDataType.h"
#include "BasicTypedefs.h"
#include "Z.h"


namespace mpplas{
  class Digit_p : public MPPDataType, public Field<Digit_p> {
    public:
      Digit_p( const Digit p );
      Digit_p(const Digit n, const Digit p );
      Digit_p(const Digit_p& src );

      //convesion to Digit. Must be done this way because
      //Digit is a basic datatype. See Stroustrup 3rd Ed (2000), 11.4 (p 275)
      operator Digit() const { return this->value; };

      Digit_p& operator=(const Digit_p& src);

      bool operator==(const Digit_p& rhs) const;
      bool operator!=(const Digit_p& rhs) const;

      Digit_p& operator+=(const Digit rhs);
      Digit_p& operator-=(const Digit rhs);
      Digit_p& operator*=(const Digit rhs);
      Digit_p& operator/=(const Digit rhs);
      Digit_p& operator/=(const Digit_p& rhs);

      inline Digit getMod() const;
      Digit_p& invert();
      Digit_p getInverse() const;

      virtual std::string toString() const;

      /* Ring, Group and Field methods */
      static const Digit_p ZERO;
      static const Digit_p ONE;

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;


      Digit_p getMultInverse() const {
        Digit_p tmp(*this);
//        tmp.inverse();
        return tmp;
      }
      static const Digit_p& getMultIdentity() {
        return Digit_p::ONE ;
      };
      static const Digit_p& getAddIdentity() {
        return Digit_p::ZERO;
      };
      Digit_p getAddInverse() const{
        return _p - value;
      };
      static const Digit_p& getGroupGenerator() {
        return Digit_p::ONE;
      }
      Z getCharacteristic() const {
        return Z(_p);
      }

      Digit value;
    protected:
      Digit _p;
  };

  std::ostream& operator<<(std::ostream& out, const Digit_p& n);
  std::istream& operator>>(std::istream& in, Digit_p& n); 


  Digit_p operator+(Digit_p lhs, const Digit rhs);
  Digit_p operator-(Digit_p lhs, const Digit rhs);
  Digit_p operator*(Digit_p lhs, const Digit rhs);
  Digit_p operator/(Digit_p lhs, const Digit rhs);
  Digit_p operator/(Digit_p lhs, const Digit_p& rhs);

  ///////////////////////


  inline Digit Digit_p::getMod() const{
    return _p;
  }
}

#endif
