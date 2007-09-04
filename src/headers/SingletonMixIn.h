/*
 * $Id$
 */


#ifndef __SINGLETONMIXIN_H
#define __SINGLETONMIXIN_H

#include <memory>
#include "omp_mock.h"
#include <cassert>

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
        static T* getInstance(){
          T* ptr = (_getInstanceAutoPtr()).get(); 
          assert( ptr != 0 );
          return ptr;
        }
        
        /** Get a reference to the singleton instance.
         *
         * @return A reference to the singleton instance.
         */
        static T& getReference(){
          return *(_getInstanceAutoPtr());
        }


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

      private:

        /** Returns the smart pointer to the singleton instance. 
         *
         * Lazy initialization. Otherwise, if we relied on "static"
         * initialization, we might have circular dependencies.  */
        static const std::auto_ptr< T >& _getInstanceAutoPtr(){
          if( _singletonInstance.get() == 0 ){
            _singletonInstance.reset( new T );
          }

          return _singletonInstance;
        }

        omp_nest_lock_t _lock;
        static std::auto_ptr< T > _singletonInstance;

        

  };
}


#endif
