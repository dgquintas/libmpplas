#ifndef __FIELD_H
#define __FIELD_H

#include "Ring.h"

namespace mpplas{
  template<class T>
    class Field: public Ring<T>
    {
      public:

//        virtual T getMultInverse() const = 0;

        ~Field() {
          // for a ring to be also a field, it must fullfil the following
          // two conditions
          STATIC_ASSERT( T::divisionRing );
          STATIC_ASSERT( T::multCommutative );
          STATIC_ASSERT( ValidateRequirements() );
        }
      protected:
        Field(){};
      private:
        static bool ValidateRequirements() {
          T (T::*getMultInverse)() const __attribute__ ((__unused__))  = &(T::getMultInverse) ;
          return true;
        }

    };
}

#endif
