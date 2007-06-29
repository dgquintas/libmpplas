#ifndef __GROUP_H
#define __GROUP_H

#include <cassert>

// http://www.gotw.ca/gotw/071.htm

namespace mpplas{
  template<class T, bool ABELIAN>
    class Group
    {
      public:
        const T& getGroupIdentity() const{
          return T::getGroupIdentity();
        };
        T getGroupInverse()  const{
          return T::getAdditionInverse();
        };

        bool isGroupCommutative() const {
          return ABELIAN;
        }

        bool isGroupCyclic() const {
          return T::isGroupCyclic();
        }

        const T& getGroupGenerator() const {
          return T::getGroupGenerator();
        }


        ~Group() {
          assert( ValidateRequirements() );
        }

      private:
        static bool ValidateRequirements() {
          T& (T::*closure)(const T&) __attribute__ ((__unused__)) 
            = &(T::operator+=) ;

          const T& (*getGroupIdentity)() __attribute__ ((__unused__)) 
            = &(T::getGroupIdentity) ;
          T (T::*getGroupInverse)() const __attribute__ ((__unused__)) 
            = &(T::getGroupInverse) ;
          bool (*isGroupCyclic )() __attribute__ ((__unused__)) 
            = &(T::isGroupCyclic) ;
          const T& (*getGroupGenerator)() __attribute__ ((__unused__)) 
            = &(T::getGroupGenerator) ;

          return true;
        }
    };
}

#endif
