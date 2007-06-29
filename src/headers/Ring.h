#ifndef __RING_H
#define __RING_H

#include "Group.h"

namespace mpplas{
  template<class T, bool DIVISION_RING >
    class Ring : public Group<T, true /* abelian */> 
    {
      public:

        bool isUnitaryRing() const {
          return T::isUnitary();
        };
        bool isDivisionRing() const {
          return DIVISION_RING;
        }
        const T& getMultIdentity() const {
          return T::getMultIdentity();
        };
        bool isMultCommutative() const {
          return T::isMultCommutative();
        }
        bool isMultAssociative() const {
          return T::isMultAssociative();
        }


        ~Ring() {
          assert( ValidateRequirements() );
        }

      private:
        static bool ValidateRequirements() {
          T& (T::*multiplication)(const T&) __attribute__ ((__unused__)) 
            = &(T::operator*=) ;
          bool (*isUnitaryRing)() __attribute__ ((__unused__)) 
            = &(T::isUnitaryRing) ;
          const T& (*getMultIdentity)() __attribute__ ((__unused__)) 
            = &(T::getMultIdentity) ;
          bool (*isMultCommutative)() __attribute__ ((__unused__)) 
            = &(T::isMultCommutative) ;
          bool (*isMultAssociative)() __attribute__ ((__unused__)) 
            = &(T::isMultAssociative) ;


          return true;
        }
    };
}

#endif
