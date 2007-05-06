/*
 * $Id$
 */

#include <memory>
#ifdef _OPENMP
  #include <omp.h>
#else
  #include "omp_mock.h"
#endif

#ifndef __SINGLETONMIXIN_H
#define __SINGLETONMIXIN_H

namespace mpplas{
  template<typename T>
    class SingletonMixIn{
      public:
        static T* getInstance(){return singletonInstance.get();}
        static T& getReference(){return *singletonInstance;}
        virtual ~SingletonMixIn(){
          omp_destroy_nest_lock(&_lock);
        }

        
      protected:
        SingletonMixIn() {
          omp_init_nest_lock(&_lock);
        };

        inline void _get_lock(){
          omp_set_nest_lock(&_lock);
          return;
        }

        inline void _release_lock(){
          omp_unset_nest_lock(&_lock);
          return;
        }


        static const std::auto_ptr< T > singletonInstance;
        omp_nest_lock_t _lock;

        

  };
}


#endif
