#ifndef __RING_H
#define __RING_H

#include "Group.h"

namespace mpplas{
  class Z;
  template<class T>
    class Ring : public Group<T> 
    {
      public:
        /** The smallest number of times one must add the multiplicative 
         * identity element (1) to itself to get the additive identity 
         * element (0) */
        //inline const Z& getCharacteristic() const;

        static const T& getMultIdentity() { return T::getMultIdentity();  };

        static bool isMultCommutative() { return T::multCommutative; }
        static bool isMultAssociative() { return T::multAssociative; }
        static bool isUnitaryRing() { return T::unitaryRing; };
        static bool isDivisionRing() { return T::divisionRing; }

        virtual T& makeOne() = 0;
        virtual bool isOne() const = 0;

        ~Ring() {
          STATIC_ASSERT( ValidateRequirements() );

          // the group "component" of the ring must be commutative (abelian)
          STATIC_ASSERT( T::addCommutative );
        }

      protected:
        Ring(){};

      private:
        static bool ValidateRequirements() {
//          T& (T::*multiplication)(const T&) __attribute__ ((__unused__)) = &(T::operator*=) ;
          const T& (*getMultIdentity)() __attribute__ ((__unused__)) = &(T::getMultIdentity) ;
          T (T::*getAddInverse)() const __attribute__ ((__unused__)) = &(T::getAddInverse) ;
          Z (T::*getCharacteristic)() const __attribute__ ((__unused__)) = &(T::getCharacteristic) ;
          return true;
        }
    };
}

#endif
