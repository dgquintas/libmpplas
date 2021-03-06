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

        /** Makes a group element zero.
         *
         * The group element on which the method is applied becomes zero, ie. 
         * the identity element for the (addition) operation of the group.
         *
         * @par Complexity: \f$O(1)\f$
         *
         * @return a reference to *this. */
        virtual T& makeOne() = 0;

        /** Returns the one element for the group.
         *
         * Applied on a given datatype implementing Ring<T>,
         * returns a one for such a ring.
         *
         * @par Complexity: \f$O(1)\f$
         *
         * @return a zero for the group of *this. */
//        virtual const T& getOne() const = 0; //{ return T::getMultIdentity(); }

        /** Check for unity.
         *
         * @par Complexity: \f$O(1)\f$
         *
         * @return true if *this is a one for its ring. */
        virtual bool isOne() const = 0;

        virtual ~Ring() {
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
