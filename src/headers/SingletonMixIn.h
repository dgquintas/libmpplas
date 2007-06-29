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

  /** Singleton mixin template.
   *
   * It exports the methods @a getInstance and @a getReference, which return a pointer
   * and a reference, respectively, to the singleton instance of class that has been 
   * "mixed in" with this template.
   *
   * This singleton mixin implementation takes care of OpenMP synchronization issues.
   * It is therefore @e thread-safe in an OpenMP context.
   */
  template<typename T>
    class SingletonMixIn{
      public:
        /** Get a pointer to the singleton instance.
         *
         * @return A pointer to the singleton instance.
         */
        static T* getInstance(){return singletonInstance.get();}
        
        /** Get a reference to the singleton instance.
         *
         * @return A reference to the singleton instance.
         */
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
