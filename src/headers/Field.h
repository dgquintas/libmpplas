#ifndef __FIELD_H
#define __FIELD_H

#include "Ring.h"

namespace mpplas{
  template<class T>
    class Field: public Ring<T, true /* division ring */>
    {
      public:

        T getMultInverse() const {
          return T::getMultInverse();
        }

        ~Field() {
          assert( ValidateRequirements() );
        }

      private:
        static bool ValidateRequirements() {
          T (T::*getMultInverse)() const __attribute__ ((__unused__)) 
            = &(T::getMultInverse) ;
          return true;
        }
    };
}

#endif
