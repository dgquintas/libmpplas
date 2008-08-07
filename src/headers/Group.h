#ifndef __GROUP_H
#define __GROUP_H

#include "Constraints.h"

// http://www.gotw.ca/gotw/071.htm

namespace mpplas{
  template<class T>
    class Group {
      public:
//        T getAddInverse() const ;

        static const T& getAddIdentity() { return T::getAddIdentity();  };
        static const T& getGroupGenerator() { return T::getGroupGenerator(); }
        static bool isGroupCommutative() { return T::addCommutative; }
        static bool isGroupCyclic() { return T::groupCyclic; }

        /** Makes a group element zero.
         *
         * The group element on which the method is applied becomes zero, ie. 
         * the identity element for the (addition) operation of the group.
         *
         * @par Complexity: \f$O(1)\f$
         *
         * @return a reference to *this. */
        virtual T& makeZero() = 0;

        /** Returns the zero element for the group.
         *
         * Applied on a given datatype implementing Group<T>,
         * returns a zero for such a group.
         *
         * @par Complexity: \f$O(1)\f$
         *
         * @return a zero for the group of *this. */
        virtual const T& getZero() const { return T::getAddIdentity(); }


        /** Check for zero.
         *
         * @par Complexity: \f$O(1)\f$
         *
         * @return true if *this is a zero for its group. */
        virtual bool isZero() const = 0;
        virtual T& invertSign() = 0;

        virtual ~Group() {
          STATIC_ASSERT( ValidateRequirements() );
        }

      protected:
        Group(){};
      private:
        static bool ValidateRequirements() {
//          T& (T::*closure)(const T&) __attribute__ ((__unused__))      = &(T::operator+=) ;
          T (T::*getAddInverse)() const __attribute__ ((__unused__))  = &(T::getAddInverse) ;
          const T& (*getAddIdentity)() __attribute__ ((__unused__))  = &(T::getAddIdentity) ;
          const T& (*getGroupGenerator)() __attribute__ ((__unused__)) = &(T::getGroupGenerator) ;

          return true;
        }
    };
}

#endif
