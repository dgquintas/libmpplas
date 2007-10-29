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

        ~Group() {
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
